
/**
 * ImageRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/8 22:50
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Renderer.hpp"
NS_STITCHES_BEGIN

class ImageRender : public Renderer
{
public:
    ImageRender();

    void Start() override;
    void Update() override;
};

NS_STITCHES_END

