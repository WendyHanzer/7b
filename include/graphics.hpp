#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <vector>
#include <map>
#include <string>

#include "gl.hpp"
#include "scene.hpp"

#include <SDL.h>

#include <glm/glm.hpp>

class Engine;
class Camera;
//class Water;
//class Sparkler;
class Texture;
class Program;
class Cube;

class Graphics {
public:
    Graphics(Engine *eng);
    ~Graphics();

    void init();
    void tick(float dt);
    void render();
    void stop();

    void updateView();
    void updateCamera();
    void windowResized();

    void getWindowSize(int &w, int &h) const;
    Program* getShaderProgram(const std::string& name) const;

    SDL_Window* getRenderWindow() const {return window;}
    void setClearColor(const glm::vec3& color);
    glm::mat4 view, projection;

    Camera *camera;
    //Cube *cube;
    Scene *scene;
    //Water *water;
    //Sparkler *sparkler;
private:
    void initGL();
    void initScenes();

    Engine *engine;
    std::map<std::string, Program*> programs;

    SDL_Window *window;
    SDL_GLContext gl_context;
};

#endif // GRAPHICS_HPP
