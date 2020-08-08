
/**
 * BufferGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/8 0:17
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Base/Buffer.hpp"
#include "Graphics/Platform.hpp"
NS_STITCHES_BEGIN

class BufferGL : public Buffer
{
public:
    BufferGL(std::size_t size, BufferType type, BufferUsage usage);
    ~BufferGL() override;

    void updateData(void* data, std::size_t size) override;

    void updateSubData(void* data, std::size_t offset, std::size_t size) override;

    void usingDefaultStoredData(bool needDefaultStoredData) override ;

    inline GLuint getHandler() const { return mBuffer; }

private:
    GLuint mBuffer = 0;
    std::size_t mBufferAllocated = 0;
    char* mData = nullptr;
    bool mNeedDefaultStoredData = true;
};

NS_STITCHES_END

