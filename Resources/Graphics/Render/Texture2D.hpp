
/**
 * Texture2D
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 20:52
 **/
#pragma once

#include <Graphics/Image/Image.hpp>
#include <Graphics/Command/CustomCommand.hpp>
#include "Stitches.hpp"
#include "Graphics/Base/Texture.hpp"
#include "Graphics/Base/ProgramState.hpp"
#include "Graphics/Base/Types.hpp"
#include "Utils/Ref.hpp"
#include "Math/Math.hpp"

NS_STITCHES_BEGIN

class Texture2D : public Ref
{
public:
    struct PixelFormatInfo
    {

        PixelFormatInfo(int aBpp, bool aCompressed, bool anAlpha)
                : bpp(aBpp)
                , compressed(aCompressed)
                , alpha(anAlpha)
        {}

        int bpp;
        bool compressed;
        bool alpha;
    };

    typedef std::map<PixelFormat, const PixelFormatInfo> PixelFormatInfoMap;

    /**
     * Extension to set the Min / Mag filter
     */
    using TexParams = SamplerDescriptor;

public:
    /** sets the default pixel format for UIImagescontains alpha channel.

     @param format
     If the UIImage contains alpha channel, then the options are:
     - generate 32-bit textures: PixelFormat::RGBA8888 (default one)
     - generate 24-bit textures: PixelFormat::RGB888
     - generate 16-bit textures: PixelFormat::RGBA4444
     - generate 16-bit textures: PixelFormat::RGB5A1
     - generate 16-bit textures: PixelFormat::RGB565
     - generate 8-bit textures: PixelFormat::A8 (only use it if you use just 1 color)

     How does it work ?
     - If the image is an RGBA (with Alpha) then the default pixel format will be used (it can be a 8-bit, 16-bit or 32-bit texture)
     - If the image is an RGB (without Alpha) then: If the default pixel format is RGBA8888 then a RGBA8888 (32-bit) will be used. Otherwise a RGB565 (16-bit texture) will be used.

     This parameter is not valid for PVR / PVR.CCZ images.

     @since v0.8
     */
    static void setDefaultAlphaPixelFormat(PixelFormat format);

    /** Returns the alpha pixel format.
     @since v0.8
     */
    static PixelFormat getDefaultAlphaPixelFormat();

public:
    /**
     * @js ctor
     */
    Texture2D();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Texture2D();

    /** Initializes with a texture2d with data.

     @param data Specifies a pointer to the image data in memory.
     @param dataLen The image data length.
     @param pixelFormat The image pixelFormat.
     @param pixelsWide The image width.
     @param pixelsHigh The image height.
     @param contentSize The image content size.
     @param preMultipliedAlpha The texture has premultiplied alpha
     * @js NA
     * @lua NA
     */
//    bool initWithData(const void *data, ssize_t dataLen, PixelFormat pixelFormat, int pixelsWide, int pixelsHigh, const Vector2i& contentSize, bool preMultipliedAlpha = false) { return initWithData(data, dataLen, pixelFormat, pixelFormat, pixelsWide, pixelsHigh, contentSize, preMultipliedAlpha);}

    /** Initializes with a texture2d with data.

     @param data Specifies a pointer to the image data in memory.
     @param dataLen The image data length.
     @param pixelFormat The image pixelFormat.
     @param renderFormat The format converted to.
     @param pixelsWide The image width.
     @param pixelsHigh The image height.
     @param contentSize The image content size.
     @param preMultipliedAlpha The texture has premultiplied alpha
     * @js NA
     * @lua NA
     */
//    bool initWithData(const void *data, ssize_t dataLen, PixelFormat pixelFormat, PixelFormat renderFormat, int pixelsWide, int pixelsHigh, const Vector2i& contentSize, bool preMultipliedAlpha = false);

    /** Initializes with mipmaps.

     @param mipmaps Specifies a pointer to the image data in memory.
     @param mipmapsNum The mipmaps number.
     @param pixelFormat The image pixelFormat.
     @param pixelsWide The image width.
     @param pixelsHigh The image height.
     @param preMultipliedAlpha The texture has premultiplied alpha
     */
//    bool initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, PixelFormat pixelFormat, PixelFormat renderFormat, int pixelsWide, int pixelsHigh, bool preMultipliedAlpha = false);

    /** Update with texture data.

     @param data Specifies a pointer to the image data in memory.
     @param offsetX Specifies a texel offset in the x direction within the texture array.
     @param offsetY Specifies a texel offset in the y direction within the texture array.
     @param width Specifies the width of the texture subimage.
     @param height Specifies the height of the texture subimage.
     */
    bool updateWithData(void *data,int offsetX,int offsetY,int width,int height);
    /**
    Drawing extensions to make it easy to draw basic quads using a Texture2D object.
    These functions require GL_TEXTURE_2D and both GL_VERTEX_ARRAY and GL_TEXTURE_COORD_ARRAY client states to be enabled.
    */
    /** Draws a texture at a given point. */
    void drawAtPoint(const Vector2f & point, float globalZOrder);
    /** Draws a texture inside a rect.*/
    void drawInRect(const Rect& rect, float globalZOrder);

    /**
    Extensions to make it easy to create a Texture2D object from an image file.
    */
    /**
    Initializes a texture from a UIImage object.

    We will use the format you specified with setDefaultAlphaPixelFormat to convert the image for texture.
    NOTE: It will not convert the pvr image file.
    @param image An UIImage object.
    */
//    bool initWithImage(Image * image);

    /**
    Initializes a texture from a UIImage object.

    We will use the format you passed to the function to convert the image format to the texture format.
    If you pass PixelFormat::Automatic, we will auto detect the image render type and use that type for texture to render.
    @param image An UIImage object.
    @param format Texture pixel formats.
    **/
//    bool initWithImage(Image * image, PixelFormat format);

    /** Initializes a texture from a string with dimensions, alignment, font name and font size.

     @param text A null terminated string.
     @param fontName The font name.
     @param fontSize The font size.
     @param dimensions The font dimension.
     @param hAlignment The font horizontal text alignment type.
     @param vAlignment The font vertical text alignment type.
     @param enableWrap Whether enable text wrap or not.
     @param overflow Whether shrink font size when content larger than the dimensions.
     */
//    bool initWithString(const char *text,  const std::string &fontName, float fontSize, const Vector2i& dimensions = Vector2i(0, 0), TextHAlignment hAlignment = TextHAlignment::CENTER, TextVAlignment vAlignment = TextVAlignment::TOP, bool enableWrap = true, int overflow = 0);

    /** Initializes a texture from a string using a text definition.

     @param text A null terminated string.
     @param textDefinition A FontDefinition object contains font attributes.
     */
//    bool initWithString(const char *text, const FontDefinition& textDefinition);

    //TODO: minggo: is it resaonable?
    bool initWithBackendTexture(TextureBackend* texture, bool preMultipliedAlpha = false);
    void setRenderTarget(bool renderTarget);
    inline bool isRenderTarget() const { return _isRenderTarget; }


    void setTexParameters(const TexParams &params);

    /** Generates mipmap images for the texture.
     It only works if the texture size is POT (power of 2).
     @since v0.99.0
     */
    void generateMipmap();

    /** Sets antialias texture parameters:
     - GL_TEXTURE_MIN_FILTER = GL_LINEAR
     - GL_TEXTURE_MAG_FILTER = GL_LINEAR

     @warning Calling this method could allocate additional texture memory.

     @since v0.8
     */
    void setAntiAliasTexParameters();

    /** Sets alias texture parameters:
    - GL_TEXTURE_MIN_FILTER = GL_NEAREST
    - GL_TEXTURE_MAG_FILTER = GL_NEAREST

    @warning Calling this method could allocate additional texture memory.

    @since v0.8
    */
    void setAliasTexParameters();

    /** Returns the pixel format.
     @since v2.0
     */
    const char* getStringForFormat() const;

    /** Returns the bits-per-pixel of the in-memory OpenGL texture
    @since v1.0
    */
    unsigned int getBitsPerPixelForFormat() const;

    /** Helper functions that returns bits per pixels for a given format.
     @since v2.0
     */
    unsigned int getBitsPerPixelForFormat(PixelFormat format) const;

    /** Get content size. */
    const Vector2i & getContentSizeInPixels();

    /** Whether or not the texture has their Alpha premultiplied. */
    bool hasPremultipliedAlpha() const;

    /** Whether or not the texture has mip maps.*/
    bool hasMipmaps() const;

    /** Gets the pixel format of the texture. */
    PixelFormat getPixelFormat() const;

    /** Gets the width of the texture in pixels. */
    int getPixelsWide() const;

    /** Gets the height of the texture in pixels. */
    int getPixelsHigh() const;

    TextureBackend* getBackendTexture() const;

    /** Gets max S. */
    float getMaxS() const;
    /** Sets max S. */
    void setMaxS(float maxS);

    /** Gets max T. */
    float getMaxT() const;
    /** Sets max T. */
    void setMaxT(float maxT);

    /** Get the texture content size.*/
    Vector2i getContentSize() const;

    std::string getPath()const { return _filePath; }

    void setAlphaTexture(Texture2D* alphaTexture);
    Texture2D* getAlphaTexture() const;

    bool getAlphaTextureName() const;

public:
    /** Get pixel info map, the key-value pairs is PixelFormat and PixelFormatInfo.*/
    static const PixelFormatInfoMap& getPixelFormatInfoMap();

private:
    /**
    * A struct for storing 9-patch image capInsets.
    */

//    class NinePatchInfo
//    {
//    public:
//        Rect capInsetSize;
//        std::unordered_map<SpriteFrame*, Rect> capInsetMap;
//    };

    /**
     * Whether the texture contains a 9-patch capInset info or not.
     *
     * @return True is Texture contains a 9-patch info, false otherwise.
     */
//    bool isContain9PatchInfo()const;

    /**
     * Get spriteFrame capInset, If spriteFrame can't be found in 9-patch info map,
     * then single 9-patch texture capInset will be returned.
     * If the arg is nullptr, the capInset of single 9-patch texture will be returned.
     *
     * @param spriteFrame A SpriteFrame object pointer.
     *
     * @return The capInset of the SpriteFrame object.
     */
//    const Rect& getSpriteFrameCapInset(SpriteFrame* spriteFrame)const;
    /**
     * Remove the spriteFrame capInset info when the spriteFrame is removed.
     *
     * @param spriteFrame A SpriteFrame object pointer.
     */
//    void removeSpriteFrameCapInset(SpriteFrame* spriteFrame);
    /**
     * Add capInset for sprite atlas.
     * When handling single texture, pass nullptr in the first arg.
     *
     * @param spritframe The sprite frame object.
     * @param capInsets The parsed capInset from a .9 patch image.
     */
//    void addSpriteFrameCapInset(SpriteFrame* spritframe, const Rect& capInsets);

    void initProgram();

protected:
    /** pixel format of the texture */
    PixelFormat _pixelFormat;

    /** width in pixels */
    int _pixelsWide;

    /** height in pixels */
    int _pixelsHigh;

    /** texture name */
    Texture2DBackend* _texture;


    /** texture max S */
    float _maxS;

    /** texture max T */
    float _maxT;

    /** content size */
    Vector2i _contentSize;

    /** whether or not the texture has their Alpha premultiplied */
    bool _hasPremultipliedAlpha;

    /** whether or not the texture has mip maps*/
    bool _hasMipmaps;

    static const PixelFormatInfoMap _pixelFormatInfoTables;

    bool _antialiasEnabled;
//    NinePatchInfo* _ninePatchInfo;
    friend class SpriteFrameCache;
    friend class TextureCache;
    friend class Scale9Sprite;

    bool _valid;
    std::string _filePath;

    Texture2D* _alphaTexture;
    ProgramState* _programState = nullptr;
    UniformLocation _mvpMatrixLocation;
    UniformLocation _textureLocation;
    CustomCommand _customCommand;

    bool _isRenderTarget = false;
};

NS_STITCHES_END

