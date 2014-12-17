#ifndef PARTICLE_PROGRAM_UPDATE_HPP
#define PARTICLE_PROGRAM_UPDATE_HPP

#include "program.hpp"

class ParticleUpdateProgram : public Program {
public:
    ParticleUpdateProgram();
    virtual ~ParticleUpdateProgram();

    void init();
    void bind();
    void unbind();

protected:
    void loadShaders();

    void initProgram();
    void initLocations();
};

#endif // PARTICLE_PROGRAM_UPDATE_HPP