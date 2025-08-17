#version 430 core
layout(location = 0) out vec4 color;
in vec3 lightDirection;
in vec3 v_FragPos;
uniform vec3 u_viewPos;

layout(std430, binding = 0) buffer normalsBuffer {
    vec3 normals[];
};
layout(std430, binding = 1) buffer normalIndiciesBuffer {
    uint normalIndicies[];
};
void main(){
    vec3 viewDir = normalize(u_viewPos - v_FragPos);
    vec3 normal = normals[normalIndicies[gl_PrimitiveID]];

    float diff = max(dot(normal, normalize(lightDirection)), 0.3);

    color = vec4(1*diff, 1*diff, 1*diff, 1.0f);
}