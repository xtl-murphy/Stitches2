
/**
 * Texture
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 1:48
 **/
#include "Texture.hpp"

NS_STITCHES_BEGIN

#define byte(n) ((n) * 8)
#define bit(n) (n)

uint8_t computeBitsPerElement(PixelFormat textureFormat)
{
    switch (textureFormat)
    {
        case PixelFormat::RGBA8888:
        case PixelFormat::BGRA8888:
            return byte(4);
        case PixelFormat::RGB888:
            return byte(3);
        case PixelFormat::RGBA4444:
            return byte(2);
        case PixelFormat::A8:
            return byte(1);
        case PixelFormat::I8:
            return byte(1);
        case PixelFormat::RGB565:
            return byte(2);
        case PixelFormat::RGB5A1:
            return byte(2);
        case PixelFormat::AI88:
            return byte(2);
        case PixelFormat::ETC:
            return bit(4);
        case PixelFormat::ATC_RGB:
            return bit(4);
        case PixelFormat::ATC_EXPLICIT_ALPHA:
            return byte(1);
        case PixelFormat::ATC_INTERPOLATED_ALPHA:
            return byte(1);
        case PixelFormat::PVRTC2:
            return bit(2);
        case PixelFormat::PVRTC2A:
            return bit(2);
        case PixelFormat::PVRTC4:
            return bit(4);
        case PixelFormat::PVRTC4A:
            return bit(4);
        case PixelFormat::S3TC_DXT1:
            return bit(4);
        case PixelFormat::S3TC_DXT3:
            return byte(1);
        case PixelFormat::S3TC_DXT5:
            return byte(1);
        case PixelFormat::MTL_BGR5A1:
            return byte(2);
        case PixelFormat::MTL_B5G6R5:
            return byte(2);
        case PixelFormat::MTL_ABGR4:
            return byte(2);
        case PixelFormat::D24S8:
        default:
            return byte(0); //"textureFormat pixel size in bytes not defined!";
    }
    return 0;
}

TextureBackend::TextureBackend(const TextureDescriptor& descriptor)
        : mBitsPerElement(computeBitsPerElement(descriptor.textureFormat))
        , mWidth(descriptor.width)
        , mHeight(descriptor.height)
        , mTextureType(descriptor.textureType)
        , mTextureFormat(descriptor.textureFormat)
        , mTextureUsage(descriptor.textureUsage)
{
}

TextureBackend::~TextureBackend()
{}

void TextureBackend::updateTextureDescriptor(const TextureDescriptor &descriptor)
{
    mBitsPerElement = computeBitsPerElement(descriptor.textureFormat);
    mTextureType = descriptor.textureType;
    mTextureFormat = descriptor.textureFormat;
    mTextureUsage = descriptor.textureUsage;
    mWidth = descriptor.width;
    mHeight = descriptor.height;
}

Texture2DBackend::Texture2DBackend(const TextureDescriptor& descriptor)
        : TextureBackend(descriptor)
{
}

TextureCubemapBackend::TextureCubemapBackend(const TextureDescriptor &descriptor)
        : TextureBackend(descriptor)
{

}

NS_STITCHES_END