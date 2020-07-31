
/**
 * Shader
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/7/30 11:27
 **/
#include "Shader.hpp"

USING_STITCHES_VK

Shader::Shader(const String& vsFile, const String& fsFile)
        : programId(0)
        , vertexShader(0)
        , fragmentShader(0)
{
    this->Init(vsFile, fsFile);
}

Shader::Shader(const GLchar* inlineVert, const GLchar* inlineFrag)
        : programId(0)
        , vertexShader(0)
        , fragmentShader(0)
{
    Init(inlineVert,inlineFrag);
}

Shader::~Shader()
{
    glDeleteProgram(this->programId);
}

bool Shader::Init(const String& vsFile, const String& fsFile)
{
    if(!CompileShader(&this->vertexShader, GL_VERTEX_SHADER, vsFile))
    {
        return false;
    }

    if(!CompileShader(&this->fragmentShader, GL_FRAGMENT_SHADER, fsFile))
    {
        return false;
    }

    return GLInit();
}

bool Shader::Init(const GLchar* inlineVert, const GLchar* inlineFrag)
{
    if(!CompileShader(&this->vertexShader, GL_VERTEX_SHADER, inlineVert ))
    {
        return false;
    }

    if(!CompileShader(&this->fragmentShader, GL_FRAGMENT_SHADER, inlineFrag))
    {
        return false;
    }
    return GLInit();
}

bool Shader::GLInit()
{
    this->programId = glCreateProgram();

    if(this->programId == 0)
    {
        LOGE("Shader", "Failed to create program!");
    }

    glAttachShader(this->programId, this->vertexShader);
    glAttachShader(this->programId, this->fragmentShader);

    glLinkProgram(this->programId);
    GLint status;
    glGetProgramiv(this->programId, GL_LINK_STATUS, &status);
    if(!status)
    {
        GLint infoLen(0);
        glGetProgramiv(this->programId, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1)
        {
//            schar* infoLog = new schar[infoLen];
//            glGetProgramInfoLog(m_ProgramID, infoLen, NULL, infoLog);
//            tstringstream buffer;
//            buffer	<< _T("Shader::GLInit: Failed to link program: ")
//                      << infoLog;
//            LOG(LogLevel::Error, buffer.str(),
//                STARENGINE_LOG_TAG);
//            delete infoLog;

        }
        else
        {
//            schar* infoLog = new schar[ANDROID_ERROR_SIZE];
//            glGetProgramInfoLog(m_ProgramID, ANDROID_ERROR_SIZE, NULL, infoLog);
//            tstringstream buffer;
//            buffer << _T("Shader::GLInit: Failed to link program: ")
//                    << infoLog;
//            LOG(LogLevel::Error, buffer.str());
//            delete infoLog;

        }

        glDeleteProgram(this->programId);
        return false;
    }
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);

    return true;
}

bool Shader::CompileShader(GLuint* shader, GLenum type, const String& file)
{
    char* source;
    uint32 size;
    char* buffer = ReadBinaryFile(file, size);
    source = new char[size+1];
    memcpy(source, buffer, size);

    delete [] buffer;

    source[size] = '\0';

    bool returnValue(CompileShader(shader, type, source));

    delete[] source;

    return returnValue;
}

bool Shader::CompileShader(GLuint* shader, GLenum type, const GLchar* inlineFile)
{
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &inlineFile, NULL);
    glCompileShader(*shader);
    GLint status;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if(status == 0)
    {
        GLint infolength;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &infolength);
        if (infolength > 1)
        {
//            schar* buf = new schar[infolength];
//            if (buf)
//            {
//                tstring stringType;
//                switch(type)
//                {
//                    case GL_VERTEX_SHADER:
//                        stringType = _T("GL_VERTEX_SHADER");
//                        break;
//                    case GL_FRAGMENT_SHADER:
//                        stringType = _T("GL_FRAGMENT_SHADER");
//                        break;
//                    default:
//                        stringType = _T("UNKNOWN_SHADER_TYPE");
//                        break;
//                }
//                glGetShaderInfoLog(*shader, infolength, NULL, buf);
//                tstringstream buffer;
////                buffer	<< _T("Shader::CompileShader: \
////Could not compile shader of type ")
////                          << stringType
////                          << _T(": ")
////                          << buf;
////                LOG(LogLevel::Error,
////                    buffer.str(), STARENGINE_LOG_TAG);
//                delete buf;
//            }
        }
        else
        {
//            //This is necessary due to an Android bug!
//            schar* buf = new schar[ANDROID_ERROR_SIZE];
//            if (buf)
//            {
//                tstring stringType;
//                switch(type)
//                {
//                case GL_VERTEX_SHADER:
//                    stringType = _T("GL_VERTEX_SHADER");
//                    break;
//                case GL_FRAGMENT_SHADER:
//                    stringType = _T("GL_FRAGMENT_SHADER");
//                    break;
//                default:
//                    stringType = _T("UNKNOWN_SHADER_TYPE");
//                    break;
//                }
//                glGetShaderInfoLog(*shader, ANDROID_ERROR_SIZE, NULL, buf);
//                tstringstream buffer;
//                buffer 	<< _T("Shader::CompileShader: \
//Could not compile shader of type ")
//                        << stringType
//                        << _T(": ")
//                        << buf;
//                LOG(LogLevel::Error,
//                    buffer.str(), STARENGINE_LOG_TAG);
//                delete buf;
//            }
        }
        glDeleteShader(*shader);
        shader = 0;
        return false;
    }
    return true;
}

void Shader::Bind()
{
    glUseProgram(this->programId);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

const GLuint Shader::GetProgramID() const
{
    return this->programId;
}

GLuint Shader::GetUniformLocation(const GLchar* nameInShader) const
{
    return glGetUniformLocation(this->programId, nameInShader);
}

GLuint Shader::GetAttribLocation(const GLchar* nameInShader) const
{
    return glGetAttribLocation(this->programId, nameInShader);
}

void Shader::PrintActiveAttribs() const
{
    GLint nAttribs;
    GLsizei maxLength;

    glGetProgramiv(this->programId, GL_ACTIVE_ATTRIBUTES, &nAttribs);
    glGetProgramiv(this->programId, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    GLchar* name = new GLchar[maxLength];

    GLint written, size, location;
    GLenum type;

    for(GLuint i = 0; i < GLuint(nAttribs); ++i)
    {
        glGetActiveAttrib(
                this->programId,
                i,
                maxLength,
                &written,
                &size,
                &type,
                name
        );
        location = glGetAttribLocation(this->programId, name);
//        Logger::GetInstance()->
//                DebugLog(LogLevel::Info,
//                         string_cast<tstring>(location) +
//                         _T(" | ") +
//                         string_cast<tstring>(name),
//                         STARENGINE_LOG_TAG
//        );
    }
    delete[] name;
}

void Shader::PrintActiveUniforms() const
{
    GLint nUniforms;
    GLsizei maxLength;

    glGetProgramiv(this->programId, GL_ACTIVE_UNIFORMS, &nUniforms);
    glGetProgramiv(this->programId, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

    GLchar* name = new GLchar[maxLength];

    GLint size, location;
    GLsizei written;
    GLenum type;

    for(GLuint i = 0; i < GLuint(nUniforms); ++i)
    {
        glGetActiveUniform(
                this->programId,
                i,
                maxLength,
                &written,
                &size,
                &type,
                name
        );
        location = glGetUniformLocation(this->programId, name);
    }
    delete[] name;
}
