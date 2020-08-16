
/**
 * ImageSubRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 0:51
 **/
#include "ImageSubRender.hpp"

NS_STITCHES_BEGIN

ImageSubRender::ImageSubRender(SubRenderType type) : SubRender(type)
{

    triangles.verts = nullptr;
    triangles.indices = nullptr;
    triangles.vertCount = 0;
    triangles.indexCount = 0;

    this->command.init(0, nullptr, BlendFunc::DISABLE, this->triangles, this->mat, 0);

}

ImageSubRender::~ImageSubRender()
{

}

void ImageSubRender::Render()
{

}

RenderCommand *ImageSubRender::GetCommand()
{
    return &this->command;
}

void ImageSubRender::Start()
{
    auto* program = Program::getBuiltinProgram(ProgramType::Normal_Image);
    auto programState = new ProgramState(program);
    command.getPipelineDescriptor().programState = programState;

}

NS_STITCHES_END


