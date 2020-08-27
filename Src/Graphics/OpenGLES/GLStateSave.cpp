
/**
 * GLStateSave
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/7/21 9:50
 **/

#include "GLStateSave.hpp"

USING_STITCHES_VK

static const bool exclusivelyVAO = false;

GLStateSave::GLStateSave()
{
    glGetIntegerv(GL_BLEND, &Blend);
    glGetIntegerv(GL_BLEND_DST_ALPHA, &BlendDstAlpha);
    glGetIntegerv(GL_BLEND_DST_RGB, &BlendDstRGB);
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &BlendEquationAlpha);
    glGetIntegerv(GL_BLEND_EQUATION_RGB, &BlendEquationRgb);
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &BlendSrcAlpha);
    glGetIntegerv(GL_BLEND_SRC_RGB, &BlendSrcRGB);

    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &ArrayBuffer);

    if (!exclusivelyVAO)
    {
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &ElementArrayBuffer);
        for (int i = 0 ; i < MAX_ATTRIBS ; i++)
        {
            glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &vertexAttribArrayEnabled[i]);
        }
    }

    glGetIntegerv(GL_SCISSOR_TEST, &ScissorTest);
    glGetIntegerv(GL_SCISSOR_BOX, ScissorBox);
    glGetIntegerv(GL_DEPTH_TEST, &DepthTest);
    glGetIntegerv(GL_DEPTH_FUNC, &DepthFunc);
    glGetIntegerv(GL_DEPTH_WRITEMASK, &DepthWriteMask);
    glGetIntegerv(GL_CULL_FACE, &CullFace);
    glGetFloatv(GL_COLOR_CLEAR_VALUE, &ClearColor[0]);
}

GLStateSave::~GLStateSave()
{
    glBlendEquationSeparate(BlendEquationRgb, BlendEquationAlpha);
    glBlendFuncSeparate(BlendSrcRGB, BlendDstRGB, BlendSrcAlpha, BlendDstAlpha);
    Enable(GL_BLEND, Blend);

    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);

    if (exclusivelyVAO) {
//        glBindVertexArrayOES(0);
    } else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementArrayBuffer);
        for (int i = 0 ; i < MAX_ATTRIBS ; i++)
        {
            if (vertexAttribArrayEnabled[i])
            {
                glEnableVertexAttribArray(i);
            }
            else
            {
                glDisableVertexAttribArray(i);
            }
        }
    }

    Enable(GL_SCISSOR_TEST, ScissorTest);
    glScissor(ScissorBox[0], ScissorBox[1], ScissorBox[2], ScissorBox[3]);

    Enable(GL_DEPTH_TEST, DepthTest);
    glDepthFunc(DepthFunc);

    glDepthMask(DepthWriteMask);

    Enable(GL_CULL_FACE, CullFace);
    glClearColor(ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3]);
}

void GLStateSave::Enable(const GLenum feature, GLboolean enabled)
{
    if (enabled)
    {
        glEnable(feature);
    }
    else
    {
        glDisable(feature);
    }
}
