
/**
 * ProgramState
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 1:45
 **/
#include "ProgramState.hpp"

NS_STITCHES_BEGIN
#define MAT3_SIZE 36
#define MAT4X3_SIZE 48
#define VEC3_SIZE 12
#define VEC4_SIZE 16
#define BVEC3_SIZE 3
#define BVEC4_SIZE 4
#define IVEC3_SIZE 12
#define IVEC4_SIZE 16

    void convertbVec3TobVec4(const bool* src, bool* dst)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = false;
    }

    void convertiVec3ToiVec4(const int* src, int* dst)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = 0;
    }

    void convertVec3ToVec4(const float* src, float* dst)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = 0.0f;
    }

    void convertMat3ToMat4x3(const float* src, float* dst)
    {
        dst[3] = dst[7] = dst[11] = 0.0f;
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
        dst[4] = src[3]; dst[5] = src[4]; dst[6] = src[5];
        dst[8] = src[6]; dst[9] = src[7]; dst[10] = src[8];
    }

//static field
std::vector<ProgramState::AutoBindingResolver*> ProgramState::mCustomAutoBindingResolvers;

TextureInfo::TextureInfo(const std::vector<uint32_t>& _slots, const std::vector<TextureBackend*> _textures)
        : slot(_slots)
        , textures(_textures)
{
    retainTextures();
}

TextureInfo::TextureInfo(const TextureInfo &other)
        : slot(other.slot)
        , textures(other.textures)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, location(other.location)
#endif
{
    retainTextures();
}

TextureInfo::~TextureInfo()
{
    releaseTextures();
}

void TextureInfo::retainTextures()
{
    for (auto& texture : textures)
        SAFE_RETAIN(texture);
}

void TextureInfo::releaseTextures()
{
    for (auto& texture : textures)
        SAFE_RELEASE(texture);
}

TextureInfo& TextureInfo::operator=(TextureInfo&& rhs)
{
    if (this != &rhs)
    {
        slot = rhs.slot;

        rhs.retainTextures();
        releaseTextures();
        textures = rhs.textures;

        //release the textures before cleaning the vertor
        rhs.releaseTextures();
        rhs.textures.clear();

    }
    return *this;
}

TextureInfo& TextureInfo::operator=(const TextureInfo& rhs)
{
    if (this != &rhs)
    {
        slot = rhs.slot;
        textures = rhs.textures;
        retainTextures();

    }
    return *this;
}

ProgramState::ProgramState(Program* program)
{
    init(program);
}

bool ProgramState::init(Program* program)
{
    SAFE_RETAIN(program);
    mProgram = program;
    mVertexUniformBufferSize = mProgram->getUniformBufferSize(ShaderStage::VERTEX);
    mVertexUniformBuffer = new char[mVertexUniformBufferSize];
    memset(mVertexUniformBuffer, 0, mVertexUniformBufferSize);
    return true;
}

void ProgramState::resetUniforms()
{

}

ProgramState::ProgramState()
{
}

ProgramState::~ProgramState()
{
    SAFE_RELEASE(mProgram);
    SAFE_DELETE_ARRAY(mVertexUniformBuffer);
    SAFE_DELETE_ARRAY(mFragmentUniformBuffer);
}

ProgramState *ProgramState::clone() const
{
    ProgramState *cp = new ProgramState();
    cp->mProgram = mProgram;
    cp->mVertexUniformBufferSize = mVertexUniformBufferSize;
    cp->mFragmentUniformBufferSize = mFragmentUniformBufferSize;
    cp->mVertexTextureInfos = mVertexTextureInfos;
    cp->mFragmentTextureInfos = mFragmentTextureInfos;
    cp->mVertexUniformBuffer = new char[mVertexUniformBufferSize];
    memcpy(cp->mVertexUniformBuffer, mVertexUniformBuffer, mVertexUniformBufferSize);
    cp->mVertexLayout = mVertexLayout;
    return cp;
}

UniformLocation ProgramState::getUniformLocation(Uniform name) const
{
    return mProgram->getUniformLocation(name);
}

UniformLocation ProgramState::getUniformLocation(const std::string& uniform) const
{
    return mProgram->getUniformLocation(uniform);
}

void ProgramState::setCallbackUniform(const UniformLocation& uniformLocation,const UniformCallback& callback)
{
    mCallbackUniforms[uniformLocation] = callback;
}

void ProgramState::setUniform(const UniformLocation& uniformLocation, const void* data, std::size_t size)
{
    switch (uniformLocation.shaderStage)
    {
        case ShaderStage::VERTEX:
            setVertexUniform(uniformLocation.location[0], data, size, uniformLocation.location[1]);
            break;
        case ShaderStage::FRAGMENT:
            setFragmentUniform(uniformLocation.location[1], data, size);
            break;
        case ShaderStage::VERTEX_AND_FRAGMENT:
            setVertexUniform(uniformLocation.location[0], data, size, uniformLocation.location[1]);
            setFragmentUniform(uniformLocation.location[1], data, size);
            break;
        default:
            break;
    }
}

#ifdef CC_USE_METAL
void ProgramState::convertAndCopyUniformData(const UniformInfo& uniformInfo, const void* srcData, std::size_t srcSize, void* buffer)
{
    auto basicType = static_cast<glslopt_basic_type>(uniformInfo.type);
    char* convertedData = new char[uniformInfo.size];
    memset(convertedData, 0, uniformInfo.size);
    int offset = 0;
    switch (basicType)
    {
        case kGlslTypeFloat:
        {
            if(uniformInfo.isMatrix)
            {
                for (int i=0; i<uniformInfo.count; i++)
                {
                    if(offset >= srcSize)
                        break;

                    convertMat3ToMat4x3((float*)srcData + offset, (float*)convertedData + i * MAT4X3_SIZE);
                    offset += MAT3_SIZE;
                }
            }
            else
            {
                for (int i=0; i<uniformInfo.count; i++)
                {
                    if(offset >= srcSize)
                        break;

                    convertVec3ToVec4((float*)srcData +offset, (float*)convertedData + i * VEC4_SIZE);
                    offset += VEC3_SIZE;
                }
            }
            break;
        }
        case kGlslTypeBool:
        {
            for (int i=0; i<uniformInfo.count; i++)
            {
                if(offset >= srcSize)
                    break;

                convertbVec3TobVec4((bool*)srcData + offset, (bool*)convertedData + i * BVEC4_SIZE);
                offset += BVEC3_SIZE;
            }
            break;
        }
        case kGlslTypeInt:
        {
            for (int i=0; i<uniformInfo.count; i++)
            {
                if(offset >= srcSize)
                    break;

                convertiVec3ToiVec4((int*)srcData + offset, (int*)convertedData + i * IVEC4_SIZE);
                offset += IVEC3_SIZE;
            }
            break;
        }
        default:
            CC_ASSERT(false);
            break;
    }

    memcpy((char*)buffer + uniformInfo.location, convertedData, uniformInfo.size);
    CC_SAFE_DELETE_ARRAY(convertedData);
}
#endif

void ProgramState::setVertexUniform(int location, const void* data, std::size_t size, std::size_t offset)
{
    if(location < 0)
        return;

    memcpy(mVertexUniformBuffer + offset, data, size);
}

void ProgramState::setFragmentUniform(int location, const void* data, std::size_t size)
{
    if(location < 0)
        return;
}

void ProgramState::setTexture(const UniformLocation& uniformLocation, uint32_t slot, TextureBackend* texture)
{
    switch (uniformLocation.shaderStage)
    {
        case ShaderStage::VERTEX:
            setTexture(uniformLocation.location[0], slot, texture, mVertexTextureInfos);
            break;
        case ShaderStage::FRAGMENT:
            setTexture(uniformLocation.location[1], slot, texture, mFragmentTextureInfos);
            break;
        case ShaderStage::VERTEX_AND_FRAGMENT:
            setTexture(uniformLocation.location[0], slot, texture, mVertexTextureInfos);
            setTexture(uniformLocation.location[1], slot, texture, mFragmentTextureInfos);
            break;
        default:
            break;
    }
}

void ProgramState::setTextureArray(const UniformLocation& uniformLocation, const std::vector<uint32_t>& slots, const std::vector<TextureBackend*> textures)
{
    switch (uniformLocation.shaderStage)
    {
        case ShaderStage::VERTEX:
            setTextureArray(uniformLocation.location[0], slots, textures, mVertexTextureInfos);
            break;
        case ShaderStage::FRAGMENT:
            setTextureArray(uniformLocation.location[1], slots, textures, mFragmentTextureInfos);
            break;
        case ShaderStage::VERTEX_AND_FRAGMENT:
            setTextureArray(uniformLocation.location[0], slots, textures, mVertexTextureInfos);
            setTextureArray(uniformLocation.location[1], slots, textures, mFragmentTextureInfos);
            break;
        default:
            break;
    }
}

void ProgramState::setTexture(int location, uint32_t slot, TextureBackend* texture, std::unordered_map<int, TextureInfo>& textureInfo)
{
    if(location < 0)
        return;
    TextureInfo& info = textureInfo[location];
    info.releaseTextures();
    info.slot = {slot};
    info.textures = {texture};
    info.retainTextures();
}

void ProgramState::setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<TextureBackend*> textures, std::unordered_map<int, TextureInfo>& textureInfo)
{

    TextureInfo& info = textureInfo[location];
    info.releaseTextures();
    info.slot = slots;
    info.textures = textures;
    info.retainTextures();

}

void ProgramState::setParameterAutoBinding(const std::string &uniform, const std::string &autoBinding)
{
    mAutoBindings.emplace(uniform, autoBinding);
    applyAutoBinding(uniform, autoBinding);
}

void ProgramState::applyAutoBinding(const std::string &uniformName, const std::string &autoBinding)
{
    bool resolved = false;
    for (const auto resolver : mCustomAutoBindingResolvers)
    {
        resolved = resolver->resolveAutoBinding(this, uniformName, autoBinding);
        if (resolved) break;
    }
}

ProgramState::AutoBindingResolver::AutoBindingResolver()
{
    mCustomAutoBindingResolvers.emplace_back(this);
}

ProgramState::AutoBindingResolver::~AutoBindingResolver()
{
    auto &list = mCustomAutoBindingResolvers;
    list.erase(std::remove(list.begin(), list.end(), this), list.end());
}

void ProgramState::getVertexUniformBuffer(char** buffer, std::size_t& size) const
{
    *buffer = mVertexUniformBuffer;
    size = mVertexUniformBufferSize;
}

void ProgramState::getFragmentUniformBuffer(char** buffer, std::size_t& size) const
{
    *buffer = mFragmentUniformBuffer;
    size = mFragmentUniformBufferSize;
}

NS_STITCHES_END