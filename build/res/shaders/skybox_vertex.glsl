#version 430 core
layout(location = 0) in vec3 aPos;
out vec3 vDir;

uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    mat4 rotView = mat4(mat3(u_view)); 
    vec4 worldPos = u_projection * rotView * vec4(aPos, 1.0);
    gl_Position = worldPos;
    vDir = aPos; 
}