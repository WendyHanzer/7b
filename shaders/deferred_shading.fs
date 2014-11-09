#version 410

in vec2 fs_uv;
in vec3 fs_normals;
in vec3 fs_pos;

layout (location = 0) out vec3 pos_out;
layout (location = 1) out vec3 diff_out;
layout (location = 2) out vec3 normal_out;
layout (location = 3) out vec3 tex_out;

uniform sampler2D colorMap;

void main(void) {
    pos_out = fs_pos;
    diff_out = texture(colorMap, fs_uv).xyz;
    normal_out = normalize(fs_normals);
    tex_out = vec3(fs_uv, 0.0);
}