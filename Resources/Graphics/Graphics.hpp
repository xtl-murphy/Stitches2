//
// Created by Murphy on 2020/8/2.
//

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
#include "OpenGLES/Renderer.hpp"
NS_STITCHES_BEGIN
class Renderer;
class Graphics final : public Module::Registrar<Graphics, Module::Stage::Render>
{
public:
    Graphics();
    ~Graphics();

    void Update() override;

    Renderer *GetRenderer() const { return renderer.get(); }
    void SetRenderer(std::unique_ptr<Renderer> &&renderer) { this->renderer = std::move(renderer); }
private:
    std::unique_ptr<Renderer> renderer;
};

NS_STITCHES_END

