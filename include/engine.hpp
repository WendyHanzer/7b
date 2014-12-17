#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>

struct Options {
    bool verbose;
    std::string color_map;
    std::vector<std::string> terrain;
    std::vector<std::string> shapes;
    float height_scalar;
    float map_scalar;
    bool wireframe;
    float camera_sensitivity;
    float camera_speed;
    std::string data_directory;
    float sample_probability;
    float density;
    float light_speed;
    int max_particles;

    std::vector<unsigned int> water_size;

    bool update_partial, loading_done;
};

class Input;
class Graphics;

class Engine {
public:
    Engine(int argc, char **argv);
    ~Engine();

    void init();
    int run();

    void stop(int exit_code = 0);

    Options& getOptions();
    std::vector<std::string> getCmdArgs() const;

    static Engine* getEngine();

    Input *input;
    Graphics *graphics;
private:
    void parseArgs();
    int _argc;
    char **_argv;

    Options options;

    static Engine* currentEngine;
};

#endif // ENGINE_HPP