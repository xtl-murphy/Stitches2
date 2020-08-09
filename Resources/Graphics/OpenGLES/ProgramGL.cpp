

/**
 * ProgramGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:31
 **/
#include "Graphics/Base/ShaderCache.hpp"
#include "ProgramGL.hpp"
#include "Graphics/Base/ProgramCache.hpp"
#include "UtilsGL.hpp"

NS_STITCHES_BEGIN

ProgramGL::ProgramGL(const String &vertexShader, const String &fragmentShader)
: Program(vertexShader, fragmentShader)
{
    mVertexShaderModule = dynamic_cast<ShaderModuleGL*>(ShaderCache::newVertexShaderModule(vertexShader));
    mFragmentShaderModule = dynamic_cast<ShaderModuleGL*>(ShaderCache::newFragmentShaderModule(fragmentShader));

    SAFE_RETAIN(mVertexShaderModule);
    SAFE_RETAIN(mFragmentShaderModule);
    compileProgram();
    computeUniformInfos();
    computeLocations();
}

ProgramGL::~ProgramGL()
{
    SAFE_RELEASE(mVertexShaderModule);
    SAFE_RELEASE(mFragmentShaderModule);
    if (mProgramId)
        glDeleteProgram(mProgramId);
}

UniformLocation ProgramGL::getUniformLocation(const String &uniform) const
{
    UniformLocation uniformLocation;
    if (mActiveUniformInfos.find(uniform) != mActiveUniformInfos.end())
    {
        const auto &uniformInfo = mActiveUniformInfos.at(uniform);
        uniformLocation.location[0] = uniformInfo.location;
        uniformLocation.location[1] = uniformInfo.bufferOffset;
    }
    return uniformLocation;
}

UniformLocation ProgramGL::getUniformLocation(Uniform name) const
{
    return mBuiltinUniformLocation[name];
}

int ProgramGL::getAttributeLocation(const String &name) const
{
    return glGetAttribLocation(mProgramId, name.c_str());
}

int ProgramGL::getAttributeLocation(Attribute name) const
{
    return mBuiltinAttributeLocation[name];
}

int ProgramGL::getMaxVertexLocation() const
{
    return mMaxLocation;
}

int ProgramGL::getMaxFragmentLocation() const
{
    return mMaxLocation;
}

const std::unordered_map<String, AttributeBindInfo> ProgramGL::getActiveAttributes() const
{
    std::unordered_map<std::string, AttributeBindInfo> attributes;

    if (!mProgramId) return attributes;

    GLint numOfActiveAttributes = 0;
    glGetProgramiv(mProgramId, GL_ACTIVE_ATTRIBUTES, &numOfActiveAttributes);


    if (numOfActiveAttributes <= 0)
        return attributes;

    attributes.reserve(numOfActiveAttributes);

    int MAX_ATTRIBUTE_NAME_LENGTH = 256;
    std::vector<char> attrName(MAX_ATTRIBUTE_NAME_LENGTH + 1);

    GLint attrNameLen = 0;
    GLenum attrType;
    GLint attrSize;
    AttributeBindInfo info;

    for (int i = 0; i < numOfActiveAttributes; i++)
    {
        glGetActiveAttrib(mProgramId, i, MAX_ATTRIBUTE_NAME_LENGTH, &attrNameLen, &attrSize, &attrType, attrName.data());
        CHECK_GL_ERROR_DEBUG();
        info.attributeName = std::string(attrName.data(), attrName.data() + attrNameLen);
        info.location = glGetAttribLocation(mProgramId, info.attributeName.c_str());
        info.type = attrType;
        info.size = UtilsGL::getGLDataTypeSize(attrType) * attrSize;
        CHECK_GL_ERROR_DEBUG();
        attributes[info.attributeName] = info;
    }

    return attributes;
}

void ProgramGL::compileProgram()
{
    if (mVertexShaderModule == nullptr || mFragmentShaderModule == nullptr)
        return;

    auto vertShader = mVertexShaderModule->getShader();
    auto fragShader = mFragmentShaderModule->getShader();

//    assert (vertShader != 0 && fragShader != 0);
    if (vertShader == 0 || fragShader == 0)
        return;

    mProgramId = glCreateProgram();
    if (!mProgramId)
        return;

    glAttachShader(mProgramId, vertShader);
    glAttachShader(mProgramId, fragShader);

    glLinkProgram(mProgramId);

    GLint status = 0;
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &status);
    if (GL_FALSE == status)
    {
        LOGE("OpenGLES", "ERROR: %s: failed to link program", __FUNCTION__);
        glDeleteProgram(mProgramId);
        mProgramId = 0;
    }
}

bool ProgramGL::getAttributeLocation(const String &attributeName, unsigned int &location) const
{
    GLint loc = glGetAttribLocation(mProgramId, attributeName.c_str());
    if (-1 == loc)
    {
        LOGE("OpenGLES", "Stitches: %s: can not find vertex attribute of %s", __FUNCTION__, attributeName.c_str());
        return false;
    }

    location = GLuint(loc);
    return true;
}

void ProgramGL::computeUniformInfos()
{
    if (!mProgramId)
        return;

    GLint numOfUniforms = 0;
    glGetProgramiv(mProgramId, GL_ACTIVE_UNIFORMS, &numOfUniforms);
    if (!numOfUniforms)
        return;

#define MAX_UNIFORM_NAME_LENGTH 256
    UniformInfo uniform;
    GLint length = 0;
    mTotalBufferSize = 0;
    mMaxLocation = -1;
    mActiveUniformInfos.clear();
    GLchar* uniformName = (GLchar*)malloc(MAX_UNIFORM_NAME_LENGTH + 1);
    for (int i = 0; i < numOfUniforms; ++i)
    {
        glGetActiveUniform(mProgramId, i, MAX_UNIFORM_NAME_LENGTH, &length, &uniform.count, &uniform.type, uniformName);
        uniformName[length] = '\0';

        if (length > 3)
        {
            char* c = strrchr(uniformName, '[');
            if (c)
            {
                *c = '\0';
                uniform.isArray = true;
            }
        }
        uniform.location = glGetUniformLocation(mProgramId, uniformName);
        uniform.size = UtilsGL::getGLDataTypeSize(uniform.type);
        uniform.bufferOffset = (uniform.size == 0) ? 0 : mTotalBufferSize;
        mActiveUniformInfos[uniformName] = uniform;
        mTotalBufferSize += uniform.size * uniform.count;
        mMaxLocation = mMaxLocation <= uniform.location ? (uniform.location + 1) : mMaxLocation;
    }
    free(uniformName);
}

void ProgramGL::computeLocations()
{
    std::fill(mBuiltinAttributeLocation, mBuiltinAttributeLocation + ATTRIBUTE_MAX, -1);
//    std::fill(mBuiltinUniformLocation, mBuiltinUniformLocation + UNIFORM_MAX, -1);

    ///a_position
    auto location = glGetAttribLocation(mProgramId, ATTRIBUTE_NAME_POSITION);
    mBuiltinAttributeLocation[Attribute::POSITION] = location;

    ///a_color
    location = glGetAttribLocation(mProgramId, ATTRIBUTE_NAME_COLOR);
    mBuiltinAttributeLocation[Attribute::COLOR] = location;

    ///a_texCoord
    location = glGetAttribLocation(mProgramId, ATTRIBUTE_NAME_TEXCOORD);
    mBuiltinAttributeLocation[Attribute::TEXCOORD] = location;

    ///u_MVPMatrix
    location = glGetUniformLocation(mProgramId, UNIFORM_NAME_MVP_MATRIX);
    mBuiltinUniformLocation[Uniform::MVP_MATRIX].location[0] = location;
    mBuiltinUniformLocation[Uniform::MVP_MATRIX].location[1] = mActiveUniformInfos[UNIFORM_NAME_MVP_MATRIX].bufferOffset;

    ///u_textColor
    location = glGetUniformLocation(mProgramId, UNIFORM_NAME_TEXT_COLOR);
    mBuiltinUniformLocation[Uniform::TEXT_COLOR].location[0] = location;
    mBuiltinUniformLocation[Uniform::TEXT_COLOR].location[1] = mActiveUniformInfos[UNIFORM_NAME_TEXT_COLOR].bufferOffset;

    ///u_effectColor
    location = glGetUniformLocation(mProgramId, UNIFORM_NAME_EFFECT_COLOR);
    mBuiltinUniformLocation[Uniform::EFFECT_COLOR].location[0] = location;
    mBuiltinUniformLocation[Uniform::EFFECT_COLOR].location[1] = mActiveUniformInfos[UNIFORM_NAME_EFFECT_COLOR].bufferOffset;

    ///u_effectType
    location = glGetUniformLocation(mProgramId, UNIFORM_NAME_EFFECT_TYPE);
    mBuiltinUniformLocation[Uniform::EFFECT_TYPE].location[0] = location;
    mBuiltinUniformLocation[Uniform::EFFECT_TYPE].location[1] = mActiveUniformInfos[UNIFORM_NAME_EFFECT_TYPE].bufferOffset;

    ///u_texture
    location = glGetUniformLocation(mProgramId, UNIFORM_NAME_TEXTURE);
    mBuiltinUniformLocation[Uniform::TEXTURE].location[0] = location;

    ///u_texture1
    location = glGetUniformLocation(mProgramId, UNIFORM_NAME_TEXTURE1);
    mBuiltinUniformLocation[Uniform::TEXTURE1].location[0] = location;
}

NS_STITCHES_END