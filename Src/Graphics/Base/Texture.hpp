
/**
 * Texture
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 1:48
 **/
#pragma once

#include <Graphics/Image/Bitmap.hpp>
#include "Stitches.hpp"
#include "Types.hpp"
#include "Utils/Ref.hpp"

NS_STITCHES_BEGIN

struct TextureDescriptor
{
    TextureType textureType = TextureType::TEXTURE_2D;
    PixelFormat textureFormat = PixelFormat::RGBA8888;
    TextureUsage textureUsage = TextureUsage::READ;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
    SamplerDescriptor samplerDescriptor;
};

class TextureBackend : public Ref
{
public:
    /**
     * Update sampler
     * @param sampler Specifies the sampler descriptor.
     */
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) = 0;

    /**
     * Read a block of pixels from the drawable texture
     * @param x,y Specify the window coordinates of the first pixel that is read from the drawable texture. This location is the lower left corner of a rectangular block of pixels.
     * @param width,height Specify the dimensions of the pixel rectangle. width and height of one correspond to a single pixel.
     * @param flipImage Specifies if needs to flip the image.
     * @param callback Specifies a call back function to deal with the image.
     */
    virtual void getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback) = 0;

    /// Generate mipmaps.
    virtual void generateMipmaps() = 0;

    /**
     * Update texture description.
     * @param descriptor Specifies texture and sampler descriptor.
     */
    virtual void updateTextureDescriptor(const TextureDescriptor& descriptor);

    /**
     * Get texture format.
     * @return Texture format.
     */
    inline PixelFormat getTextureFormat() const { return mTextureFormat; }

    /**
     * Get texture usage. Symbolic constant can be READ, WRITE or RENDER_TARGET.
     * @return Texture usage.
     */
    inline TextureUsage getTextureUsage() const { return mTextureUsage; }

    /**
     * Get texture type. Symbolic constant value can be either TEXTURE_2D or TEXTURE_CUBE.
     * @return Texture type.
     */
    inline TextureType getTextureType() const { return mTextureType; }

    /**
     * Check if mipmap had generated before.
     * @return true if the mipmap has always generated before, otherwise false.
     */
    inline bool hasMipmaps() const { return mHasMipmaps; }

protected:
    /**
     * @param descriptor Specifies the texture descirptor.
     */
    TextureBackend(const TextureDescriptor& descriptor);
    virtual ~TextureBackend();

    /// The bytes of all components.
    uint8_t mBitsPerElement = 0;
    bool mHasMipmaps = false;
    bool mIsCompressed = false;
    uint32_t mWidth = 0;
    uint32_t mHeight = 0;

    TextureType mTextureType = TextureType::TEXTURE_2D;
    PixelFormat mTextureFormat = PixelFormat::RGBA8888;
    TextureUsage mTextureUsage = TextureUsage::READ;
};

class Texture2DBackend : public TextureBackend
{
public:

    virtual void updateWithBitmap(Bitmap* bitmap) = 0;

    virtual void updateData(uint8_t* data, std::size_t width , std::size_t height, std::size_t level) = 0;

    virtual void updateCompressedData(uint8_t* data, std::size_t width , std::size_t height, std::size_t dataLen, std::size_t level) = 0;

    virtual void updateSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t level, uint8_t* data) = 0;

    virtual void updateCompressedSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t dataLen, std::size_t level, uint8_t* data) = 0;

    inline std::size_t getWidth() const { return mWidth; }

    inline std::size_t getHeight() const { return mHeight; }

protected:

    Texture2DBackend(const TextureDescriptor& descriptor);
};


class TextureCubemapBackend : public TextureBackend
{
public:
    /**
     * Update texutre cube data in give slice side.
     * @param side Specifies which slice texture of cube to be update.
     * @param data Specifies a pointer to the image data in memory.
     */
    virtual void updateFaceData(TextureCubeFace side, void *data) = 0;

protected:

    TextureCubemapBackend(const TextureDescriptor& descriptor);
};

NS_STITCHES_END

