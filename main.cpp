
#include "Engine/Engine.hpp"
#include "Test/Image/ImageRender.hpp"

USING_STITCHES_VK

int main(int argc, char **argv)
{
    auto engine = std::make_unique<Engine>();
    Graphics::Get()->SetRenderer(std::make_unique<ImageRender>());
    engine->Run();
    return 0;
}