#ifndef DEFERRED_SHADING_PROGRAM_HPP
#define DEFERRED_SHADING_PROGRAM_HPP

#include "program.hpp"

class DeferredShadingProgram : public Program {
public:
    DeferredShadingProgram();
    virtual ~DeferredShadingProgram();

    void init();
    void bind();
    void unbind();

protected:
    void loadShaders();

    void initProgram();
    void initLocations();
};

#endif // DEFERRED_SHADING_PROGRAM_HPP