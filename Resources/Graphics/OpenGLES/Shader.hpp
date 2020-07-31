
/**
 * Shader
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/7/30 11:27
 **/

#pragma once

#include "Stitches.hpp"
#include "Graphics/Platform.hpp"

NS_STITCHES_BEGIN

class Shader
{
private:
    GLuint programId;
    GLuint vertexShader;
    GLuint fragmentShader;

public:
    Shader(const String& vsFile, const String& fsFile);

    Shader(const GLchar* inlineVert, const GLchar* inlineFrag);

    ~Shader();

    void Bind();

    void Unbind();

    const GLuint GetProgramID() const;

    GLuint GetUniformLocation(const GLchar* nameInShader) const;

    GLuint GetAttribLocation(const GLchar* nameInShader) const;

    void PrintActiveAttribs() const;

    void PrintActiveUniforms() const;

private:

    bool Init(const String& vsFile, const String& fsFile);

    bool Init(const GLchar* inlineVert, const GLchar* inlineFrag);

    bool CompileShader(GLuint* shader, GLenum type, const String& file);

    bool CompileShader(GLuint* shader, GLenum type, const GLchar* inlineFile);

    bool GLInit();

    bool GLCompileShader();

#ifdef ANDROID
    static const int32 ANDROID_ERROR_SIZE = 4096;
#endif

    Shader(const Shader& t);
    Shader(Shader&& t);
    Shader& operator=(const Shader& t);
    Shader& operator=(Shader&&);
};

NS_STITCHES_END
