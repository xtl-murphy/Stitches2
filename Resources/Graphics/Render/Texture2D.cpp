
/**
 * Texture2D
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 20:52
 **/
#include "Texture2D.hpp"

NS_STITCHES_BEGIN

typedef Texture2D::PixelFormatInfoMap::value_type PixelFormatInfoMapValue;
static const PixelFormatInfoMapValue TexturePixelFormatInfoTablesValue[] =
{
        PixelFormatInfoMapValue(PixelFormat::BGRA8888, Texture2D::PixelFormatInfo(32, false, true)),
        PixelFormatInfoMapValue(PixelFormat::RGBA8888, Texture2D::PixelFormatInfo(32, false, true)),
        PixelFormatInfoMapValue(PixelFormat::RGBA4444, Texture2D::PixelFormatInfo(16, false, true)),
        PixelFormatInfoMapValue(PixelFormat::RGB5A1, Texture2D::PixelFormatInfo(16, false, true)),
        PixelFormatInfoMapValue(PixelFormat::RGB565, Texture2D::PixelFormatInfo(16, false, false)),
        PixelFormatInfoMapValue(PixelFormat::RGB888, Texture2D::PixelFormatInfo(24, false, false)),
        PixelFormatInfoMapValue(PixelFormat::A8, Texture2D::PixelFormatInfo(8, false, false)),
        PixelFormatInfoMapValue(PixelFormat::I8, Texture2D::PixelFormatInfo(8, false, false)),
        PixelFormatInfoMapValue(PixelFormat::AI88, Texture2D::PixelFormatInfo(16, false, true)),

#if defined( GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        PixelFormatInfoMapValue(PixelFormat::PVRTC2, Texture2D::PixelFormatInfo(2, true, false)),
        PixelFormatInfoMapValue(PixelFormat::PVRTC2A, Texture2D::PixelFormatInfo(2, true, true)),
        PixelFormatInfoMapValue(PixelFormat::PVRTC4, Texture2D::PixelFormatInfo(4, true, false)),
        PixelFormatInfoMapValue(PixelFormat::PVRTC4A, Texture2D::PixelFormatInfo(4, true, true)),
#endif

#if defined(GL_ETC1_RGB8_OES) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        PixelFormatInfoMapValue(PixelFormat::ETC, Texture2D::PixelFormatInfo(4, true, false)),
#endif

#if defined(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        PixelFormatInfoMapValue(PixelFormat::S3TC_DXT1, Texture2D::PixelFormatInfo(4, true, false)),
#endif

#if defined(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        PixelFormatInfoMapValue(PixelFormat::S3TC_DXT3, Texture2D::PixelFormatInfo(8, true, false)),
#endif

#if defined(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        PixelFormatInfoMapValue(PixelFormat::S3TC_DXT5, Texture2D::PixelFormatInfo(8, true, false)),
#endif

#ifdef GL_ATC_RGB_AMD
        PixelFormatInfoMapValue(PixelFormat::ATC_RGB, Texture2D::PixelFormatInfo(4, true, false)),
#endif

#ifdef GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
        PixelFormatInfoMapValue(PixelFormat::ATC_EXPLICIT_ALPHA, Texture2D::PixelFormatInfo(8, true, false)),
#endif

#ifdef GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
        PixelFormatInfoMapValue(PixelFormat::ATC_INTERPOLATED_ALPHA, Texture2D::PixelFormatInfo(8, true, false)),
#endif
        //metal formats
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        PixelFormatInfoMapValue(PixelFormat::MTL_ABGR4, Texture2D::PixelFormatInfo(16, false, true)),
        PixelFormatInfoMapValue(PixelFormat::MTL_B5G6R5, Texture2D::PixelFormatInfo(16, false, false)),
        PixelFormatInfoMapValue(PixelFormat::MTL_BGR5A1, Texture2D::PixelFormatInfo(16, false, true)),
#endif
};

const Texture2D::PixelFormatInfoMap Texture2D::_pixelFormatInfoTables(TexturePixelFormatInfoTablesValue,
                                                                      TexturePixelFormatInfoTablesValue + sizeof(TexturePixelFormatInfoTablesValue) / sizeof(TexturePixelFormatInfoTablesValue[0]));

// If the image has alpha, you can create RGBA8 (32-bit) or RGBA4 (16-bit) or RGB5A1 (16-bit)
// Default is: RGBA8888 (32-bit textures)
static PixelFormat g_defaultAlphaPixelFormat = PixelFormat::DEFAULT;


Texture2D::Texture2D()
        : _pixelFormat(PixelFormat::DEFAULT)
        , _pixelsWide(0)
        , _pixelsHigh(0)
        , _maxS(0.0)
        , _maxT(0.0)
        , _hasPremultipliedAlpha(false)
        , _hasMipmaps(false)
        , _antialiasEnabled(true)
//        , _ninePatchInfo(nullptr)
        , _valid(true)
        , _alphaTexture(nullptr)
{
    TextureDescriptor textureDescriptor;
    textureDescriptor.textureFormat = PixelFormat::NONE;
//    _texture = static_cast<Texture2DBackend*>(getInstance()->newTexture(textureDescriptor));
}

Texture2D::~Texture2D()
{
    SAFE_RELEASE_NULL(_alphaTexture); // ETC1 ALPHA support.

//    CCLOGINFO("deallocing Texture2D: %p - id=%u", this, _name);

//    CC_SAFE_DELETE(_ninePatchInfo);

    SAFE_RELEASE(_texture);
    SAFE_RELEASE(_programState);
}

PixelFormat Texture2D::getPixelFormat() const
{
    return _pixelFormat;
}

int Texture2D::getPixelsWide() const
{
    return _pixelsWide;
}

int Texture2D::getPixelsHigh() const
{
    return _pixelsHigh;
}

TextureBackend* Texture2D::getBackendTexture() const
{
    return _texture;
}

bool Texture2D::getAlphaTextureName() const
{
    return _alphaTexture == nullptr ? 0 : _alphaTexture->getBackendTexture();
}

Vector2i Texture2D::getContentSize() const
{
    Vector2i ret;
//    ret.x = _contentSize.x / CC_CONTENT_SCALE_FACTOR();
//    ret.y = _contentSize.y / CC_CONTENT_SCALE_FACTOR();

    return ret;
}

const Vector2i& Texture2D::getContentSizeInPixels()
{
    return _contentSize;
}

float Texture2D::getMaxS() const
{
    return _maxS;
}

void Texture2D::setMaxS(float maxS)
{
    _maxS = maxS;
}

float Texture2D::getMaxT() const
{
    return _maxT;
}

void Texture2D::setMaxT(float maxT)
{
    _maxT = maxT;
}

bool Texture2D::hasPremultipliedAlpha() const
{
    return _hasPremultipliedAlpha;
}

//bool Texture2D::initWithData(const void *data, ssize_t dataLen, PixelFormat pixelFormat, PixelFormat renderFormat, int pixelsWide, int pixelsHigh, const Vector2i& /*contentSize*/, bool preMultipliedAlpha)
//{
////    CCASSERT(dataLen>0 && pixelsWide>0 && pixelsHigh>0, "Invalid size");
//
//    //if data has no mipmaps, we will consider it has only one mipmap
//    MipmapInfo mipmap;
//    mipmap.address = (unsigned char*)data;
//    mipmap.len = static_cast<int>(dataLen);
//    return initWithMipmaps(&mipmap, 1, pixelFormat, renderFormat, pixelsWide, pixelsHigh, preMultipliedAlpha);
//}

//bool Texture2D::initWithMipmaps(MipmapInfo* mipmaps, int mipmapsNum, PixelFormat pixelFormat, PixelFormat renderFormat, int pixelsWide, int pixelsHigh, bool preMultipliedAlpha)
//{
//    //the pixelFormat must be a certain value
////    CCASSERT(pixelFormat != PixelFormat::NONE && pixelFormat != PixelFormat::AUTO, "the \"pixelFormat\" param must be a certain value!");
////    CCASSERT(pixelsWide > 0 && pixelsHigh > 0, "Invalid size");
//
//    if (mipmapsNum <= 0)
//    {
////        CCLOG("WARNING: mipmap number is less than 1");
//        return false;
//    }
//
//
//    auto formatItr = _pixelFormatInfoTables.find(pixelFormat);
//    if (formatItr == _pixelFormatInfoTables.end())
//    {
//        LOGE("", "WARNING: unsupported pixelformat: %lx", (unsigned long)pixelFormat);
//
//        return false;
//    }
//
//    const PixelFormatInfo& info = formatItr->second;
//
//
//    TextureDescriptor textureDescriptor;
//    textureDescriptor.width = pixelsWide;
//    textureDescriptor.height = pixelsHigh;
//    textureDescriptor.samplerDescriptor.magFilter = (_antialiasEnabled) ? SamplerFilter::LINEAR : SamplerFilter::NEAREST;
//    if (mipmapsNum == 1)
//    {
//        textureDescriptor.samplerDescriptor.minFilter = (_antialiasEnabled) ? SamplerFilter::LINEAR : SamplerFilter::NEAREST;
//    }
//    else
//    {
//        textureDescriptor.samplerDescriptor.minFilter = (_antialiasEnabled) ? SamplerFilter::LINEAR_MIPMAP_NEAREST : SamplerFilter::NEAREST_MIPMAP_NEAREST;
//    }
//
//    int width = pixelsWide;
//    int height = pixelsHigh;
//    PixelFormat oriPixelFormat = pixelFormat;
//    for (int i = 0; i < mipmapsNum; ++i)
//    {
//        unsigned char *data = mipmaps[i].address;
//        size_t dataLen = mipmaps[i].len;
//        unsigned char *outData = data;
//        size_t outDataLen = dataLen;
//
//        if(renderFormat != oriPixelFormat && !info.compressed) //need conversion
//        {
//            auto convertedFormat = PixelFormatUtils::convertDataToFormat(data, dataLen, oriPixelFormat, renderFormat, &outData, &outDataLen);
//
//            if(convertedFormat == renderFormat) pixelFormat = renderFormat;
//        }
//
//        textureDescriptor.textureFormat = pixelFormat;
////        CCASSERT(textureDescriptor.textureFormat != PixelFormat::NONE, "PixelFormat should not be NONE");
//
//        if(_texture->getTextureFormat() != textureDescriptor.textureFormat)
//            _texture->updateTextureDescriptor(textureDescriptor);
//
//        if(info.compressed)
//        {
//            _texture->updateCompressedData(data, width, height, dataLen, i);
//        }
//        else
//        {
//            _texture->updateData(outData, width, height, i);
//        }
//
//        if(outData && outData != data && outDataLen > 0)
//        {
//            free(outData);
//            outData = nullptr;
//            outDataLen = 0;
//        }
//
//        if (i > 0 && (width != height || ccNextPOT(width) != width ))
//        {
//            LOGE("Texture2D", "Texture2D. WARNING. Mipmap level %u is not squared. Texture won't render correctly. width=%d != height=%d", i, width, height);
//        }
//
//        width = MAX(width >> 1, 1);
//        height = MAX(height >> 1, 1);
//    }
//
//    _contentSize = Vector2i((float)pixelsWide, (float)pixelsHigh);
//    _pixelsWide = pixelsWide;
//    _pixelsHigh = pixelsHigh;
//    _pixelFormat = pixelFormat;
//    _maxS = 1;
//    _maxT = 1;
//
//    _hasPremultipliedAlpha = preMultipliedAlpha;
//    _hasMipmaps = mipmapsNum > 1;
//
//    return true;
//}

bool Texture2D::updateWithData(void *data,int offsetX,int offsetY,int width,int height)
{
    if (_texture && width > 0 && height > 0)
    {
        uint8_t* textureData = static_cast<uint8_t*>(data);
        _texture->updateSubData(offsetX, offsetY, width, height, 0, textureData);
        return true;
    }
    return false;
}

// implementation Texture2D (Image)
//bool Texture2D::initWithImage(Image *image)
//{
//    return initWithImage(image, g_defaultAlphaPixelFormat);
//}
//
//bool Texture2D::initWithImage(Image *image, PixelFormat format)
//{
//    if (image == nullptr)
//    {
//        LOGE("", "Texture2D. Can't create Texture. UIImage is nil");
//        return false;
//    }
//
//    int imageWidth = image->getWidth();
//    int imageHeight = image->getHeight();
//    this->_filePath = image->getFilePath();
//    Configuration *conf = Configuration::getInstance();
//
//    int maxTextureSize = conf->getMaxTextureSize();
//    if (imageWidth > maxTextureSize || imageHeight > maxTextureSize)
//    {
//        LOGE("", "WARNING: Image (%u x %u) is bigger than the supported %u x %u", imageWidth, imageHeight, maxTextureSize, maxTextureSize);
//        return false;
//    }
//
//    unsigned char*   tempData = image->getData();
//    Vector2i         imageSize = Vector2i((float)imageWidth, (float)imageHeight);
//    PixelFormat      renderFormat = ((PixelFormat::NONE == format) || (PixelFormat::AUTO == format)) ? image->getPixelFormat() : format;
//    PixelFormat      imagePixelFormat = image->getPixelFormat();
//    size_t           tempDataLen = image->getDataLen();
//
//
//
//    if (image->getNumberOfMipmaps() > 1)
//    {
//        if (renderFormat != image->getPixelFormat())
//        {
//            LOGE("", "WARNING: This image has more than 1 mipmaps and we will not convert the data format");
//        }
//
//        //pixel format of data is not converted, renderFormat can be different from pixelFormat
//        //it will be done later
//        initWithMipmaps(image->getMipmaps(), image->getNumberOfMipmaps(), image->getPixelFormat(), renderFormat, imageWidth, imageHeight, image->hasPremultipliedAlpha());
//
//        return true;
//    }
//    else if (image->isCompressed())
//    {
//        if (renderFormat != image->getPixelFormat())
//        {
//            LOGE("", "WARNING: This image is compressed and we can't convert it for now");
//        }
//
//        initWithData(tempData, tempDataLen, image->getPixelFormat(), imageWidth, imageHeight, imageSize, image->hasPremultipliedAlpha());
//
//        return true;
//    }
//    else
//    {
//        //after conversion, renderFormat == pixelFormat of data
//        initWithData(tempData, tempDataLen, imagePixelFormat, renderFormat, imageWidth, imageHeight, imageSize, image->hasPremultipliedAlpha());
//
//        return true;
//    }
//}

// implementation Texture2D (Text)
//bool Texture2D::initWithString(const char *text, const std::string& fontName, float fontSize, const Vector2i& dimensions/* = Size(0, 0)*/, TextHAlignment hAlignment/* =  TextHAlignment::CENTER */, TextVAlignment vAlignment/* =  TextVAlignment::TOP */, bool enableWrap /* = false */, int overflow /* = 0 */)
//{
//    FontDefinition tempDef;
//
//    tempDef._shadow._shadowEnabled = false;
//    tempDef._stroke._strokeEnabled = false;
//
//
//    tempDef._fontName      = fontName;
//    tempDef._fontSize      = fontSize;
//    tempDef._dimensions    = dimensions;
//    tempDef._alignment     = hAlignment;
//    tempDef._vertAlignment = vAlignment;
//    tempDef._fontFillColor = Color3B::WHITE;
//    tempDef._enableWrap    = enableWrap;
//    tempDef._overflow      = overflow;
//
//    return initWithString(text, tempDef);
//}

//bool Texture2D::initWithString(const char *text, const FontDefinition& textDefinition)
//{
//    if(!text || 0 == strlen(text))
//    {
//        return false;
//    }
//
//
//    bool ret = false;
//    TextAlign align;
//
//    if (TextVAlignment::TOP == textDefinition._vertAlignment)
//    {
//        align = (TextHAlignment::CENTER == textDefinition._alignment) ? TextAlign::TOP
//                                                                      : (TextHAlignment::LEFT == textDefinition._alignment) ? TextAlign::TOP_LEFT : TextAlign::TOP_RIGHT;
//    }
//    else if (TextVAlignment::CENTER == textDefinition._vertAlignment)
//    {
//        align = (TextHAlignment::CENTER == textDefinition._alignment) ? TextAlign::CENTER
//                                                                      : (TextHAlignment::LEFT == textDefinition._alignment) ? TextAlign::LEFT : TextAlign::RIGHT;
//    }
//    else if (TextVAlignment::BOTTOM == textDefinition._vertAlignment)
//    {
//        align = (TextHAlignment::CENTER == textDefinition._alignment) ? TextAlign::BOTTOM
//                                                                      : (TextHAlignment::LEFT == textDefinition._alignment) ? TextAlign::BOTTOM_LEFT : TextAlign::BOTTOM_RIGHT;
//    }
//    else
//    {
////        CCASSERT(false, "Not supported alignment format!");
//        return false;
//    }
//
//
//    PixelFormat      pixelFormat = g_defaultAlphaPixelFormat;
//    unsigned char* outTempData = nullptr;
//    size_t outTempDataLen = 0;
//
//    int imageWidth;
//    int imageHeight;
//    auto textDef = textDefinition;
//    auto contentScaleFactor = CC_CONTENT_SCALE_FACTOR();
//    textDef._fontSize *= contentScaleFactor;
//    textDef._dimensions.width *= contentScaleFactor;
//    textDef._dimensions.height *= contentScaleFactor;
//    textDef._stroke._strokeSize *= contentScaleFactor;
//    textDef._shadow._shadowEnabled = false;
//
//    bool hasPremultipliedAlpha;
//    Data outData = getTextureDataForText(text, textDef, align, imageWidth, imageHeight, hasPremultipliedAlpha);
//    if(outData.isNull())
//    {
//        return false;
//    }
//
//    Size  imageSize = Size((float)imageWidth, (float)imageHeight);
//    pixelFormat = PixelFormatUtils::convertDataToFormat(outData.getBytes(), imageWidth*imageHeight*4, PixelFormat::RGBA8888, pixelFormat, &outTempData, &outTempDataLen);
//
//    ret = initWithData(outTempData, outTempDataLen, pixelFormat, imageWidth, imageHeight, imageSize);
//
//    if (outTempData != nullptr && outTempData != outData.getBytes())
//    {
//        free(outTempData);
//    }
//    _hasPremultipliedAlpha = hasPremultipliedAlpha;
//
//    return ret;
//}

bool Texture2D::initWithBackendTexture(TextureBackend *texture, bool preMultipliedAlpha)
{
    SAFE_RETAIN(texture);
    SAFE_RELEASE(_texture);
    _texture = dynamic_cast<Texture2DBackend*>(texture);
//    CC_ASSERT(_texture);
    _pixelsWide = _contentSize.x = _texture->getWidth();
    _pixelsHigh = _contentSize.y = _texture->getHeight();
    _hasPremultipliedAlpha = preMultipliedAlpha;

    return true;
}

void Texture2D::setRenderTarget(bool renderTarget)
{
    _isRenderTarget = renderTarget;
}

bool Texture2D::hasMipmaps() const
{
    return _texture->hasMipmaps();
}

void Texture2D::setAliasTexParameters()
{

    if (! _antialiasEnabled)
    {
        return;
    }

    _antialiasEnabled = false;

    SamplerDescriptor descriptor(
            SamplerFilter::NEAREST, //magFilter
            (_texture->hasMipmaps()) ? SamplerFilter::NEAREST_MIPMAP_NEAREST : SamplerFilter::NEAREST, //minFilter
            SamplerAddressMode::DONT_CARE, //sAddressMode
            SamplerAddressMode::DONT_CARE//tAddressMode
    );
    _texture->updateSamplerDescriptor(descriptor);
}

void Texture2D::setAntiAliasTexParameters()
{

    if ( _antialiasEnabled )
    {
        return;
    }
    _antialiasEnabled = true;

    SamplerDescriptor descriptor(
            SamplerFilter::LINEAR, //magFilter
            (_texture->hasMipmaps()) ? SamplerFilter::LINEAR_MIPMAP_NEAREST : SamplerFilter::LINEAR, //minFilter
            SamplerAddressMode::DONT_CARE, //sAddressMode
            SamplerAddressMode::DONT_CARE //tAddressMode
    );
    _texture->updateSamplerDescriptor(descriptor);
}

const char* Texture2D::getStringForFormat() const
{
    switch (_pixelFormat)
    {
        case PixelFormat::RGBA8888:
            return  "RGBA8888";

        case PixelFormat::RGB888:
            return  "RGB888";

        case PixelFormat::RGB565:
            return  "RGB565";

        case PixelFormat::RGBA4444:
            return  "RGBA4444";

        case PixelFormat::RGB5A1:
            return  "RGB5A1";

        case PixelFormat::AI88:
            return  "AI88";

        case PixelFormat::A8:
            return  "A8";

        case PixelFormat::I8:
            return  "I8";

        case PixelFormat::PVRTC4:
            return  "PVRTC4";

        case PixelFormat::PVRTC2:
            return  "PVRTC2";

        case PixelFormat::PVRTC2A:
            return "PVRTC2A";

        case PixelFormat::PVRTC4A:
            return "PVRTC4A";

        case PixelFormat::ETC:
            return "ETC";

        case PixelFormat::S3TC_DXT1:
            return "S3TC_DXT1";

        case PixelFormat::S3TC_DXT3:
            return "S3TC_DXT3";

        case PixelFormat::S3TC_DXT5:
            return "S3TC_DXT5";

        case PixelFormat::ATC_RGB:
            return "ATC_RGB";

        case PixelFormat::ATC_EXPLICIT_ALPHA:
            return "ATC_EXPLICIT_ALPHA";

        case PixelFormat::ATC_INTERPOLATED_ALPHA:
            return "ATC_INTERPOLATED_ALPHA";

        case PixelFormat::MTL_ABGR4:
            return "MTL_ABGR4";

        case PixelFormat::MTL_B5G6R5:
            return "MTL_RGB565";

        case PixelFormat::MTL_BGR5A1:
            return "MTL_BGR5A1";

        default:
//            CCLOG("stringForFormat: %ld, cannot give useful result", (long)_pixelFormat);
            break;
    }

    return  nullptr;
}

//
// Texture options for images that contains alpha
//
// implementation Texture2D (PixelFormat)

void Texture2D::setDefaultAlphaPixelFormat(PixelFormat format)
{
    g_defaultAlphaPixelFormat = format;
}

PixelFormat Texture2D::getDefaultAlphaPixelFormat()
{
    return g_defaultAlphaPixelFormat;
}

unsigned int Texture2D::getBitsPerPixelForFormat(PixelFormat format) const
{
    if (format == PixelFormat::NONE || format == PixelFormat::DEFAULT)
    {
        return 0;
    }

    return _pixelFormatInfoTables.at(format).bpp;
}

unsigned int Texture2D::getBitsPerPixelForFormat() const
{
    return this->getBitsPerPixelForFormat(_pixelFormat);
}

const Texture2D::PixelFormatInfoMap& Texture2D::getPixelFormatInfoMap()
{
    return _pixelFormatInfoTables;
}

//void Texture2D::addSpriteFrameCapInset(SpriteFrame* spritframe, const Rect& capInsets)
//{
//    if(nullptr == _ninePatchInfo)
//    {
//        _ninePatchInfo = new (std::nothrow) NinePatchInfo;
//    }
//    if(nullptr == spritframe)
//    {
//        _ninePatchInfo->capInsetSize = capInsets;
//    }
//    else
//    {
//        _ninePatchInfo->capInsetMap[spritframe] = capInsets;
//    }
//}

//bool Texture2D::isContain9PatchInfo()const
//{
//    return nullptr != _ninePatchInfo;
//}

//const Rect& Texture2D::getSpriteFrameCapInset( cocos2d::SpriteFrame *spriteFrame )const
//{
//    CCASSERT(_ninePatchInfo != nullptr,
//             "Can't get the sprite frame capInset when the texture contains no 9-patch info.");
//    if(nullptr == spriteFrame)
//    {
//        return this->_ninePatchInfo->capInsetSize;
//    }
//    else
//    {
//        auto &capInsetMap = this->_ninePatchInfo->capInsetMap;
//        if(capInsetMap.find(spriteFrame) != capInsetMap.end())
//        {
//            return capInsetMap.at(spriteFrame);
//        }
//        else
//        {
//            return this->_ninePatchInfo->capInsetSize;
//        }
//    }
//}
//
//
//void Texture2D::removeSpriteFrameCapInset(SpriteFrame* spriteFrame)
//{
//    if(nullptr != this->_ninePatchInfo)
//    {
//        auto capInsetMap = this->_ninePatchInfo->capInsetMap;
//        if(capInsetMap.find(spriteFrame) != capInsetMap.end())
//        {
//            capInsetMap.erase(spriteFrame);
//        }
//    }
//}

/// halx99 spec, ANDROID ETC1 ALPHA supports.
void Texture2D::setAlphaTexture(Texture2D* alphaTexture)
{
    if (alphaTexture != nullptr) {
        alphaTexture->retain();
        SAFE_RELEASE(_alphaTexture);
        _alphaTexture = alphaTexture;
        _hasPremultipliedAlpha = true; // PremultipliedAlpha should be true.
    }
}

Texture2D* Texture2D::getAlphaTexture() const
{
    return _alphaTexture;
}

void Texture2D::setTexParameters(const Texture2D::TexParams &desc)
{
    _texture->updateSamplerDescriptor(desc);
}

void Texture2D::generateMipmap()
{
//    CCASSERT(_pixelsWide == ccNextPOT(_pixelsWide) && _pixelsHigh == ccNextPOT(_pixelsHigh), "Mipmap texture only works in POT textures");

    _texture->generateMipmaps();
}

void Texture2D::initProgram()
{
    if(_programState != nullptr)
        return;

    auto& pipelineDescriptor = _customCommand.getPipelineDescriptor();
    //create program state
    auto* program = Program::getBuiltinProgram(ProgramType::POSITION_TEXTURE);
    _programState = new (std::nothrow) ProgramState(program);
    _mvpMatrixLocation = _programState->getUniformLocation("u_MVPMatrix");
    _textureLocation = _programState->getUniformLocation("u_texture");

    pipelineDescriptor.programState = _programState;

    //setup vertex layout
    auto vertexLayout = _programState->getVertexLayout();
    auto& attributes = _programState->getProgram()->getActiveAttributes();
    auto iter = attributes.find("a_position");
    if(iter != attributes.end())
        vertexLayout->setAttribute("a_position", iter->second.location, VertexFormat::FLOAT2, 0, false);

    iter = attributes.find("a_texCoord");
    if(iter != attributes.end())
        vertexLayout->setAttribute("a_texCoord", iter->second.location, VertexFormat::FLOAT2, 2 * sizeof(float), false);

    vertexLayout->setLayout(4 * sizeof(float));

    //create vertex buffer
    _customCommand.setDrawType(CustomCommand::DrawType::ARRAY);
    _customCommand.setPrimitiveType(CustomCommand::PrimitiveType::TRIANGLE_STRIP);
    _customCommand.createVertexBuffer(4 * sizeof(float), 4, CustomCommand::BufferUsage::DYNAMIC);

    //setup blend state
    BlendFunc blendFunc;
    if(hasPremultipliedAlpha())
    {
        blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    }
    else
    {
        blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
    }

    auto& blendDescriptor = pipelineDescriptor.blendDescriptor;
    blendDescriptor.blendEnabled = true;
    blendDescriptor.sourceRGBBlendFactor = blendDescriptor.sourceAlphaBlendFactor = blendFunc.src;
    blendDescriptor.destinationRGBBlendFactor = blendDescriptor.destinationAlphaBlendFactor = blendFunc.dst;

    _programState->setTexture(_textureLocation, 0, _texture);
}

void Texture2D::drawAtPoint(const Vector2f &point, float globalZOrder)
{
    float width = (float)_pixelsWide * _maxS;
    float height = (float)_pixelsHigh * _maxT;
//    Rect rect = { point.x, point.y, width, height };
    Rect rect;
    rect.origin.x = point.x;
    rect.origin.y = point.y;
    rect.size.x = width;
    rect.size.y = height;
    drawInRect(rect, globalZOrder);
}

void Texture2D::drawInRect(const Rect& rect, float globalZOrder)
{
    initProgram();
    _customCommand.init(globalZOrder);
//    auto director = Director::getInstance();
//    const auto& modelView = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    const auto& projection = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

//    Matrix4 matrixMVP = projection * modelView;
    Matrix4 matrixMVP;

    float vertexData[] = {
            rect.origin.x,                      rect.origin.y,                      0.0f,   _maxT,
            rect.size.x + rect.origin.x,    rect.origin.y,                      _maxS,  _maxT,
            rect.origin.x,                      rect.size.y  + rect.origin.y,  0.0f,   0.0f,
            rect.size.x + rect.origin.x,    rect.size.y  + rect.origin.y,  _maxS,  0.0f };

    _programState->setUniform(_mvpMatrixLocation, matrixMVP.rows, sizeof(matrixMVP.rows));
    _customCommand.updateVertexBuffer(vertexData, sizeof(vertexData));
//    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

NS_STITCHES_END