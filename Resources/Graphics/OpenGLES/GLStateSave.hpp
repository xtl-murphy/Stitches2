
/**
 * GLStateSave
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/7/21 9:50
 **/

#pragma once

#include "Stitches.hpp"
#include "Graphics/Platform.hpp"

NS_STITCHES_BEGIN

class GLStateSave
{
private:
    GLint	Blend;
    GLint	BlendDstAlpha;
    GLint	BlendDstRGB;
    GLint	BlendEquationAlpha;
    GLint	BlendEquationRgb;
    GLint	BlendSrcAlpha;
    GLint	BlendSrcRGB;

    GLint	ElementArrayBuffer;
    GLint	ArrayBuffer;
    static const int MAX_ATTRIBS = 4;
    GLint	vertexAttribArrayEnabled[MAX_ATTRIBS];

    GLint	ScissorTest;
    GLint	ScissorBox[4];

    GLint	DepthTest;
    GLint	DepthFunc;
    GLint	DepthWriteMask;

    GLint   CullFace;
public:
    GLStateSave();
    ~GLStateSave();

    void Enable(const GLenum feature, GLboolean enabled);
};

NS_STITCHES_END
