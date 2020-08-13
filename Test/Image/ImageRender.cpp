
/**
 * ImageRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/8 22:50
 **/
#include "ImageRender.hpp"

USING_STITCHES_VK

ImageRender::ImageRender() : GraphicsRenderer()
{
    auto* program = Program::getBuiltinProgram(ProgramType::Normal_Image);
    auto programState = new ProgramState(program);
    command.getPipelineDescriptor().programState = programState;
}

ImageRender::~ImageRender()
{

}


void ImageRender::Start()
{
//    auto* program = backend::Device::getInstance()->newProgram(vert, frag);
//    auto programState = new (std::nothrow) backend::ProgramState(program);

}

void ImageRender::Update()
{

}

