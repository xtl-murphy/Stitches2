
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

}

Graphics::~Graphics()
{

}

void Graphics::Update()
{
    if (!renderer->started)
    {
        renderer->Start();
        renderer->started = true;
    }

    renderer->Update();


}

bool Graphics::StartRenderPass()
{
    return false;
}

void Graphics::EndRenderPass()
{

}
