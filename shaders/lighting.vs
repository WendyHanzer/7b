#version 410

in vec3 vs_pos;
in vec3 vs_norm;
in vec2 vs_uv;

out vec3 fs_norm;
out vec2 fs_uv;
uniform mat4 mvp;

void main(void) {
    gl_Position = mvp * vec4(vs_pos, 1.0);

    fs_norm = vs_norm;
    fs_uv = vs_uv;
}