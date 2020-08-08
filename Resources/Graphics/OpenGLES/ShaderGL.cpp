
/**
 * ShaderGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:31
 **/
#include "ShaderGL.hpp"
#include "Graphics/Base/ShaderCache.hpp"

NS_STITCHES_BEGIN

ShaderGL::ShaderGL(const String &vertexShader, const String &fragmentShader)
: Shader(vertexShader, fragmentShader)
{
//    this->vertexShaderModule = ShaderCache::new
}

ShaderGL::~ShaderGL()
{

}

UniformLocation ShaderGL::getUniformLocation(const String &uniform) const
{
    return UniformLocation();
}

UniformLocation ShaderGL::getUniformLocation(Uniform name) const
{
    return UniformLocation();
}

int ShaderGL::getAttributeLocation(const String &name) const
{
    return 0;
}

int ShaderGL::getAttributeLocation(Attribute name) const
{
    return 0;
}

int ShaderGL::getMaxVertexLocation() const
{
    return 0;
}

int ShaderGL::getMaxFragmentLocation() const
{
    return 0;
}

const std::unordered_map<String, AttributeBindInfo> ShaderGL::getActiveAttributes() const
{
    return std::unordered_map<std::string, AttributeBindInfo>();
}

void ShaderGL::compileProgram()
{

}

bool ShaderGL::getAttributeLocation(const String &attributeName, unsigned int &location) const
{
    return false;
}

void ShaderGL::computeUniformInfos()
{

}

void ShaderGL::computeLocations()
{

}


NS_STITCHES_END