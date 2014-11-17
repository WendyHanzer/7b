#ifndef GDAL_TERRAIN_HPP
#define GDAL_TERRAIN_HPP

#include "entity.hpp"
#include "vertex.hpp"
#include "gl.hpp"

#include <string>
#include <vector>

class Program;
class Texture;
class GDALDataset;

class GDALTerrain : public Entity {
public:
    GDALTerrain(Program *prog, const std::string& gdal_file);
    virtual ~GDALTerrain();

    virtual void init();
    virtual void tick(float dt);
    virtual void render();

private:
    std::vector<Vertex> geometry;
    Program *program;
    Texture *texture;
    std::string gdalFile;

    GDALDataset *dataset;
    GLuint vbo, vao;
};


#endif // GDAL_TERRAIN_HPP