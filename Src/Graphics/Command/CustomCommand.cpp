
/**
 * CustomCommand
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/12 23:09
 **/
#include <Graphics/OpenGLES/BufferGL.hpp>
#include "CustomCommand.hpp"

NS_STITCHES_BEGIN

CustomCommand::CustomCommand()
{
    _type = RenderCommand::Type::CUSTOM_COMMAND;
}

CustomCommand::~CustomCommand()
{
    SAFE_RELEASE(_vertexBuffer);
    SAFE_RELEASE(_indexBuffer);
}

void CustomCommand::init(float depth, const Matrix4 &modelViewTransform, unsigned int flags)
{
    RenderCommand::init(depth, modelViewTransform, flags);
}

void CustomCommand::init(float globalZOrder)
{
    _globalOrder = globalZOrder;
}

void CustomCommand::init(float globalZOrder, const BlendFunc& blendFunc)
{
    _globalOrder = globalZOrder;

    auto& blendDescriptor = _pipelineDescriptor.blendDescriptor;
    blendDescriptor.blendEnabled = true;
    blendDescriptor.sourceRGBBlendFactor = blendDescriptor.sourceAlphaBlendFactor = blendFunc.src;
    blendDescriptor.destinationRGBBlendFactor = blendDescriptor.destinationAlphaBlendFactor = blendFunc.dst;
}

void CustomCommand::createVertexBuffer(std::size_t vertexSize, std::size_t capacity, BufferUsage usage)
{
    SAFE_RELEASE(_vertexBuffer);

    _vertexCapacity = capacity;
    _vertexDrawCount = capacity;

//    auto device = Device::getInstance();
//    _vertexBuffer = device->newBuffer(vertexSize * capacity, BufferType::VERTEX, usage);
    _vertexBuffer = new BufferGL(vertexSize * capacity, BufferType::VERTEX, usage);
}

void CustomCommand::createIndexBuffer(IndexFormat format, std::size_t capacity, BufferUsage usage)
{
    SAFE_RELEASE(_indexBuffer);

    _indexFormat = format;
    _indexSize = computeIndexSize();
    _indexCapacity = capacity;
    _indexDrawCount = capacity;

//    auto device = Device::getInstance();
//    _indexBuffer = device->newBuffer(_indexSize * capacity, BufferType::INDEX, usage);
}

void CustomCommand::updateVertexBuffer(void* data, std::size_t offset, std::size_t length)
{
    assert(_vertexBuffer);
    _vertexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::updateIndexBuffer(void* data, std::size_t offset, std::size_t length)
{
    assert(_indexBuffer);
    _indexBuffer->updateSubData(data, offset, length);
}

void CustomCommand::setVertexBuffer(Buffer *vertexBuffer)
{
    if (_vertexBuffer == vertexBuffer)
        return;

    _vertexBuffer = vertexBuffer;
    SAFE_RETAIN(_vertexBuffer);
}

void CustomCommand::setIndexBuffer(Buffer *indexBuffer, IndexFormat format)
{
    if (_indexBuffer == indexBuffer && _indexFormat == format)
        return;

    _indexBuffer = indexBuffer;
    SAFE_RETAIN(_indexBuffer);

    _indexFormat = format;
    _indexSize = computeIndexSize();
}

void CustomCommand::updateVertexBuffer(void* data, std::size_t length)
{
    assert(_vertexBuffer);
    _vertexBuffer->updateData(data, length);
}

void CustomCommand::updateIndexBuffer(void* data, std::size_t length)
{
    assert(_indexBuffer);
    _indexBuffer->updateData(data, length);
}

std::size_t CustomCommand::computeIndexSize() const
{
    if (IndexFormat::U_SHORT == _indexFormat)
        return sizeof(unsigned short);
    else
        return sizeof(unsigned int);
}

NS_STITCHES_END