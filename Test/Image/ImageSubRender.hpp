
/**
 * ImageSubRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 0:51
 **/
#pragma once


#include "Stitches.hpp"
#include "Graphics/SubRender.hpp"

NS_STITCHES_BEGIN

class ImageSubRender : public SubRender
{
public:
    explicit ImageSubRender(SubRenderType type);
    ~ImageSubRender() override;
    void Render() override;

    RenderCommand* GetCommand() override;
    void Start() override;
private:

    TrianglesCommand command;
    TrianglesCommand::Triangles triangles;
    Matrix4 mat;
};

NS_STITCHES_END

