
/**
 * ImageRender
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/8 22:50
 **/
#include "ImageRender.hpp"
#include "ImageSubRender.hpp"

USING_STITCHES_VK

ImageRender::ImageRender() : RenderContainer()
{
//    auto* program = Program::getBuiltinProgram(ProgramType::Normal_Image);
//    auto programState = new ProgramState(program);
//    command.getPipelineDescriptor().programState = programState;
//
//    _mvpMatrixLocation = command.getPipelineDescriptor().programState->getUniformLocation("u_MVPMatrix");
//    _textureLocation = command.getPipelineDescriptor().programState->getUniformLocation("u_texture");
//
//
//#define VERTEX_POSITION_SIZE 3
//#define VERTEX_TEXCOORD_SIZE 2
//    uint32_t texcoordOffset = (VERTEX_POSITION_SIZE)*sizeof(float);
//    uint32_t totalSize = (VERTEX_POSITION_SIZE+VERTEX_TEXCOORD_SIZE)*sizeof(float);
//
//    auto vertexLayout = programState->getVertexLayout();
//    const auto& attributeInfo = programState->getProgram()->getActiveAttributes();
//    auto iter = attributeInfo.find("a_position");
//    if(iter != attributeInfo.end())
//    {
//        vertexLayout->setAttribute("a_position", iter->second.location, VertexFormat::FLOAT3, 0, false);
//    }
//    iter = attributeInfo.find("a_texCoord");
//    if(iter != attributeInfo.end())
//    {
//        vertexLayout->setAttribute("a_texCoord", iter->second.location, VertexFormat::FLOAT2, texcoordOffset, false);
//    }
//    vertexLayout->setLayout(totalSize);

//    addCommand(&_groupCommand);
//    renderer->pushGroup(_groupCommand.getRenderQueueID());
}

ImageRender::~ImageRender()
{

}


void ImageRender::Start()
{
    auto imageSubRender = AddSubRender<ImageSubRender>(SubRenderType::Normal);


}

void ImageRender::Update()
{

}

