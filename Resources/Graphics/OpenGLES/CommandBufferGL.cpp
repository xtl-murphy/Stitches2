
/**
 * CommandBufferGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 17:45
 **/
#include "CommandBufferGL.hpp"
#include "Graphics/Platform.hpp"
#include "UtilsGL.hpp"

USING_STITCHES_VK

CommandBufferGL::CommandBufferGL()
{

}

CommandBufferGL::~CommandBufferGL()
{

}

void CommandBufferGL::beginFrame()
{

}

void CommandBufferGL::beginRenderPass(const RenderPassDescriptor &descriptor)
{
    this->applyRenderPassDescriptor(descriptor);
}

void CommandBufferGL::applyRenderPassDescriptor(const RenderPassDescriptor &descirptor)
{
//    bool useColorAttachmentExternal = descirptor.needColorAttachment && descirptor.colorAttachmentsTexture[0];
//    bool useDepthAttachmentExternal = descirptor.depthTestEnabled && descirptor.depthAttachmentTexture;
//    bool useStencilAttachmentExternal = descirptor.stencilTestEnabled && descirptor.stencilAttachmentTexture;
    bool useGeneratedFBO = false;
}

void CommandBufferGL::endRenderPass()
{

}

void CommandBufferGL::endFrame()
{

}

void CommandBufferGL::setRenderPipeline(RenderPipeline *renderPipeline)
{
    if (renderPipeline == nullptr)
        return;

    auto* rp = dynamic_cast<RenderPipelineGL*>(renderPipeline);
    this->mRenderPipeline = rp;
}


void CommandBufferGL::setViewport(int x, int y, unsigned int w, unsigned int h)
{
    glViewport(x, y, w, h);
    this->mViewport.x = x;
    this->mViewport.y = y;
    this->mViewport.w = w;
    this->mViewport.h = h;
}

void CommandBufferGL::setCullMode(CullMode mode)
{
    this->mCullMode = mode;
}

void CommandBufferGL::setWinding(Winding winding)
{
    glFrontFace(UtilsGL::toGLFrontFace(winding));
}

void CommandBufferGL::setVertexBuffer(Buffer *buffer)
{
    if (buffer == nullptr)
    {
        return;
    }
//    buffer->retain();
    this->mVertexBuffer = dynamic_cast<BufferGL*>(buffer);
}

void CommandBufferGL::setIndexBuffer(Buffer *buffer)
{
    if (buffer == nullptr)
        return;

//    buffer->retain();
//    CC_SAFE_RELEASE(_indexBuffer);
    mIndexBuffer = static_cast<BufferGL*>(buffer);
}

void CommandBufferGL::setLineWidth(float lineWidth)
{
    if(lineWidth > 0.0f)
    {
        glLineWidth(lineWidth);
    }
    else
    {
        glLineWidth(1.0f);
    }
}

void CommandBufferGL::drawArrays(PrimitiveType primitiveType, std::size_t start, std::size_t count)
{
    prepareDrawing();
    glDrawArrays(UtilsGL::toGLPrimitiveType(primitiveType), start, count);
}

void
CommandBufferGL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, std::size_t count,
                              std::size_t offset)
{
    prepareDrawing();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->getHandler());
    glDrawElements(UtilsGL::toGLPrimitiveType(primitiveType), count, UtilsGL::toGLIndexType(indexType), (GLvoid*)offset);
}

void CommandBufferGL::setScissorRect(bool isEnabled, float x, float y, float width, float height)
{

}

void CommandBufferGL::setDepthStencilState(DepthStencilState *depthStencilState)
{
//    if (depthStencilState)
//    {
//        _depthStencilStateGL = static_cast<DepthStencilStateGL*>(depthStencilState);
//    }
//    else
//    {
//        _depthStencilStateGL = nullptr;
//    }
}

void CommandBufferGL::captureScreen(std::function<void(const unsigned char *, int, int)> callback)
{

}

void CommandBufferGL::prepareDrawing()
{
    const auto& shader = mRenderPipeline->getShader();
    glUseProgram(shader->getHandler());

    bindVertexBuffer(shader);
    setUniforms(shader);

//    if (mDepthStencilStateGL)
//    {
//        mDepthStencilStateGL->apply(_stencilReferenceValueFront, _stencilReferenceValueBack);
//    }
//    else
//    {
//        mDepthStencilStateGL::reset();
//    }

    // Set cull mode.
    if (CullMode::NONE == this->mCullMode)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(UtilsGL::toGLCullMode(this->mCullMode));
    }
}

void CommandBufferGL::bindVertexBuffer(ShaderGL *shader) const
{
//    auto vertexLayout = _programState->getVertexLayout();
//
//    if (!vertexLayout->isValid())
//        return;
//
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer->getHandler());
//
//    const auto& attributes = vertexLayout->getAttributes();
//    for (const auto& attributeInfo : attributes)
//    {
//        const auto& attribute = attributeInfo.second;
//        glEnableVertexAttribArray(attribute.index);
//        glVertexAttribPointer(attribute.index,
//                              UtilsGL::getGLAttributeSize(attribute.format),
//                              UtilsGL::toGLAttributeType(attribute.format),
//                              attribute.needToBeNormallized,
//                              vertexLayout->getStride(),
//                              (GLvoid*)attribute.offset);
//    }
}

void CommandBufferGL::setUniforms(ShaderGL *program) const
{

}

#define DEF_TO_INT(pointer, index)     (*((GLint*)(pointer) + index))
#define DEF_TO_FLOAT(pointer, index)   (*((GLfloat*)(pointer) + index))
void CommandBufferGL::setUniform(bool isArray, GLuint location, unsigned int size, GLenum uniformType,
                            void *data) const
{
    GLsizei count = size;
    switch (uniformType)
    {
        case GL_INT:
        case GL_BOOL:
        case GL_SAMPLER_2D:
        case GL_SAMPLER_CUBE:
            if (isArray)
                glUniform1iv(location, count, (GLint*)data);
            else
                glUniform1i(location, DEF_TO_INT(data, 0));
            break;
        case GL_INT_VEC2:
        case GL_BOOL_VEC2:
            if (isArray)
                glUniform2iv(location, count, (GLint*)data);
            else
                glUniform2i(location, DEF_TO_INT(data, 0), DEF_TO_INT(data, 1));
            break;
        case GL_INT_VEC3:
        case GL_BOOL_VEC3:
            if (isArray)
                glUniform3iv(location, count, (GLint*)data);
            else
                glUniform3i(location,
                            DEF_TO_INT(data, 0),
                            DEF_TO_INT(data, 1),
                            DEF_TO_INT(data, 2));
            break;
        case GL_INT_VEC4:
        case GL_BOOL_VEC4:
            if (isArray)
                glUniform4iv(location, count, (GLint*)data);
            else
                glUniform4i(location,
                            DEF_TO_INT(data, 0),
                            DEF_TO_INT(data, 1),
                            DEF_TO_INT(data, 2),
                            DEF_TO_INT(data, 4));
            break;
        case GL_FLOAT:
            if (isArray)
                glUniform1fv(location, count, (GLfloat*)data);
            else
                glUniform1f(location, DEF_TO_FLOAT(data, 0));
            break;
        case GL_FLOAT_VEC2:
            if (isArray)
                glUniform2fv(location, count, (GLfloat*)data);
            else
                glUniform2f(location, DEF_TO_FLOAT(data, 0), DEF_TO_FLOAT(data, 1));
            break;
        case GL_FLOAT_VEC3:
            if (isArray)
                glUniform3fv(location, count, (GLfloat*)data);
            else
                glUniform3f(location,
                            DEF_TO_FLOAT(data, 0),
                            DEF_TO_FLOAT(data, 1),
                            DEF_TO_FLOAT(data, 2));
            break;
        case GL_FLOAT_VEC4:
            if (isArray)
                glUniform4fv(location, count, (GLfloat*)data);
            else
                glUniform4f(location,
                            DEF_TO_FLOAT(data, 0),
                            DEF_TO_FLOAT(data, 1),
                            DEF_TO_FLOAT(data, 2),
                            DEF_TO_FLOAT(data, 3));
            break;
        case GL_FLOAT_MAT2:
            glUniformMatrix2fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
        case GL_FLOAT_MAT3:
            glUniformMatrix3fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
            break;

        default:
//            CCASSERT(false, "invalidate Uniform data type");
            break;
    }
}


