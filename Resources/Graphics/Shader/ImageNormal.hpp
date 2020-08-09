
const char* ImageNormalVert = R"(

attribute vec4 a_position;
attribute vec2 a_texCoord;

varying mediump vec2 v_texCoord;

uniform mat4 u_MVPMatrix;

void main()
{
    gl_Position = u_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
}
)";


const char* ImageNormalVertFrag = R"(

precision mediump float;

varying vec2 v_texCoord;

uniform sampler2D u_texture;

void main()
{
    gl_FragColor =  texture2D(u_texture, v_texCoord);
}
)";
