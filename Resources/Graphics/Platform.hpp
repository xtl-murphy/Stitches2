
/**
 * Platform
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/7/30 11:34
 **/

#pragma once

#include <glad/glad.h>

//#define GLFW_INCLUDE_ES3
//#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>





#define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
            LOGE("OpenGLES", "OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)

