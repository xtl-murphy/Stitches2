
/**
 * Renderer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/4 23:37
 **/

#pragma once

#include <Graphics/Render/Renderer.hpp>
#include "Stitches.hpp"
#include "Graphics/SubRenderHolder.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/Base/Types.hpp"
#include "RenderState.hpp"
NS_STITCHES_BEGIN

class GraphicsRenderer
{
    friend class Graphics;
public:
    /**
     * Creates a new renderer, fill {@link renderStages} in your subclass of this.
     */
    GraphicsRenderer();

    virtual ~GraphicsRenderer() = default;

    virtual void Start() = 0;

    virtual void Update() = 0;

    void drawScene();


protected:


private:
    bool started = false;
    std::unique_ptr<Renderer> renderer;
};

NS_STITCHES_END

