
/**
 * Buffer
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/3 11:07
 **/

#pragma once

#include "Stitches.hpp"
#include "Types.hpp"

NS_STITCHES_BEGIN

class Buffer
{
public:
    Buffer(std::size_t size, BufferType type, BufferUsage usage)
            : mUsage(usage)
            , mType(type)
            , mSize(size)
    {}

    virtual ~Buffer() = default;

    virtual void updateData(void* data, std::size_t size) = 0;

    virtual void updateSubData(void* data, std::size_t offset, std::size_t size) = 0;

    virtual void usingDefaultStoredData(bool needDefaultStoredData) = 0;

    std::size_t getSize() const { return mSize; }

protected:
    BufferUsage mUsage = BufferUsage::DYNAMIC; ///< Buffer usage.
    BufferType mType = BufferType::VERTEX; ///< Buffer type.
    std::size_t mSize = 0; ///< buffer size in bytes.
};

NS_STITCHES_END
