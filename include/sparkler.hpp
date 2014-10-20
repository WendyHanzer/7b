#ifndef SPARKLER_HPP
#define SPARKLER_HPP

#include "gl.hpp"

#include <glm/glm.hpp>

#include <vector>

class Engine;
struct Vertex;

struct Particle
{
    glm::vec3 pos;
    unsigned char r,g,b,a;
    float size, angle, weight;
    float life;
};

class Sparkler
{
public:
    Sparkler(Engine *eng);
    ~Sparkler();

    void init();
    void initGL();
    void tick(float dt);
    void render();

private:
    Engine *engine;

    GLuint program;
    GLuint vbo_main, vbo_pos, vbo_color, vao_main, vao_pos, vao_color;

    GLint loc_pos, loc_mvp, loc_view, loc_normal, loc_texture, loc_model, loc_modelView, loc_specPower,
        loc_specIntensity, loc_camPos, loc_time, loc_ambient, loc_sampler;
    GLint loc_lightDir;

    int maxParticles, numParticles;

    std::vector<Vertex> geometry;
    glm::mat4 model;
    glm::
};

#endif // SPARKLER_HPP