
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
#include "BufferGL.hpp"
#include "RenderPipelineGL.hpp"

NS_STITCHES_BEGIN

class CommandBufferGL final : public CommandBuffer
{
private:
    void applyRenderPassDescriptor(const RenderPassDescriptor& descirptor);

public:
    CommandBufferGL();
    ~CommandBufferGL();

    void beginFrame() override ;
    void beginRenderPass(const RenderPassDescriptor& descriptor) override;
    void endRenderPass() override;
    void endFrame() override;

    void setRenderPipeline(RenderPipeline* renderPipeline) override;

    void setViewport(int x, int y, unsigned int w, unsigned int h) override;
    void setCullMode(CullMode mode) override;
    void setWinding(Winding winding) override;
    void setVertexBuffer(Buffer* buffer) override;
    void setIndexBuffer(Buffer* buffer) override;
    void setLineWidth(float lineWidth) override;
//    virtual void setProgramState(ProgramState* programState) override;
    void drawArrays(PrimitiveType primitiveType, std::size_t start,  std::size_t count) override;
    void drawElements(PrimitiveType primitiveType, IndexFormat indexType, std::size_t count, std::size_t offset) override;

    void setScissorRect(bool isEnabled, float x, float y, float width, float height) override;
    void setDepthStencilState(DepthStencilState* depthStencilState) override;
    void captureScreen(std::function<void(const unsigned char*, int, int)> callback) override;
private:

    void prepareDrawing();
    void bindVertexBuffer(ShaderGL* program) const;
    void setUniforms(ShaderGL* program) const;
    void setUniform(bool isArray, GLuint location, unsigned int size, GLenum uniformType, void* data) const;

    RenderPipelineGL* mRenderPipeline = nullptr;
    Viewport mViewport;
    CullMode mCullMode = CullMode::NONE;
    BufferGL* mVertexBuffer = nullptr;
    BufferGL* mIndexBuffer = nullptr;
};

NS_STITCHES_END

