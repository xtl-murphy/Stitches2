/**
 * Engine
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/6/16 23:50
 **/

#include "Engine.hpp"
NS_STITCHES_BEGIN
Engine *Engine::Instance = nullptr;

Engine::Engine( bool emptyRegister) :
        fpsLimit(-1.0f),
        running(true),
        elapsedUpdate(15.77ms),
        elapsedRender(-1s) {
    Instance = this;

    if (!emptyRegister)
    {
        Window::Register();
    }
}

Engine::~Engine()
{
    Module::Registry().clear();
//    Log::CloseLog();
}

int32_t Engine::Run()
{
    while (running) {
//        if (app) {
//            if (!app->started) {
//                app->Start();
//                app->started = true;
//            }
//
//            app->Update();
//        }

        elapsedRender.SetInterval(Time::Seconds(1.0f / fpsLimit));

        // Always-Update.
        UpdateStage(Module::Stage::Always);
//
        if (elapsedUpdate.GetElapsed() != 0) {
            // Resets the timer.
            ups.Update(Time::Now());

            // Pre-Update.
            UpdateStage(Module::Stage::Pre);

            // Update.
            UpdateStage(Module::Stage::Normal);

            // Post-Update.
            UpdateStage(Module::Stage::Post);

            // Updates the engines delta.
            deltaUpdate.Update();
        }

        // Prioritize updates over rendering.
        if (!Maths::AlmostEqual(elapsedUpdate.GetInterval().AsSeconds(), deltaUpdate.change.AsSeconds(), 0.8f))
        {
        	continue;
        }

        // Renders when needed.
        if (elapsedRender.GetElapsed() != 0) {
            // Resets the timer.
            fps.Update(Time::Now());
//            LOGI("Engine", "fps %f", this->fpsLimit);
            // Render
            UpdateStage(Module::Stage::Render);

            // Updates the render delta, and render time extension.
            deltaRender.Update();
        }
    }

    return EXIT_SUCCESS;
}



void Engine::UpdateStage(Module::Stage stage)
{
    for (auto &[stageIndex, module] : Module::Registry())
    {
        if (stageIndex.first == stage)
            module->Update();
    }
}
NS_STITCHES_END
