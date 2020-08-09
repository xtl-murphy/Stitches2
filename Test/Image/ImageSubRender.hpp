
/**
 * ImageSubRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 0:51
 **/
#pragma once


#include "Stitches.hpp"
#include "Graphics/SubRender.hpp"
#include "Graphics/OpenGLES/RenderPipelineGL.hpp"

NS_STITCHES_BEGIN

class ImageSubRender : public SubRender
{
public:
    virtual void Render(const CommandBuffer &commandBuffer) override ;

private:
};

NS_STITCHES_END

