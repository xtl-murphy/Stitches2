
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


NS_STITCHES_END