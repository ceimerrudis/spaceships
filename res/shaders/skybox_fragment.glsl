#version 430 core
in vec3 vDir;
out vec4 fragColor;

uniform samplerCube u_skybox;

void main() {
    fragColor = texture(u_skybox, normalize(vDir));
}