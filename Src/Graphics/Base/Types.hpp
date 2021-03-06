
/**
 * Types
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:17
 **/
#pragma once

#include "Math/Math.hpp"
#include "Stitches.hpp"

NS_STITCHES_BEGIN

//#define ENABLE_BITMASK_OPERATORS(x)  \
//template<>                           \
//struct EnableBitMaskOperators<x>     \
//{                                    \
//    static const bool enable = true; \
//};

struct Color4B;
struct Color4F;

enum class BufferUsage : uint32_t
{
    STATIC,
    DYNAMIC
};

enum class BufferType : uint32_t
{
    VERTEX,
    INDEX
};

enum class ShaderStage : uint32_t
{
    VERTEX,
    FRAGMENT,
    VERTEX_AND_FRAGMENT
};

enum class VertexFormat : uint32_t
{
    FLOAT4,
    FLOAT3,
    FLOAT2,
    FLOAT,
    INT4,
    INT3,
    INT2,
    INT,
    USHORT4,
    USHORT2,
    UBYTE4
};

/** @typedef backend::PixelFormat
 Possible texture pixel formats
 */
enum class PixelFormat
{
    //! auto detect the type
    AUTO,
    //! 32-bit texture: BGRA8888
    BGRA8888,
    //! 32-bit texture: RGBA8888
    RGBA8888,
    //! 24-bit texture: RGBA888
    RGB888,
    //! 16-bit texture without Alpha channel
    RGB565,
    //! 8-bit textures used as masks
    A8,
    //! 8-bit intensity texture
    I8,
    //! 16-bit textures used as masks
    AI88,
    //! 16-bit textures: RGBA4444
    RGBA4444,
    //! 16-bit textures: RGB5A1
    RGB5A1,
    //! 4-bit PVRTC-compressed texture: PVRTC4
    PVRTC4,
    //! 4-bit PVRTC-compressed texture: PVRTC4 (has alpha channel)
    PVRTC4A,
    //! 2-bit PVRTC-compressed texture: PVRTC2
    PVRTC2,
    //! 2-bit PVRTC-compressed texture: PVRTC2 (has alpha channel)
    PVRTC2A,
    //! ETC-compressed texture: ETC
    ETC,
    //! S3TC-compressed texture: S3TC_Dxt1
    S3TC_DXT1,
    //! S3TC-compressed texture: S3TC_Dxt3
    S3TC_DXT3,
    //! S3TC-compressed texture: S3TC_Dxt5
    S3TC_DXT5,
    //! ATITC-compressed texture: ATC_RGB
    ATC_RGB,
    //! ATITC-compressed texture: ATC_EXPLICIT_ALPHA
    ATC_EXPLICIT_ALPHA,
    //! ATITC-compressed texture: ATC_INTERPOLATED_ALPHA
    ATC_INTERPOLATED_ALPHA,
    //! Default texture format: AUTO

    MTL_B5G6R5,
    //MTL_A1BGR5,
    MTL_BGR5A1,
    MTL_ABGR4,

    // A packed 32-bit combined depth and stencil pixel format with two nomorlized unsigned integer
    // components: 24 bits, typically used for a depth render target, and 8 bits, typically used for
    // a stencil render target.
    D24S8,

    DEFAULT = AUTO,

    NONE = -1
};

enum class TextureUsage : uint32_t
{
    READ,
    WRITE,
    RENDER_TARGET
};

enum class IndexFormat : uint32_t
{
    U_SHORT,
    U_INT
};

enum class VertexStepMode : uint32_t
{
    VERTEX,
    INSTANCE
};

enum class PrimitiveType : uint32_t
{
    POINT,
    LINE,
    LINE_STRIP,
    TRIANGLE,
    TRIANGLE_STRIP
};

enum class TextureType: uint32_t
{
    TEXTURE_2D,
    TEXTURE_CUBE
};

enum class SamplerAddressMode: uint32_t
{
    REPEAT,
    MIRROR_REPEAT,
    CLAMP_TO_EDGE,
    DONT_CARE,
};

enum class SamplerFilter: uint32_t
{
    NEAREST,
    NEAREST_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR,
    LINEAR_MIPMAP_LINEAR,
    LINEAR_MIPMAP_NEAREST,
    DONT_CARE,
};

enum class StencilOperation: uint32_t
{
    KEEP,
    ZERO,
    REPLACE,
    INVERT,
    INCREMENT_WRAP,
    DECREMENT_WRAP
};

enum class CompareFunction: uint32_t
{
    NEVER,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    NOT_EQUAL,
    ALWAYS
};

enum class BlendOperation: uint32_t
{
    ADD,
    SUBTRACT,
    RESERVE_SUBTRACT
};

enum class BlendFactor : uint32_t
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    CONSTANT_ALPHA,
    SRC_ALPHA_SATURATE,
    ONE_MINUS_CONSTANT_ALPHA,
    BLEND_CLOLOR
};

enum class ColorWriteMask: uint32_t
{
    NONE = 0x00000000,
    RED = 0x00000001,
    GREEN = 0x00000002,
    BLUE = 0x00000004,
    ALPHA = 0x00000008,
    ALL = 0x0000000F
};

struct SamplerDescriptor
{
    SamplerFilter magFilter = SamplerFilter::LINEAR;
    SamplerFilter minFilter = SamplerFilter::LINEAR;
    SamplerAddressMode sAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;
    SamplerAddressMode tAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;

    SamplerDescriptor() {}

    SamplerDescriptor(
            SamplerFilter _magFilter,
            SamplerFilter _minFilter,
            SamplerAddressMode _sAddressMode,
            SamplerAddressMode _tAddressMode
    ) : magFilter(_magFilter), minFilter(_minFilter),
        sAddressMode(_sAddressMode), tAddressMode(_tAddressMode) {}
};

enum class CullMode: uint32_t
{
    NONE = 0x00000000,
    BACK = 0x00000001,
    FRONT = 0x00000002
};

enum class Winding: uint32_t
{
    CLOCK_WISE,
    COUNTER_CLOCK_WISE
};

struct UniformInfo
{
    int count = 0;
    int location = -1;

    //in opengl, type means uniform data type, i.e. GL_FLOAT_VEC2, while in metal type means data basic type, i.e. float
    unsigned int type = 0;
    bool isArray = false;
    unsigned int size = 0;
    unsigned int bufferOffset = 0;

    //only used in metal
    bool isMatrix = false;
    bool needConvert = false;
};

struct UniformLocation
{
    /**
     * in metal, those two locations represent to vertex and fragment location.
     * in opengl, location[0] represent the location, and location[1] represent location offset in uniform buffer.
     */
    int location[2] = {-1, -1};
    ShaderStage shaderStage = ShaderStage::VERTEX;
    UniformLocation() = default;
    operator bool()
    {
        if(shaderStage == ShaderStage::VERTEX_AND_FRAGMENT)
            return location[0] >= 0 && location[1] >= 0;
        else
            return location[int(shaderStage)] >=0;
    }
    void reset() { location[0] = location[1] = -1; }
    bool operator == (const UniformLocation &other) const;
    std::size_t operator()(const UniformLocation &uniform) const;
};


struct AttributeBindInfo
{
    std::string attributeName;
    int         location    = -1;
    int         size        = 0;
    int         type        = 0;
};

enum class TextureCubeFace : uint32_t
{
    POSITIVE_X = 0,
    NEGATIVE_X = 1,
    POSITIVE_Y = 2,
    NEGATIVE_Y = 3,
    POSITIVE_Z = 4,
    NEGATIVE_Z = 5
};

enum class ProgramType : size_t
{
    Normal_Image
};

///built-in uniform name
static const char* UNIFORM_NAME_MVP_MATRIX = "u_MVPMatrix";
static const char* UNIFORM_NAME_TEXTURE = "u_texture";
static const char* UNIFORM_NAME_TEXTURE1 = "u_texture1";
static const char* UNIFORM_NAME_TEXTURE2 = "u_texture2";
static const char* UNIFORM_NAME_TEXTURE3 = "u_texture3";
static const char* UNIFORM_NAME_TEXT_COLOR = "u_textColor";
static const char* UNIFORM_NAME_EFFECT_COLOR = "u_effectColor";
static const char* UNIFORM_NAME_EFFECT_TYPE = "u_effectType";

///built-in attribute name
static const char* ATTRIBUTE_NAME_POSITION = "a_position";
static const char* ATTRIBUTE_NAME_COLOR = "a_color";
static const char* ATTRIBUTE_NAME_TEXCOORD = "a_texCoord";
static const char* ATTRIBUTE_NAME_TEXCOORD1 = "a_texCoord1";
static const char* ATTRIBUTE_NAME_TEXCOORD2 = "a_texCoord2";
static const char* ATTRIBUTE_NAME_TEXCOORD3 = "a_texCoord3";

/**
* @brief a structor to store blend descriptor
*/
struct BlendDescriptor
{
    ColorWriteMask writeMask = ColorWriteMask::ALL;

    bool blendEnabled = false;

    BlendOperation rgbBlendOperation = BlendOperation::ADD;
    BlendOperation alphaBlendOperation = BlendOperation::ADD;

    BlendFactor sourceRGBBlendFactor = BlendFactor::ONE;
    BlendFactor destinationRGBBlendFactor = BlendFactor::ZERO;
    BlendFactor sourceAlphaBlendFactor = BlendFactor::ONE;
    BlendFactor destinationAlphaBlendFactor = BlendFactor::ZERO;
};

enum class TextHAlignment
{
    LEFT,
    CENTER,
    RIGHT
};

enum class TextVAlignment
{
    TOP,
    CENTER,
    BOTTOM
};

enum class ClearFlag : uint8_t
{
    NONE = 0,
    COLOR = 1,
    DEPTH = 1 << 1,
    STENCIL = 1 << 2,
    ALL = COLOR | DEPTH | STENCIL
};
//ENABLE_BITMASK_OPERATORS(ClearFlag)

enum class RenderTargetFlag : uint8_t
{
    COLOR = 1,
    DEPTH = 1 << 1,
    STENCIL = 1 << 2,
    ALL = COLOR | DEPTH | STENCIL
};

struct Tex2F {
    Tex2F(float _u, float _v): u(_u), v(_v) {}

    Tex2F() {}

    float u = 0.f;
    float v = 0.f;
};

struct BlendFunc
{
    /** source blend function */
    BlendFactor src;
    /** destination blend function */
    BlendFactor dst;

    /** Blending disabled. Uses {BlendFactor::ONE, BlendFactor::ZERO} */
    static const BlendFunc DISABLE;
    /** Blending enabled for textures with Alpha premultiplied. Uses {BlendFactor::ONE, BlendFactor::ONE_MINUS_SRC_ALPHA} */
    static const BlendFunc ALPHA_PREMULTIPLIED;
    /** Blending enabled for textures with Alpha NON premultiplied. Uses {BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA} */
    static const BlendFunc ALPHA_NON_PREMULTIPLIED;
    /** Enables Additive blending. Uses {BlendFactor::SRC_ALPHA, BlendFactor::ONE} */
    static const BlendFunc ADDITIVE;

    bool operator==(const BlendFunc &a) const
    {
        return src == a.src && dst == a.dst;
    }

    bool operator!=(const BlendFunc &a) const
    {
        return src != a.src || dst != a.dst;
    }

    bool operator<(const BlendFunc &a) const
    {
        return src < a.src || (src == a.src && dst < a.dst);
    }
};

struct ScissorRect
{
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
};

struct Rect
{
    Vector2f origin;
    Vector2f size;
};

struct Color3B
{
            Color3B();
    Color3B(uint8_t _r, uint8_t _g, uint8_t _b);
    explicit Color3B(const Color4B& color);
    explicit Color3B(const Color4F& color);

    bool operator==(const Color3B& right) const;
    bool operator==(const Color4B& right) const;
    bool operator==(const Color4F& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4B& right) const;
    bool operator!=(const Color4F& right) const;

    bool equals(const Color3B& other) const
    {
        return (*this == other);
    }

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    static const Color3B WHITE;
    static const Color3B YELLOW;
    static const Color3B BLUE;
    static const Color3B GREEN;
    static const Color3B RED;
    static const Color3B MAGENTA;
    static const Color3B BLACK;
    static const Color3B ORANGE;
    static const Color3B GRAY;
    };

/**
* RGBA color composed of 4 bytes.
* @since v3.0
*/
struct Color4B
{
    Color4B();
    Color4B(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a);
    explicit Color4B(const Color3B& color, uint8_t _a = 255);
    explicit Color4B(const Color4F& color);

    inline void set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    bool operator==(const Color4B& right) const;
    bool operator==(const Color3B& right) const;
    bool operator==(const Color4F& right) const;
    bool operator!=(const Color4B& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4F& right) const;

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0;

    static const Color4B WHITE;
    static const Color4B YELLOW;
    static const Color4B BLUE;
    static const Color4B GREEN;
    static const Color4B RED;
    static const Color4B MAGENTA;
    static const Color4B BLACK;
    static const Color4B ORANGE;
    static const Color4B GRAY;
    };


/**
* RGBA color composed of 4 floats.
* @since v3.0
*/
struct Color4F
{
    Color4F();
    Color4F(float _r, float _g, float _b, float _a);
    explicit Color4F(const Color3B& color, float _a = 1.0f);
    explicit Color4F(const Color4B& color);

    bool operator==(const Color4F& right) const;
    bool operator==(const Color3B& right) const;
    bool operator==(const Color4B& right) const;
    bool operator!=(const Color4F& right) const;
    bool operator!=(const Color3B& right) const;
    bool operator!=(const Color4B& right) const;

    bool equals(const Color4F &other) const
    {
        return (*this == other);
    }

    float r = 0.f;
    float g = 0.f;
    float b = 0.f;
    float a = 0.f;

    static const Color4F WHITE;
    static const Color4F YELLOW;
    static const Color4F BLUE;
    static const Color4F GREEN;
    static const Color4F RED;
    static const Color4F MAGENTA;
    static const Color4F BLACK;
    static const Color4F ORANGE;
    static const Color4F GRAY;
    };

Color4F& operator+=(Color4F& lhs, const Color4F& rhs);
Color4F operator+(Color4F lhs, const Color4F& rhs);

Color4F& operator-=(Color4F& lhs, const Color4F& rhs);
Color4F operator-(Color4F lhs, const Color4F& rhs);

Color4F& operator*=(Color4F& lhs, const Color4F& rhs);
Color4F operator*(Color4F lhs, const Color4F& rhs);
Color4F& operator*=(Color4F& lhs, float rhs);
Color4F operator*(Color4F lhs, float rhs);

Color4F& operator/=(Color4F& lhs, const Color4F& rhs);
Color4F operator/(Color4F lhs, const Color4F& rhs);
Color4F& operator/=(Color4F& lhs, float rhs);
Color4F operator/(Color4F lhs, float rhs);


struct V3F_C4B_T2F
{
    Vec3     vertices;            // 12 bytes
    Color4F  colors;              // 4 bytes
    Tex2F    texCoords;           // 8 bytes
};

NS_STITCHES_END

