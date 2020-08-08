
/**
 * ShaderModule
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:35
 **/
#pragma once

#include "Stitches.hpp"
#include "Types.hpp"
NS_STITCHES_BEGIN

enum Uniform : uint32_t
{
    MVP_MATRIX,
    TEXTURE,
    TEXTURE1,
    TEXTURE2,
    TEXTURE3,
    TEXT_COLOR,
    EFFECT_TYPE,
    EFFECT_COLOR,
    UNIFORM_MAX //Maximum uniforms
};

enum Attribute : uint32_t
{
    POSITION,
    COLOR,
    TEXCOORD,
    TEXCOORD1,
    TEXCOORD2,
    TEXCOORD3,
    ATTRIBUTE_MAX //Maximum attributes
};

class ShaderModule
{
public:
    /**
     * Get shader stage. The symbolic constant can be either VERTEX or FRAGMENT.
     * @return Shader stage.
     */
    ShaderStage getShaderStage() const;

    std::size_t getHashValue() const { return hash; }

protected:
    ShaderModule(ShaderStage stage);
    virtual ~ShaderModule();
    void setHashValue(std::size_t hash) { hash = hash; }

    friend class ShaderCache;
    ShaderStage stage = ShaderStage::VERTEX;
    std::size_t hash = 0;
};

NS_STITCHES_END

