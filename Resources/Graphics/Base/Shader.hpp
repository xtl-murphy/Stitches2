
/**
 * Shader
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:11
 **/

#pragma once

#include "Stitches.hpp"
#include "Types.hpp"
#include "ShaderCache.hpp"

NS_STITCHES_BEGIN

class Shader
{

public:
    Shader(const String& vs, const String& fs);

    /**
     * Get engine built-in program.
     * @param type Specifies the built-in program type.
     */
    static Shader* getBuiltinProgram(ShaderType type);

    virtual UniformLocation getUniformLocation(const String& uniform) const = 0;

    virtual UniformLocation getUniformLocation(Uniform name) const = 0;

    virtual int getAttributeLocation(const String& name) const =  0;

    virtual int getAttributeLocation(Attribute name) const =  0;

    virtual int getMaxVertexLocation() const = 0;

    virtual int getMaxFragmentLocation() const = 0;

    virtual const std::unordered_map<String, AttributeBindInfo> getActiveAttributes() const = 0;

    const String& getVertexShader() const { return mVertexShader; }

    const String& getFragmentShader() const { return mFragmentShader; }

protected:
    void setShaderType(ShaderType type);

    friend class ShaderCache;

    String mVertexShader;
    String mFragmentShader;
    ShaderType mShaderType = ShaderType::CUSTOM_PROGRAM;
};

NS_STITCHES_END