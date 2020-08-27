
/**
 * BufferGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/8 0:17
 **/
#include "BufferGL.hpp"

NS_STITCHES_BEGIN

GLenum toGLUsage(const BufferUsage& usage)
{
    switch (usage)
    {
        case BufferUsage::STATIC:
            return GL_STATIC_DRAW;
        case BufferUsage::DYNAMIC:
            return GL_DYNAMIC_DRAW;
        default:
            return GL_DYNAMIC_DRAW;
    }
}

BufferGL::BufferGL(std::size_t size, Stitches::BufferType type,
                             Stitches::BufferUsage usage) : Buffer(size, type, usage)
{
    glGenBuffers(1, &this->mBuffer);
}

BufferGL::~BufferGL()
{
    if (this->mBuffer)
    {
        glDeleteBuffers(1, &this->mBuffer);
    }
}

void BufferGL::updateData(void *data, std::size_t size)
{
    if (this->mBuffer)
    {
        if (BufferType::VERTEX == this->mType)
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->mBuffer);
            glBufferData(GL_ARRAY_BUFFER, size, data, toGLUsage(this->mUsage));
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, toGLUsage(this->mUsage));
        }
        mBufferAllocated = size;
    }
}

void BufferGL::updateSubData(void *data, std::size_t offset, std::size_t size)
{
    if (this->mBuffer)
    {
        if (BufferType::VERTEX == this->mType)
        {
            glBindBuffer(GL_ARRAY_BUFFER, this->mBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        }
        else
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mBuffer);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        }
    }
}

void BufferGL::usingDefaultStoredData(bool needDefaultStoredData)
{

}

NS_STITCHES_END

