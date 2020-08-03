
/**
 * CommandBufferGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 17:45
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Base/CommandBuffer.hpp"

NS_STITCHES_BEGIN

class CommandBufferGL final : public CommandBuffer
{
private:
    Viewport viewport;
public:
    CommandBufferGL();
    ~CommandBufferGL();

    virtual void Begin(const RenderPassDescriptor& descriptor) override;
    virtual void End() override;
    virtual void SubmitIdle() override;
    virtual void Submit() override;
};

NS_STITCHES_END

