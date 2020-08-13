
/**
 * Graphics
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 16:41
 **/
#pragma once


#include "Stitches.hpp"
#include "Utils/Module.hpp"
#include "Graphics/Base/CommandBuffer.hpp"
#include "GraphicsRenderer.hpp"

NS_STITCHES_BEGIN
class GraphicsRenderer;
class Graphics final : public Module::Registrar<Graphics, Module::Stage::Render>
{
public:
    Graphics();
    ~Graphics();

    void Update() override;

    GraphicsRenderer *GetRenderer() const { return renderer.get(); }
    void SetRenderer(std::unique_ptr<GraphicsRenderer> &&renderer) { this->renderer = std::move(renderer); }

private:
    bool StartRenderPass();
    void EndRenderPass();
private:
    std::unique_ptr<GraphicsRenderer> renderer;
    std::unique_ptr<CommandBuffer> commandBuffer;
};



NS_STITCHES_END