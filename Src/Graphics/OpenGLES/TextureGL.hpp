//
// Created by Murphy on 2020/8/9.
//

/**
 * TextureGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/9 15:52
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Platform.hpp"
#include "Graphics/Base/Types.hpp"
#include "Graphics/Base/Texture.hpp"

NS_STITCHES_BEGIN

struct TextureInfoGL
{
    void applySamplerDescriptor(const SamplerDescriptor &desc, bool isPow2, bool hasMipmaps);

    GLint magFilterGL = GL_LINEAR;
    GLint minFilterGL = GL_LINEAR;
    GLint sAddressModeGL = GL_REPEAT;
    GLint tAddressModeGL = GL_REPEAT;

    // Used in glTexImage2D().
    GLint internalFormat = GL_RGBA;
    GLenum format = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;

    GLuint texture = 0;
};

class Texture2DGL : public Texture2DBackend
{
public:
    /**
     * @param descirptor Specifies the texture description.
     */
    Texture2DGL(const TextureDescriptor& descriptor);
    ~Texture2DGL();

    virtual void updateWithBitmap(Bitmap* bitmap) override ;

    /**
     * Update a two-dimensional texture image
     * @param data Specifies a pointer to the image data in memory.
     * @param width Specifies the width of the texture image.
     * @param height Specifies the height of the texture image.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     */
    virtual void updateData(uint8_t* data, std::size_t width , std::size_t height, std::size_t level) override;

    /**
     * Update a two-dimensional texture image in a compressed format
     * @param data Specifies a pointer to the compressed image data in memory.
     * @param width Specifies the width of the texture image.
     * @param height Specifies the height of the texture image.
     * @param dataLen Specifies the totoal size of compressed image in bytes.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     */
    virtual void updateCompressedData(uint8_t* data, std::size_t width , std::size_t height, std::size_t dataLen, std::size_t level) override;

    /**
     * Update a two-dimensional texture subimage
     * @param xoffset Specifies a texel offset in the x direction within the texture array.
     * @param yoffset Specifies a texel offset in the y direction within the texture array.
     * @param width Specifies the width of the texture subimage.
     * @param height Specifies the height of the texture subimage.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     * @param data Specifies a pointer to the image data in memory.
     */
    virtual void updateSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t level, uint8_t* data) override;

    /**
     * Update a two-dimensional texture subimage in a compressed format
     * @param xoffset Specifies a texel offset in the x direction within the texture array.
     * @param yoffset Specifies a texel offset in the y direction within the texture array.
     * @param width Specifies the width of the texture subimage.
     * @param height Specifies the height of the texture subimage.
     * @param dataLen Specifies the totoal size of compressed subimage in bytes.
     * @param level Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     * @param data Specifies a pointer to the compressed image data in memory.
     */
    virtual void updateCompressedSubData(std::size_t xoffset, std::size_t yoffset, std::size_t width, std::size_t height, std::size_t dataLen, std::size_t level, uint8_t* data) override;

    /**
     * Update sampler
     * @param sampler Specifies the sampler descriptor.
     */
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler)  override;

    /**
     * Read a block of pixels from the drawable texture
     * @param x,y Specify the window coordinates of the first pixel that is read from the drawable texture. This location is the lower left corner of a rectangular block of pixels.
     * @param width,height Specify the dimensions of the pixel rectangle. width and height of one correspond to a single pixel.
     * @param flipImage Specifies if needs to flip the image.
     * @param callback Specifies a call back function to deal with the image.
     */
    virtual void getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback) override;

    /**
     * Generate mipmaps.
     */
    virtual void generateMipmaps() override;

    /**
     * Update texture description.
     * @param descriptor Specifies texture and sampler descriptor.
     */
    virtual void updateTextureDescriptor(const TextureDescriptor& descriptor) override;

    /**
     * Get texture object.
     * @return Texture object.
     */
    inline GLuint getHandler() const { return mTextureInfo.texture; }

    /**
     * Set texture to pipeline
     * @param index Specifies the texture image unit selector.
     */
    void apply(int index) const;

private:
    void initWithZeros();

    TextureInfoGL mTextureInfo;
//    EventListener* _backToForegroundListener = nullptr;
};

class TextureCubeGL: public TextureCubemapBackend
{
public:
    /**
     * @param descirptor Specifies the texture description.
     */
    TextureCubeGL(const TextureDescriptor& descriptor);
    ~TextureCubeGL();

    /**
     * Update sampler
     * @param sampler Specifies the sampler descriptor.
     */
    virtual void updateSamplerDescriptor(const SamplerDescriptor &sampler) override;

    /**
     * Update texutre cube data in give slice side.
     * @param side Specifies which slice texture of cube to be update.
     * @param data Specifies a pointer to the image data in memory.
     */
    virtual void updateFaceData(TextureCubeFace side, void *data) override;

    /**
     * Read a block of pixels from the drawable texture
     * @param x,y Specify the window coordinates of the first pixel that is read from the drawable texture. This location is the lower left corner of a rectangular block of pixels.
     * @param width,height Specify the dimensions of the pixel rectangle. width and height of one correspond to a single pixel.
     * @param flipImage Specifies if needs to flip the image.
     * @param callback
     */
    virtual void getBytes(std::size_t x, std::size_t y, std::size_t width, std::size_t height, bool flipImage, std::function<void(const unsigned char*, std::size_t, std::size_t)> callback) override;

    /// Generate mipmaps.
    virtual void generateMipmaps() override;

    /**
     * Update texture description.
     * @param descriptor Specifies texture and sampler descriptor.
     */
    virtual void updateTextureDescriptor(const TextureDescriptor& descriptor) override ;

    /**
     * Get texture object.
     * @return Texture object.
     */
    inline GLuint getHandler() const { return mTextureInfo.texture; }

    /**
     * Set texture to pipeline
     * @param index Specifies the texture image unit selector.
     */
    void apply(int index) const;

private:
    void setTexParameters();

    TextureInfoGL mTextureInfo;
//    EventListener* _backToForegroundListener = nullptr;
};

NS_STITCHES_END

