
/**
 * RenderPassDescriptor
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 17:33
 **/
#pragma once

#include "Stitches.hpp"
#include "Types.hpp"
#include "ProgramState.hpp"

NS_STITCHES_BEGIN

struct RenderPassDescriptor
{
    float clearDepthValue = 0.f;
    float clearStencilValue = 0.f;
    std::array<float, 4> clearColorValue {{0.f, 0.f, 0.f, 0.f}}; // double-braces required in C++11
    bool needColorAttachment = true;
    bool depthTestEnabled = false;
    bool stencilTestEnabled = false;
    bool needClearColor = false;
    bool needClearDepth = false;
    bool needClearStencil = false;

    TextureBackend* depthAttachmentTexture = nullptr;
    TextureBackend* stencilAttachmentTexture = nullptr;
    TextureBackend* colorAttachmentsTexture[MAX_COLOR_ATTCHMENT] = { nullptr };

    RenderPassDescriptor& operator=(const RenderPassDescriptor& descriptor);
    bool operator==(const RenderPassDescriptor& descriptor) const;
};

struct PipelineDescriptor
{
    ProgramState* programState = nullptr;
//    BlendState* blendState = nullptr;
    PixelFormat colorAttachmentsFormat[MAX_COLOR_ATTCHMENT] = { PixelFormat::DEFAULT };
    PixelFormat depthAttachmentFormat = PixelFormat::NONE;
    PixelFormat stencilAttachmentFormat = PixelFormat::NONE;
};

NS_STITCHES_END

