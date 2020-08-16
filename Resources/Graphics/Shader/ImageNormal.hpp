
const char* ImageNormalVert = R"(

#version 300 es
precision highp float;

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec2 a_texCoord;

out mediump vec2 v_texCoord;

uniform highp mat4 u_MVPMatrix;

void main()
{
    gl_Position = u_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
}
)";


const char* ImageNormalVertFrag = R"(

#version 300 es
precision mediump float;

in vec2 v_texCoord;

uniform sampler2D u_texture;

void main()
{
    gl_FragColor =  texture(u_texture, v_texCoord);
}
)";
