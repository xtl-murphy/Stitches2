
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

class ShaderGL : public Shader
{
private:
    GLuint programId = 0;
    ShaderModuleGL* vertexShaderModule = nullptr;
    ShaderModuleGL* fragmentShaderModule = nullptr;

    std::vector<AttributeInfo> _attributeInfos;
    std::unordered_map<std::string, UniformInfo> _activeUniformInfos;

private:
    void compileProgram();
    bool getAttributeLocation(const String& attributeName, unsigned int& location) const;
    void computeUniformInfos();
    void computeLocations();

public:
    ShaderGL(const String& vertexShader, const String& fragmentShader);
    ~ShaderGL();


    virtual UniformLocation getUniformLocation(const String& uniform) const override;

    virtual UniformLocation getUniformLocation(Uniform name) const override;

    virtual int getAttributeLocation(const String& name) const override;

    virtual int getAttributeLocation(Attribute name) const override;

    virtual int getMaxVertexLocation() const override;

    virtual int getMaxFragmentLocation() const override;

    virtual const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const override;
};

NS_STITCHES_END

