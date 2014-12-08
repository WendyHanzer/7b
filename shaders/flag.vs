#version 410

uniform float waveTime;
uniform float waveWidth;
uniform float waveHeight;

uniform mat4 mvp;
uniform mat4 modelMatrix;

in vec3 vs_pos;
in vec3 vs_norm;
in vec2 vs_uv;

out vec3 fs_norm;
out vec2 fs_uv;
out vec3 world_pos;

void main(void)
{
    vec4 v = vec4(vs_pos,1.0);
    v.y += cos(waveWidth * v.x + waveTime) * waveHeight;

    gl_Position = mvp * v;
    fs_uv = normalize(vs_uv);

    world_pos = (modelMatrix * vec4(vs_pos,1.0)).xyz;
    fs_norm = (modelMatrix * vec4(vs_norm, 0.0)).xyz;

}
