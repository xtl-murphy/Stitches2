
/**
 * ShaderModuleGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 11:43
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Platform.hpp"
#include "Graphics/Base/ShaderModule.hpp"

NS_STITCHES_BEGIN

class ShaderModuleGL : public ShaderModule
{
    friend class ShaderGL;
private:
    GLuint shaderId;

private:
    void compileShader(ShaderStage stage, const String& source);
    char* getErrorLog(GLuint shader) const;
    void deleteShader();
public:
    ShaderModuleGL(ShaderStage stage, const String& source);
    ~ShaderModuleGL();
};

NS_STITCHES_END

