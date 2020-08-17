
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
    auto* program = Program::getBuiltinProgram(ProgramType::Normal_Image);
    auto programState = new ProgramState(program);
    command.getPipelineDescriptor().programState = programState;

    TextureDescriptor descriptor;
    Bitmap bitmap("");
    descriptor.width = bitmap.GetSize().x;
    descriptor.height = bitmap.GetSize().y;
    tex = new Texture2DGL(descriptor);
    tex->updateWithBitmap(&bitmap);


    const std::vector<V3F_C4B_T2F> vertices =
    {
            {{-1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {0.0f, 1.0f}},
            {{1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {1.0f, 1.0f}},
            {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0F}, {0.0f, 0.0f}}
    };

    this->triangles.vertCount = 4;
    this->triangles.verts = new V3F_C4B_T2F[4];

    for (int i = 0; i < 4; ++i)
    {
        this->triangles.verts[i] = vertices[i];
    }

    this->triangles.indexCount = 6;
    this->triangles.indices = new unsigned short[6]{0, 1, 2, 2, 3, 0};



    command.init(0, tex, BlendFunc::DISABLE, this->triangles, this->mat, 0);
}

NS_STITCHES_END


