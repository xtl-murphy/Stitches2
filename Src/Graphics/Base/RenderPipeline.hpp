
/**
 * RenderPipeline
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/8 0:51
 **/
#pragma once

#include "Stitches.hpp"
#include "RenderPassDescriptor.hpp"

NS_STITCHES_BEGIN

class RenderPipeline : public Ref
{
public:
    virtual void update(const PipelineDescriptor & pipelineDescirptor, const RenderPassDescriptor& renderpassDescriptor) = 0;

protected:
    virtual ~RenderPipeline() = default;
};

NS_STITCHES_END

