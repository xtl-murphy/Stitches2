
/**
 * Renderer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:37
 **/

#include "GraphicsRenderer.hpp"

NS_STITCHES_BEGIN

GraphicsRenderer::GraphicsRenderer()
{
    this->renderer = std::make_unique<Renderer>();
    this->renderer->init();
}

void GraphicsRenderer::drawScene()
{
    this->renderer->beginFrame();
    this->renderer->render();
    this->renderer->endFrame();
}



NS_STITCHES_END