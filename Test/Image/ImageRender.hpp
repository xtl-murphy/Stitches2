
/**
 * ImageRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/8 22:50
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/GraphicsRenderer.hpp"
NS_STITCHES_BEGIN

class ImageRender : public GraphicsRenderer
{
public:
    ImageRender();
    ~ImageRender() override;
    void Start() override;
    void Update() override;

private:
    TrianglesCommand command;
};

NS_STITCHES_END

