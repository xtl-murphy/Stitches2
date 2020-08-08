
/**
 * ShaderGL
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/8/1 19:31
 **/
#pragma once

#include "Stitches.hpp"
#include "Graphics/Base/Shader.hpp"
#include "Graphics/Platform.hpp"
#include "Graphics/Base/Types.hpp"
#include "ShaderModuleGL.hpp"
NS_STITCHES_BEGIN

struct AttributeInfo
{
    unsigned int location = 0;
    unsigned int size = 0;
    GLenum type = GL_BYTE;
    GLsizei stride = 0;
    unsigned int offset = 0;
    GLboolean needToBeNormallized = GL_FALSE;
    String name;
};

class ShaderGL final : public Shader
{
public:
    ShaderGL(const String& vertexShader, const String& fragmentShader);
    ~ShaderGL();

    inline GLuint getHandler() const { return mProgramId; }


    virtual UniformLocation getUniformLocation(const String& uniform) const override;

    virtual UniformLocation getUniformLocation(Uniform name) const override;

    virtual int getAttributeLocation(const String& name) const override;

    virtual int getAttributeLocation(Attribute name) const override;

    virtual int getMaxVertexLocation() const override;

    virtual int getMaxFragmentLocation() const override;

    virtual const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const override;

private:

    void compileProgram();
    bool getAttributeLocation(const String& attributeName, unsigned int& location) const;
    void computeUniformInfos();
    void computeLocations();

    GLuint mProgramId = 0;
    ShaderModuleGL* mVertexShaderModule = nullptr;
    ShaderModuleGL* mFragmentShaderModule = nullptr;

    std::vector<AttributeInfo> mAttributeInfos;
    std::unordered_map<std::string, UniformInfo> MactiveUniformInfos;

    std::size_t mTotalBufferSize = 0;
    int32 mMaxLocation = -1;
    UniformLocation mBuiltinUniformLocation[UNIFORM_MAX];
    int32 mBuiltinAttributeLocation[Attribute::ATTRIBUTE_MAX];
    std::unordered_map<int, int> mBufferOffset;

};
NS_STITCHES_END

