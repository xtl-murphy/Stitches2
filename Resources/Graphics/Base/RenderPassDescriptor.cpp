
/**
 * RenderPassDescriptor
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 17:33
 **/
#include "RenderPassDescriptor.hpp"

USING_STITCHES_VK

RenderPassDescriptor &RenderPassDescriptor::operator=(const RenderPassDescriptor &descriptor)
{
    this->clearDepthValue = descriptor.clearDepthValue;
    this->clearStencilValue = descriptor.clearStencilValue;
    this->clearColorValue = descriptor.clearColorValue;
    this->needColorAttachment = descriptor.needColorAttachment;
    this->depthTestEnabled = descriptor.depthTestEnabled;
    this->stencilTestEnabled = descriptor.stencilTestEnabled;
    this->needClearColor = descriptor.needClearColor;
    this->needClearDepth = descriptor.needClearDepth;
    this->needClearStencil = descriptor.needClearStencil;
//    depthAttachmentTexture = descriptor.depthAttachmentTexture;
//    stencilAttachmentTexture = descriptor.stencilAttachmentTexture;
//    colorAttachmentsTexture[0] = descriptor.colorAttachmentsTexture[0];

    return *this;
}

bool RenderPassDescriptor::operator==(const RenderPassDescriptor &descriptor) const
{
    return this->clearDepthValue == descriptor.clearDepthValue &&
            this->clearStencilValue == descriptor.clearStencilValue &&
            this->clearColorValue == descriptor.clearColorValue &&
            this->needColorAttachment == descriptor.needColorAttachment &&
            this->depthTestEnabled == descriptor.depthTestEnabled &&
            this->stencilTestEnabled == descriptor.stencilTestEnabled &&
            this->needClearColor == descriptor.needClearColor &&
            this->needClearDepth == descriptor.needClearDepth &&
            this->needClearStencil == descriptor.needClearStencil;
}
