#version 430 core
layout(location = 0) out vec4 color;
uniform sampler2D u_Texture;
in vec2 v_TexCoord;

void main()
{
    vec3 textColor = vec3(0,0,1);
    float intensity = texture(u_Texture, v_TexCoord).r;
    float alpha = texture(u_Texture, v_TexCoord).r;
    vec4 texColor = vec4(textColor * intensity, alpha);
    if (texColor.a < 0.01){
        discard;
    }
    color = texColor;
}
