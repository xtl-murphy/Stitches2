
/**
 * Image
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/11 23:48
 **/
#pragma once


#include "Stitches.hpp"
#include "Graphics/Base/Types.hpp"

NS_STITCHES_BEGIN

typedef struct _MipmapInfo
{
    unsigned char* address;
    int len;
    _MipmapInfo():address(NULL),len(0){}
}MipmapInfo;

class Image : public Ref
{
public:
    friend class TextureCache;
    /**
     * @js ctor
     */
    Image();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Image();

    /** Supported formats for Image */
    enum class Format
    {
        //! JPEG
        JPG,
        //! PNG
        PNG,
        //! WebP
        WEBP,
        //! PVR
        PVR,
        //! ETC
        ETC,
        //! S3TC
        S3TC,
        //! ATITC
        ATITC,
        //! TGA
        TGA,
        //! Raw Data
        RAW_DATA,
        //! Unknown format
        UNKNOWN
    };

    /**
     * Enables or disables premultiplied alpha for PNG files.
     *
     *  @param enabled (default: true)
     */
    static void setPNGPremultipliedAlphaEnabled(bool enabled) { PNG_PREMULTIPLIED_ALPHA_ENABLED = enabled; }

    /** treats (or not) PVR files as if they have alpha premultiplied.
     Since it is impossible to know at runtime if the PVR images have the alpha channel premultiplied, it is
     possible load them as if they have (or not) the alpha channel premultiplied.

     By default it is disabled.
     */
    static void setPVRImagesHavePremultipliedAlpha(bool haveAlphaPremultiplied);

    /**
    @brief Load the image from the specified path.
    @param path   the absolute file path.
    @return true if loaded correctly.
    */
    bool initWithImageFile(const std::string& path);

    /**
    @brief Load image from stream buffer.
    @param data  stream buffer which holds the image data.
    @param dataLen  data length expressed in (number of) bytes.
    @return true if loaded correctly.
    * @js NA
    * @lua NA
    */
//    bool initWithImageData(const unsigned char * data, ssize_t dataLen);

    // @warning kFmtRawData only support RGBA8888
    bool initWithRawData(const unsigned char * data, ssize_t dataLen, int width, int height, int bitsPerComponent, bool preMulti = false);

    // Getters
    unsigned char *   getData()               { return _data; }
    ssize_t           getDataLen()            { return _dataLen; }
    Format            getFileType()           { return _fileType; }
    PixelFormat getPixelFormat()  { return _pixelFormat; }
    int               getWidth()              { return _width; }
    int               getHeight()             { return _height; }
    int               getNumberOfMipmaps()    { return _numberOfMipmaps; }
    MipmapInfo*       getMipmaps()            { return _mipmaps; }
    bool              hasPremultipliedAlpha() { return _hasPremultipliedAlpha; }
    std::string getFilePath() const { return _filePath; }

    int                      getBitPerPixel();
    bool                     hasAlpha();
    bool                     isCompressed();


    /**
     @brief    Save Image data to the specified file, with specified format.
     @param    filePath        the file's absolute path, including file suffix.
     @param    isToRGB        whether the image is saved as RGB format.
     */
    bool saveToFile(const std::string &filename, bool isToRGB = true);
    void premultiplyAlpha();
    void reversePremultipliedAlpha();

protected:
    bool initWithJpgData(const unsigned char *  data, ssize_t dataLen);
    bool initWithPngData(const unsigned char * data, ssize_t dataLen);
    bool initWithWebpData(const unsigned char * data, ssize_t dataLen);
//    bool initWithPVRData(const unsigned char * data, ssize_t dataLen);
//    bool initWithPVRv2Data(const unsigned char * data, ssize_t dataLen);
//    bool initWithPVRv3Data(const unsigned char * data, ssize_t dataLen);
//    bool initWithETCData(const unsigned char * data, ssize_t dataLen);
//    bool initWithS3TCData(const unsigned char * data, ssize_t dataLen);
//    bool initWithATITCData(const unsigned char *data, ssize_t dataLen);
//    typedef struct sImageTGA tImageTGA;
//    bool initWithTGAData(tImageTGA* tgaData);

    bool saveImageToPNG(const std::string& filePath, bool isToRGB = true);
    bool saveImageToJPG(const std::string& filePath);



protected:
    /**
     @brief Determine how many mipmaps can we have.
     It's same as define but it respects namespaces
     */
    static const int MIPMAP_MAX = 16;
    /**
     @brief Determine whether we premultiply alpha for png files.
     */
    static bool PNG_PREMULTIPLIED_ALPHA_ENABLED;
    unsigned char *_data;
    ssize_t _dataLen;
    int _width;
    int _height;
    bool _unpack;
    Format _fileType;
    PixelFormat _pixelFormat;
    MipmapInfo _mipmaps[MIPMAP_MAX];   // pointer to mipmap images
    int _numberOfMipmaps;
    // false if we can't auto detect the image is premultiplied or not.
    bool _hasPremultipliedAlpha;
    std::string _filePath;


protected:
    // noncopyable
    Image(const Image& rImg);
    Image& operator=(const Image&);

    /*
     @brief The same result as with initWithImageFile, but thread safe. It is caused by
     loadImage() in TextureCache.cpp.
     @param fullpath  full path of the file.
     @param imageType the type of image, currently only supporting two types.
     @return  true if loaded correctly.
     */
    bool initWithImageFileThreadSafe(const std::string& fullpath);

    Format detectFormat(const unsigned char * data, ssize_t dataLen);
    bool isPng(const unsigned char * data, ssize_t dataLen);
    bool isJpg(const unsigned char * data, ssize_t dataLen);
    bool isWebp(const unsigned char * data, ssize_t dataLen);
//    bool isPvr(const unsigned char * data, ssize_t dataLen);
//    bool isEtc(const unsigned char * data, ssize_t dataLen);
    bool isS3TC(const unsigned char * data,ssize_t dataLen);
//    bool isATITC(const unsigned char *data, ssize_t dataLen);
};

NS_STITCHES_END

