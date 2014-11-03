#ifndef LIGHTING_PROGRAM_HPP
#define LIGHTING_PROGRAM_HPP

#include "program.hpp"

class LightingProgram : public Program {
public:
    LightingProgram();
    virtual ~LightingProgram();

    void init();
    void bind();
    void unbind();

protected:
    void loadShaders();

    void initProgram();
    void initLocations();
};

#endif // LIGHTING_PROGRAM_HPP