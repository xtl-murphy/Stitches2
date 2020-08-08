
/**
 * RenderPipelineGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/6 23:16
 **/
#include "RenderPipelineGL.hpp"
#include "UtilsGL.hpp"

NS_STITCHES_BEGIN

void RenderPipelineGL::update(const Stitches::PipelineDescriptor &pipelineDescriptor,
                                        const Stitches::RenderPassDescriptor &renderPassDescriptor)
{
//    this->updateBlendState(pipelineDescriptor.blendDescriptor);
}

void RenderPipelineGL::updateBlendState(const BlendDescriptor &descriptor)
{
    auto blendEnabled = descriptor.blendEnabled;
    auto rgbBlendOperation = UtilsGL::toGLBlendOperation(descriptor.rgbBlendOperation);
    auto alphaBlendOperation = UtilsGL::toGLBlendOperation(descriptor.alphaBlendOperation);
    auto sourceRGBBlendFactor = UtilsGL::toGLBlendFactor(descriptor.sourceRGBBlendFactor);
    auto destinationRGBBlendFactor = UtilsGL::toGLBlendFactor(descriptor.destinationRGBBlendFactor);
    auto sourceAlphaBlendFactor = UtilsGL::toGLBlendFactor(descriptor.sourceAlphaBlendFactor);
    auto destinationAlphaBlendFactor = UtilsGL::toGLBlendFactor(descriptor.destinationAlphaBlendFactor);
    auto writeMaskRed = (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::RED;
    auto writeMaskGreen = (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::GREEN;
    auto writeMaskBlue = (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::BLUE;
    auto writeMaskAlpha = (uint32_t)descriptor.writeMask & (uint32_t)ColorWriteMask::ALPHA;

    if (blendEnabled)
    {
        glEnable(GL_BLEND);
        glBlendEquationSeparate(rgbBlendOperation, alphaBlendOperation);
        glBlendFuncSeparate(sourceRGBBlendFactor,
                            destinationRGBBlendFactor,
                            sourceAlphaBlendFactor,
                            destinationAlphaBlendFactor);
    }
    else
        glDisable(GL_BLEND);

    glColorMask(writeMaskRed, writeMaskGreen, writeMaskBlue, writeMaskAlpha);
}

NS_STITCHES_END