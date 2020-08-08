
/**
 * CommandBuffer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 17:01
 **/
#pragma once

#include "Stitches.hpp"
#include "RenderPassDescriptor.hpp"
#include "Types.hpp"
#include "Buffer.hpp"
#include "DepthStencilState.hpp"
#include "RenderPipeline.hpp"

NS_STITCHES_BEGIN

struct Viewport
{
    int32 x = 0;
    int32 y = 0;
    uint32 w = 0;
    uint32 h = 0;
};

class CommandBuffer
{

public:
    using Stage = std::pair<uint32_t, uint32_t>;


    virtual void beginFrame() = 0;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) = 0;
    virtual void endRenderPass() = 0;
    virtual void endFrame() = 0;

    virtual void setRenderPipeline(RenderPipeline* renderPipeline) = 0;

    virtual void setViewport(int x, int y, unsigned int w, unsigned int h) = 0;
    virtual void setCullMode(CullMode mode) = 0;
    virtual void setWinding(Winding winding) = 0;
    virtual void setVertexBuffer(Buffer* buffer) = 0;
    virtual void setIndexBuffer(Buffer* buffer) = 0;
    virtual void setLineWidth(float lineWidth) = 0;
//    virtual void setProgramState(ProgramState* programState) = 0;
    virtual void drawArrays(PrimitiveType primitiveType, std::size_t start,  std::size_t count) = 0;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, std::size_t count, std::size_t offset) = 0;

    virtual void setScissorRect(bool isEnabled, float x, float y, float width, float height) = 0;
    virtual void setDepthStencilState(DepthStencilState* depthStencilState) = 0;
    void setStencilReferenceValue(unsigned int value);
    void setStencilReferenceValue(unsigned int frontRef, unsigned int backRef);
    virtual void captureScreen(std::function<void(const unsigned char*, int, int)> callback) = 0;


    virtual ~CommandBuffer() = default;

private:

    bool running = false;
    unsigned int stencilReferenceValueFront = 0;
    unsigned int stencilReferenceValueBack = 0;
};

NS_STITCHES_END

