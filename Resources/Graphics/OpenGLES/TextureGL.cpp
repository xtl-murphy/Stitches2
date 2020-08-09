
/**
 * TextureGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 15:52
 **/
#include "TextureGL.hpp"
#include "UtilsGL.hpp"

NS_STITCHES_BEGIN

#define ISPOW2(n) (((n) & (n-1)) == 0)

bool isMipmapEnabled(GLint filter)
{
    switch(filter)
    {
        case GL_LINEAR_MIPMAP_LINEAR:
        case GL_LINEAR_MIPMAP_NEAREST:
        case GL_NEAREST_MIPMAP_NEAREST:
        case GL_NEAREST_MIPMAP_LINEAR:
            return true;
        default:
            break;
    }
    return false;
}

void TextureInfoGL::applySamplerDescriptor(const SamplerDescriptor& descriptor, bool isPow2, bool hasMipmaps)
{
    if (descriptor.magFilter != SamplerFilter::DONT_CARE)
    {
        magFilterGL = UtilsGL::toGLMagFilter(descriptor.magFilter);
    }

    if (descriptor.minFilter != SamplerFilter::DONT_CARE)
    {
        minFilterGL = UtilsGL::toGLMinFilter(descriptor.minFilter, hasMipmaps, isPow2);
    }

    if (descriptor.sAddressMode != SamplerAddressMode::DONT_CARE)
    {
        sAddressModeGL = UtilsGL::toGLAddressMode(descriptor.sAddressMode, isPow2);
    }

    if (descriptor.tAddressMode != SamplerAddressMode::DONT_CARE)
    {
        tAddressModeGL = UtilsGL::toGLAddressMode(descriptor.tAddressMode, isPow2);
    }
}

Texture2DGL::Texture2DGL(const TextureDescriptor& descriptor) : Texture2DBackend(descriptor)
{
    glGenTextures(1, &mTextureInfo.texture);

    updateTextureDescriptor(descriptor);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Listen this event to restored texture id after coming to foreground on Android.
_backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
    glGenTextures(1, &(this->mTextureInfo.texture));
    this->initWithZeros();
});
Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

void Texture2DGL::initWithZeros()
{
    auto size = mWidth * mHeight * mBitsPerElement / 8;
    uint8_t* data = (uint8_t*)malloc(size);
    memset(data, 0, size);
    updateData(data, mWidth, mHeight, 0);
    free(data);
}

void Texture2DGL::updateTextureDescriptor(const TextureDescriptor &descriptor)
{
    TextureBackend::updateTextureDescriptor(descriptor);
    UtilsGL::toGLTypes(descriptor.textureFormat, mTextureInfo.internalFormat, mTextureInfo.format, mTextureInfo.type, mIsCompressed);

    bool isPow2 = ISPOW2(mWidth) && ISPOW2(mHeight);
    mTextureInfo.magFilterGL = UtilsGL::toGLMagFilter(descriptor.samplerDescriptor.magFilter);
    mTextureInfo.minFilterGL = UtilsGL::toGLMinFilter(descriptor.samplerDescriptor.minFilter, mHasMipmaps, isPow2);

    mTextureInfo.sAddressModeGL = UtilsGL::toGLAddressMode(descriptor.samplerDescriptor.sAddressMode, isPow2);
    mTextureInfo.tAddressModeGL = UtilsGL::toGLAddressMode(descriptor.samplerDescriptor.tAddressMode, isPow2);

    updateSamplerDescriptor(descriptor.samplerDescriptor);

    // Update data here because `updateData()` may not be invoked later.
    // For example, a texture used as depth buffer will not invoke updateData().
    initWithZeros();
}

Texture2DGL::~Texture2DGL()
{
    if (mTextureInfo.texture)
        glDeleteTextures(1, &mTextureInfo.texture);
    mTextureInfo.texture = 0;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void Texture2DGL::updateSamplerDescriptor(const SamplerDescriptor &sampler) {
    bool isPow2 = ISPOW2(mWidth) && ISPOW2(mHeight);
    mTextureInfo.applySamplerDescriptor(sampler, isPow2, mHasMipmaps);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureInfo.texture);

    if (sampler.magFilter != SamplerFilter::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureInfo.magFilterGL);
    }

    if (sampler.minFilter != SamplerFilter::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.minFilterGL);
    }

    if (sampler.sAddressMode != SamplerAddressMode::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureInfo.sAddressModeGL);
    }

    if (sampler.tAddressMode != SamplerAddressMode::DONT_CARE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureInfo.tAddressModeGL);
    }
}

void Texture2DGL::updateData(uint8_t* data, std::size_t width , std::size_t height, std::size_t level)
{
    //Set the row align only when mipmapsNum == 1 and the data is uncompressed
    auto mipmapEnalbed = isMipmapEnabled(mTextureInfo.minFilterGL) || isMipmapEnabled(mTextureInfo.magFilterGL);
    if(!mipmapEnalbed)
    {
        unsigned int bytesPerRow = width * mBitsPerElement / 8;

        if(bytesPerRow % 8 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
        }
        else if(bytesPerRow % 4 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        }
        else if(bytesPerRow % 2 == 0)
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
        }
        else
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        }
    }
    else
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureInfo.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureInfo.magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureInfo.sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureInfo.tAddressModeGL);


    glTexImage2D(GL_TEXTURE_2D,
                 level,
                 mTextureInfo.internalFormat,
                 width,
                 height,
                 0,
                 mTextureInfo.format,
                 mTextureInfo.type,
                 data);
    CHECK_GL_ERROR_DEBUG();

    if(!mHasMipmaps && level > 0)
        mHasMipmaps = true;
}

void Texture2DGL::updateCompressedData(uint8_t *data, std::size_t width, std::size_t height,
                                       std::size_t dataLen, std::size_t level)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureInfo.texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureInfo.magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureInfo.minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureInfo.sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureInfo.tAddressModeGL);


    glCompressedTexImage2D(GL_TEXTURE_2D,
                           level,
                           mTextureInfo.internalFormat,
                           (GLsizei)width,
                           (GLsizei)height,
                           0,
                           dataLen,
                           data);
    CHECK_GL_ERROR_DEBUG();

    if(!mHasMipmaps && level > 0)
        mHasMipmaps = true;
}

void Texture2DGL::updateSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t level, uint8_t* data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureInfo.texture);

    glTexSubImage2D(GL_TEXTURE_2D,
                    level,
                    xoffset,
                    yoffset,
                    width,
                    height,
                    mTextureInfo.format,
                    mTextureInfo.type,
                    data);
    CHECK_GL_ERROR_DEBUG();

    if(!mHasMipmaps && level > 0)
        mHasMipmaps = true;
}

void Texture2DGL::updateCompressedSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width,
                                          std::size_t height, std::size_t dataLen, std::size_t level,
                                          uint8_t *data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureInfo.texture);

    glCompressedTexSubImage2D(GL_TEXTURE_2D,
                              level,
                              xoffset,
                              yoffset,
                              width,
                              height,
                              mTextureInfo.format,
                              dataLen,
                              data);
    CHECK_GL_ERROR_DEBUG();

    if(!mHasMipmaps && level > 0)
        mHasMipmaps = true;
}

void Texture2DGL::apply(int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, mTextureInfo.texture);
}

void Texture2DGL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == mTextureUsage)
        return;

    if(!mHasMipmaps)
    {
        mHasMipmaps = true;
        glBindTexture(GL_TEXTURE_2D, mTextureInfo.texture);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Texture2DGL::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
    GLint defaultFBO = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);

    GLuint frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureInfo.texture, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    auto bytePerRow = width * mBitsPerElement / 8;
    unsigned char* image = new unsigned char[bytePerRow * height];
    glReadPixels(x,y,width, height,GL_RGBA,GL_UNSIGNED_BYTE, image);

    if(flipImage)
    {
        unsigned char* flippedImage = new unsigned char[bytePerRow * height];
        for (int i = 0; i < height; ++i)
        {
            memcpy(&flippedImage[i * bytePerRow],
                   &image[(height - i - 1) * bytePerRow],
                   bytePerRow);
        }
        callback(flippedImage, width, height);
        SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(image, width, height);
        SAFE_DELETE_ARRAY(image);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glDeleteFramebuffers(1, &frameBuffer);
}

TextureCubeGL::TextureCubeGL(const TextureDescriptor& descriptor)
        :TextureCubemapBackend(descriptor)
{
//    assert(mWidth == mHeight);
    mTextureType = TextureType::TEXTURE_CUBE;
    UtilsGL::toGLTypes(mTextureFormat, mTextureInfo.internalFormat, mTextureInfo.format, mTextureInfo.type, mIsCompressed);
    glGenTextures(1, &mTextureInfo.texture);
    updateSamplerDescriptor(descriptor.samplerDescriptor);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Listen this event to restored texture id after coming to foreground on Android.
_backToForegroundListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND, [this](EventCustom*){
    glGenTextures(1, &(this->mTextureInfo.texture));
    this->setTexParameters();
});
Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
    CHECK_GL_ERROR_DEBUG();
}

void TextureCubeGL::setTexParameters()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureInfo.texture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mTextureInfo.minFilterGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mTextureInfo.magFilterGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, mTextureInfo.sAddressModeGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, mTextureInfo.tAddressModeGL);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubeGL::updateTextureDescriptor(const TextureDescriptor &descriptor)
{
    UtilsGL::toGLTypes(descriptor.textureFormat, mTextureInfo.internalFormat, mTextureInfo.format, mTextureInfo.type, mIsCompressed);
    mTextureFormat = descriptor.textureFormat;
    updateSamplerDescriptor(descriptor.samplerDescriptor);
}

TextureCubeGL::~TextureCubeGL()
{
    if(mTextureInfo.texture)
        glDeleteTextures(1, &mTextureInfo.texture);
    mTextureInfo.texture = 0;

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

void TextureCubeGL::updateSamplerDescriptor(const SamplerDescriptor &sampler)
{
    mTextureInfo.applySamplerDescriptor(sampler, true, mHasMipmaps);
    setTexParameters();
}

void TextureCubeGL::apply(int index) const
{
    glActiveTexture(GL_TEXTURE0+ index);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureInfo.texture);
    CHECK_GL_ERROR_DEBUG();
}

void TextureCubeGL::updateFaceData(TextureCubeFace side, void *data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureInfo.texture);
    CHECK_GL_ERROR_DEBUG();
    int i = static_cast<int>(side);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                 0,                  // level
                 GL_RGBA,            // internal format
                 mWidth,              // width
                 mHeight,              // height
                 0,                  // border
                 mTextureInfo.internalFormat,            // format
                 mTextureInfo.type,  // type
                 data);              // pixel data

    CHECK_GL_ERROR_DEBUG();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubeGL::getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback)
{
    GLint defaultFBO = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    GLuint frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP, mTextureInfo.texture, 0);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    auto bytePerRow = width * mBitsPerElement / 8;
    unsigned char* image = new unsigned char[bytePerRow * height];
    glReadPixels(x,y,width, height,GL_RGBA,GL_UNSIGNED_BYTE, image);

    if(flipImage)
    {
        unsigned char* flippedImage = new unsigned char[bytePerRow * height];
        for (int i = 0; i < height; ++i)
        {
            memcpy(&flippedImage[i * bytePerRow],
                   &image[(height - i - 1) * bytePerRow],
                   bytePerRow);
        }
        callback(flippedImage, width, height);
        SAFE_DELETE_ARRAY(flippedImage);
    } else
    {
        callback(image, width, height);
        SAFE_DELETE_ARRAY(image);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, defaultFBO);
    glDeleteFramebuffers(1, &frameBuffer);
}

void TextureCubeGL::generateMipmaps()
{
    if (TextureUsage::RENDER_TARGET == mTextureUsage)
        return;

    if(!mHasMipmaps)
    {
        mHasMipmaps = true;
        glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureInfo.texture);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }
}

NS_STITCHES_END