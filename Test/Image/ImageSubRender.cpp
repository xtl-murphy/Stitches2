
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
    this->updateTexture();
    this->initProgram();

    //create vertex buffer
    command.setDrawType(CustomCommand::DrawType::ARRAY);
    command.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE_STRIP);
    command.createVertexBuffer(4 * sizeof(float), 4, CustomCommand::BufferUsage::DYNAMIC);

    const std::vector<V3F_C4B_T2F> vertices =
    {
            {{-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {0.0f, 1.0f}},
            {{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {1.0f, 1.0f}},
            {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {0.0f, 0.0f}}
    };





//    command.init(0, tex, BlendFunc::DISABLE, this->triangles, this->mat, 0);
    command.init(0);
//    command.updateVertexBuffer()
    command.func = [=]() -> void {
        Graphics::Get()->GetRenderer()->setViewPort(0, 0, 1080, 720);
    };
}

void ImageSubRender::updateTexture()
{
    TextureDescriptor descriptor;
    Bitmap bitmap("texture.jpg");
    descriptor.width = bitmap.GetSize().x;
    descriptor.height = bitmap.GetSize().y;
    tex = new Texture2DGL(descriptor);
    tex->updateWithBitmap(&bitmap);
}

void ImageSubRender::initProgram()
{
    auto* program = Program::getBuiltinProgram(ProgramType::Normal_Image);
    programState = new ProgramState(program);
    command.getPipelineDescriptor().programState = programState;

    _mvpMatrixLocation = programState->getUniformLocation("u_MVPMatrix");
    _textureLocation = programState->getUniformLocation("u_texture");

    auto vertexLayout = programState->getVertexLayout();
    auto& attributes = programState->getProgram()->getActiveAttributes();
    auto iter = attributes.find("a_position");
    if(iter != attributes.end())
        vertexLayout->setAttribute("a_position", iter->second.location, VertexFormat::FLOAT2, 0, false);

    iter = attributes.find("a_texCoord");
    if(iter != attributes.end())
        vertexLayout->setAttribute("a_texCoord", iter->second.location, VertexFormat::FLOAT2, 2 * sizeof(float), false);

    vertexLayout->setLayout(4 * sizeof(float));

    programState->setTexture(_textureLocation, 0, tex);

    programState->setUniform(_mvpMatrixLocation, this->mat.rows, sizeof(this->mat.rows));
}

NS_STITCHES_END


