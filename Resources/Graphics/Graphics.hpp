
/**
 * Graphics
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 16:41
 **/
#pragma once


#include "Stitches.hpp"
#include "Graphics/Render/Renderer.hpp"
#include "Graphics/Base/CommandBuffer.hpp"
#include "Utils/Module.hpp"
#include "RenderContainer.hpp"

NS_STITCHES_BEGIN
class RenderContainer;
class Graphics final : public Module::Registrar<Graphics, Module::Stage::Render>
{
public:
    Graphics();
    ~Graphics();

    void Update() override;

    Renderer *GetRenderer() const { return renderer.get(); }
    void SetRenderer(std::unique_ptr<RenderContainer> &&container) { this->container = std::move(container); }

private:

private:
    std::unique_ptr<RenderContainer> container;
    std::unique_ptr<Renderer> renderer;
};



NS_STITCHES_END
