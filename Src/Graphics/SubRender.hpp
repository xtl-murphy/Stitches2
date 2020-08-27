
/**
 * SubRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 18:20
 **/

#pragma once

#include "Stitches.hpp"
#include "RenderContainer.hpp"
#include "Utils/TypeInfo.hpp"
#include "Graphics/Command/RenderCommand.hpp"

NS_STITCHES_BEGIN

enum class SubRenderType
{
    Normal = 0
};

class SubRender
{
public:

    explicit SubRender(SubRenderType type) : type(type)
    { }

    virtual ~SubRender() = default;

    /**
     * Runs the render pipeline in the current renderpass.
     * @param commandBuffer The command buffer to record render command into.
     */
    virtual void Render() = 0;

    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool enable) { this->enabled = enable; }

    virtual void Start() = 0;
    virtual RenderCommand* GetCommand() = 0;

protected:
    bool enabled = true;
    SubRenderType type;
};


NS_STITCHES_END
