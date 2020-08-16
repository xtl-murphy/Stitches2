
/**
 * ShaderModuleGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 11:43
 **/
#include "ShaderModuleGL.hpp"

NS_STITCHES_BEGIN

ShaderModuleGL::ShaderModuleGL(ShaderStage stage, const String &source)
        : ShaderModule(stage)
{
    this->compileShader(stage, source);
 }

ShaderModuleGL::~ShaderModuleGL()
{
    deleteShader();
}

void ShaderModuleGL::compileShader(ShaderStage stage, const String &source)
{
    GLenum shaderType = stage == ShaderStage::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    const GLchar* sourcePtr = reinterpret_cast<const GLchar*>(source.c_str());
    mShaderId = glCreateShader(shaderType);
    if (!mShaderId)
        return;

    glShaderSource(mShaderId, 1, &sourcePtr, nullptr);
    glCompileShader(mShaderId);

    GLint status = 0;
    glGetShaderiv(mShaderId, GL_COMPILE_STATUS, &status);
    if (! status)
    {
        LOGE("OpenGLES", "compileShader Error : %s", getErrorLog(mShaderId));
        deleteShader();
    }
}

void ShaderModuleGL::deleteShader()
{
    if (mShaderId)
    {
        glDeleteShader(mShaderId);
        mShaderId = 0;
    }
}

char *ShaderModuleGL::getErrorLog(GLuint shader) const
{
    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    char* log = (char*)malloc(sizeof(char) * logLength);
    glGetShaderInfoLog(shader, logLength, nullptr, log);
    return log;
}


NS_STITCHES_END