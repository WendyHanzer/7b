#version 410

in vec3 vs_pos;
in vec3 vs_norm;
in vec2 vs_uv;

out vec3 fs_norm;
out vec2 fs_uv;
out vec3 world_pos;

uniform mat4 mvp;
uniform mat4 modelMatrix;

void main(void) {
    vec4 pos = mvp * vec4(vs_pos, 1.0);
    gl_Position = pos;

    world_pos = (modelMatrix * vec4(vs_pos,1.0)).xyz;

    fs_norm = (modelMatrix * vec4(vs_norm, 0.0)).xyz;
    fs_uv = vs_uv;
}
