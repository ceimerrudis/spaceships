#version 430 core
layout(location = 0) out vec4 color;
uniform sampler2D u_Texture;
in vec2 v_TexCoord;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    if (texColor.a < 0.01){
        discard;
    }
    color = texColor;
}
