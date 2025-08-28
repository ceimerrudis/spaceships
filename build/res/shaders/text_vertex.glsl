#version 430 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoord;
out vec2 v_TexCoord;

void main() 
{
    v_TexCoord = textureCoord;
    gl_Position = vec4(position.x, position.y, 0, 1.0);
}
