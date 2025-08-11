#version 430 core
layout(location = 0) in vec3 position;
uniform mat4 u_projMatrix;
uniform mat4 u_observerPlane;
uniform mat4 u_worldPlaneTransf;
uniform vec3 u_lightDirection;
out vec3 v_FragPos;
out vec3 lightDirection;

void main() {
    vec4 pos = u_worldPlaneTransf * vec4(position,1.0f);
    pos = u_observerPlane * pos;//observer plane
    pos = u_projMatrix * pos;
    gl_Position = pos;//dalisana ar z notiek automatiski
    v_FragPos = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
    lightDirection = (u_worldPlaneTransf * vec4(u_lightDirection, 0.0)).xyz;
};