
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
#include "TextureGL.hpp"

USING_STITCHES_VK

GLuint getHandler(TextureBackend *texture)
{
    switch (texture->getTextureType())
    {
        case TextureType::TEXTURE_2D:
            return static_cast<Texture2DGL*>(texture)->getHandler();
        case TextureType::TEXTURE_CUBE:
            return static_cast<TextureCubeGL*>(texture)->getHandler();
        default:
            return 0;
    }
}

void applyTexture(TextureBackend* texture, int slot)
{
    switch (texture->getTextureType())
    {
        case TextureType::TEXTURE_2D:
            static_cast<Texture2DGL*>(texture)->apply(slot);
            break;
        case TextureType::TEXTURE_CUBE:
            static_cast<TextureCubeGL*>(texture)->apply(slot);
            break;
        default:
            return ;
    }
}

CommandBufferGL::CommandBufferGL()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mDefaultFBO);
}

CommandBufferGL::~CommandBufferGL()
{
    glDeleteFramebuffers(1, &mGeneratedFBO);
    SAFE_RELEASE_NULL(mRenderPipeline);

//    cleanResources();
}

void CommandBufferGL::beginFrame()
{

}

void CommandBufferGL::beginRenderPass(const RenderPassDescriptor &descriptor)
{
    this->applyRenderPassDescriptor(descriptor);
}

void CommandBufferGL::applyRenderPassDescriptor(const RenderPassDescriptor &descriptor)
{
    bool useColorAttachmentExternal = descriptor.needColorAttachment && descriptor.colorAttachmentsTexture[0];
    bool useDepthAttachmentExternal = descriptor.depthTestEnabled && descriptor.depthAttachmentTexture;
    bool useStencilAttachmentExternal = descriptor.stencilTestEnabled && descriptor.stencilAttachmentTexture;
    bool useGeneratedFBO = false;

    if (useColorAttachmentExternal || useDepthAttachmentExternal || useStencilAttachmentExternal)
    {
        if(mGeneratedFBO == 0)
        {
            glGenFramebuffers(1, &mGeneratedFBO);
        }
        mCurrentFBO = mGeneratedFBO;
        useGeneratedFBO = true;
    }
    else
    {
        mCurrentFBO = mDefaultFBO;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, mCurrentFBO);

    if (useDepthAttachmentExternal)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_DEPTH_ATTACHMENT,
                               GL_TEXTURE_2D,
                               getHandler(descriptor.depthAttachmentTexture),
                               0);
        CHECK_GL_ERROR_DEBUG();

        mGeneratedFBOBindDepth = true;
    }
    else
    {
        if (mGeneratedFBOBindDepth && useGeneratedFBO)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_DEPTH_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   0,
                                   0);
            CHECK_GL_ERROR_DEBUG();

            mGeneratedFBOBindDepth = false;
        }
    }

    if (useStencilAttachmentExternal)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_STENCIL_ATTACHMENT,
                               GL_TEXTURE_2D,
                               getHandler(descriptor.depthAttachmentTexture),
                               0);
        CHECK_GL_ERROR_DEBUG();

        mGeneratedFBOBindStencil = true;
    }
    else
    {
        if (mGeneratedFBOBindStencil && useGeneratedFBO)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_STENCIL_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   0,
                                   0);
            CHECK_GL_ERROR_DEBUG();

            mGeneratedFBOBindStencil = false;
        }
    }

    if (descriptor.needColorAttachment)
    {
        int i = 0;
        for (const auto& texture : descriptor.colorAttachmentsTexture)
        {
            if (texture)
            {
                // TODO: support texture cube
                glFramebufferTexture2D(GL_FRAMEBUFFER,
                                       GL_COLOR_ATTACHMENT0 + i,
                                       GL_TEXTURE_2D,
                                       getHandler(texture),
                                       0);
            }
            CHECK_GL_ERROR_DEBUG();
            ++i;
        }

        if (useGeneratedFBO)
            mGeneratedFBOBindColor = true;
    }
    else
    {
        if (mGeneratedFBOBindColor && useGeneratedFBO)
        {
            // FIXME: Now only support attaching to attachment 0.
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_COLOR_ATTACHMENT0,
                                   GL_TEXTURE_2D,
                                   0,
                                   0);

            mGeneratedFBOBindColor = false;
        }

    }
    CHECK_GL_ERROR_DEBUG();

    // set clear color, depth and stencil
    GLbitfield mask = 0;
    if (descriptor.needClearColor)
    {
        mask |= GL_COLOR_BUFFER_BIT;
        const auto& clearColor = descriptor.clearColorValue;
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    }

    CHECK_GL_ERROR_DEBUG();

    GLboolean oldDepthWrite = GL_FALSE;
    GLboolean oldDepthTest = GL_FALSE;
    GLfloat oldDepthClearValue = 0.f;
    GLint oldDepthFunc = GL_LESS;
    if (descriptor.needClearDepth)
    {
        glGetBooleanv(GL_DEPTH_WRITEMASK, &oldDepthWrite);
        glGetBooleanv(GL_DEPTH_TEST, &oldDepthTest);
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);

        mask |= GL_DEPTH_BUFFER_BIT;
        glClearDepthf(descriptor.clearDepthValue);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_ALWAYS);
    }

    CHECK_GL_ERROR_DEBUG();

    if (descriptor.needClearStencil)
    {
        mask |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(descriptor.clearStencilValue);
    }

    if(mask) glClear(mask);

    CHECK_GL_ERROR_DEBUG();

    // restore depth test
    if (descriptor.needClearDepth)
    {
        if (!oldDepthTest)
            glDisable(GL_DEPTH_TEST);

        glDepthMask(oldDepthWrite);
        glDepthFunc(oldDepthFunc);
        glClearDepthf(oldDepthClearValue);
    }

    CHECK_GL_ERROR_DEBUG();
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
    buffer->retain();
    this->mVertexBuffer = dynamic_cast<BufferGL*>(buffer);
}

void CommandBufferGL::setIndexBuffer(Buffer *buffer)
{
    if (buffer == nullptr)
        return;

    buffer->retain();
    SAFE_RELEASE(mIndexBuffer);
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

void CommandBufferGL::bindVertexBuffer(ProgramGL *shader) const
{
    auto vertexLayout = mProgramState->getVertexLayout();

    if (!vertexLayout->isValid())
        return;

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer->getHandler());

    const auto& attributes = vertexLayout->getAttributes();
    for (const auto& attributeInfo : attributes)
    {
        const auto& attribute = attributeInfo.second;
        glEnableVertexAttribArray(attribute.index);
        glVertexAttribPointer(attribute.index,
                              UtilsGL::getGLAttributeSize(attribute.format),
                              UtilsGL::toGLAttributeType(attribute.format),
                              attribute.needToBeNormallized,
                              vertexLayout->getStride(),
                              (GLvoid*)attribute.offset);
    }
}

void CommandBufferGL::setUniforms(ProgramGL *program) const
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

