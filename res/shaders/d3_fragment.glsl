#version 430 core
layout(location = 0) out vec4 color;
uniform vec3 u_lightDirection;
in vec3 v_FragPos;

layout(std430, binding = 0) buffer normalsBuffer {
    vec4 normals[];
};
layout(std430, binding = 1) buffer normalIndiciesBuffer {
    uint normalIndicies[];
};
void main(){
    vec3 normal = vec3(normals[normalIndicies[gl_PrimitiveID]].x, normals[normalIndicies[gl_PrimitiveID]].y, normals[normalIndicies[gl_PrimitiveID]].z);
    float diff = max(dot(normal, u_lightDirection), 0.3);//u_lightDirection normalize(vec3(0,1,1))

    color = vec4(1*diff, 1*diff, 1*diff, 1.0f);
    //color = vec4(normal * 0.5 + 0.5, 1.0f);
}