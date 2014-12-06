
#ifndef FLAG_PROG_HPP
#define FLAG_PROG_HPP

#include "program.hpp"

class FlagProgram : public Program {
public:
    FlagProgram();
    virtual ~FlagProgram();

    void init();
    void bind();
    void unbind();

protected:
    void loadShaders();

    void initProgram();
    void initLocations();
};

#endif // FLAG_PROG_HPP