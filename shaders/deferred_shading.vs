#version 410

layout (location = 0) in vec3 vs_pos;
layout (location = 1) in vec2 vs_uv;
layout (location = 2) in vec3 vs_norm;

uniform mat4 mvp;
uniform mat4 modelMatrix;

out vec2 fs_uv;
out vec3 fs_normals;
out vec3 fs_pos;

void main(void) {
    gl_Position = mvp * vec4(vs_pos, 1.0);
    fs_uv = vs_uv;
    fs_normals = (modelMatrix * vec4(vs_norm, 0.0)).xyz;
    fs_pos = (modelMatrix * vec4(vs_pos, 1.0)).xyz;
}