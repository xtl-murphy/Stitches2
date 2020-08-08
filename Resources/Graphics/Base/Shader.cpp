
/**
 * Shader
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:11
 **/

#include "Shader.hpp"

NS_STITCHES_BEGIN

Shader::Shader(const String& vs, const String& fs)
        : mVertexShader(vs)
        , mFragmentShader(fs)
{
}

void Shader::setShaderType(ShaderType type)
{
    mShaderType = type;
}

Shader* Shader::getBuiltinProgram(ShaderType type)
{
    return ShaderCache::getInstance()->getBuiltinShader(type);
}

NS_STITCHES_END