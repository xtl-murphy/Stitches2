
#include "Engine/Engine.hpp"

USING_STITCHES_VK

int main(int argc, char **argv)
{
    printf("", "");
    auto engine = std::make_unique<Engine>();
    engine->Run();
    return 0;
}