
/**
 * Graphics
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/2 16:41
 **/
#include "Graphics.hpp"

USING_STITCHES_VK

Graphics::Graphics()
{
    this->renderer = std::make_unique<Renderer>();
    this->renderer->init();
}

Graphics::~Graphics()
{

}

void Graphics::Update()
{
    if (!container->started)
    {
        container->Start();
        container->started = true;

        for (auto subRender : container->subRenders)
        {
            subRender->Start();
        }
    }
    container->Update();

    this->renderer->beginFrame();

    for (auto subRender : container->subRenders)
    {
        subRender->Render();
        this->renderer->addCommand(subRender->GetCommand());
    }

    this->renderer->render();

    this->renderer->endFrame();
}

