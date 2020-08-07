
/**
 * RenderPipelineGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/6 23:16
 **/
#include "RenderPipelineGL.hpp"

NS_STITCHES_BEGIN

void RenderPipelineGL::update(const Stitches::PipelineDescriptor &pipelineDescirptor,
                                        const Stitches::RenderPassDescriptor &renderpassDescriptor)
{
    this->updateBlendState(pipelineDescirptor.blendDescriptor);
}

NS_STITCHES_END