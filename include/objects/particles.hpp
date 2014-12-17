#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "gl.hpp"
#include "entity.hpp"

#include <glm/vec3.hpp>

struct Particle {
    float type;
    glm::vec3 pos, vel;
    float lifetime;
};

class Program;
class Texture;

class ParticleSystem : public Entity {
public:
    ParticleSystem(Program *_update, Program *_render);
    ~ParticleSystem();

    void initWithPos(const glm::vec3& pos);

    void renderWithDT(float dt);

private:
    void updateParticles(float dt);
    void renderParticles();

    bool isFirst;
    unsigned int currVB, currTFB;
    GLuint particleBuffer[2], transformFeedback[2], vao;
    float time;

    Program *update_prog, *render_prog;
    Texture *texture, *random_texture;
};

#endif // PARTICLE_HPP

// class ParticleSystem
// {
// public:
//     ParticleSystem();

//     ~ParticleSystem();

//     bool InitParticleSystem(const Vector3f& Pos);

//     void Render(int DeltaTimeMillis, const Matrix4f& VP, const Vector3f& CameraPos);

// private:

//     bool m_isFirst;
//     unsigned int m_currVB;
//     unsigned int m_currTFB;
//     GLuint m_particleBuffer[2];
//     GLuint m_transformFeedback[2];
//     PSUpdateTechnique m_updateTechnique;
//     BillboardTechnique m_billboardTechnique;
//     RandomTexture m_randomTexture;
//     Texture* m_pTexture;
//     int m_time;
// };
