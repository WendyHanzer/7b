#ifndef PARTICLE_PROGRAM_RENDER_HPP
#define PARTICLE_PROGRAM_RENDER_HPP

#include "program.hpp"

class ParticleRenderProgram : public Program {
public:
    ParticleRenderProgram();
    virtual ~ParticleRenderProgram();

    void init();
    void bind();
    void unbind();

protected:
    void loadShaders();

    void initProgram();
    void initLocations();
};

#endif // PARTICLE_PROGRAM_RENDER_HPP