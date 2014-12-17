#include "gdalterrain.hpp"
#include "lighting.hpp"
#include "texture.hpp"

#include <gdal_priv.h>
#include <cpl_conv.h>
#include <ogr_srs_api.h>
#include <ogr_spatialref.h>

#include <iostream>
#include <engine.hpp>
#include <glm/gtc/matrix_transform.hpp>


GDALTerrain::GDALTerrain(Program *prog, const std::string& gdal_file)
    : program(prog), gdalFile(gdal_file)
{
    init();
}

GDALTerrain::~GDALTerrain()
{
    GDALClose((GDALDatasetH) dataset);
}

void GDALTerrain::init()
{
    dataset = (GDALDataset*) GDALOpen(gdalFile.c_str(), GA_ReadOnly);

    if(dataset == nullptr) {
        std::cerr << "Unable to open GDAL File: " << gdalFile << std::endl;
        exit(1);
    }

    auto raster = dataset->GetRasterBand(1);

    width = raster->GetXSize();
    height = raster->GetYSize();

    int gotMin, gotMax;
    float min = (float) raster->GetMinimum(&gotMin);
    float max = (float) raster->GetMaximum(&gotMax);

    double minMax[2] = {min, max};

    if(!(gotMin && gotMax)) {
        GDALComputeRasterMinMax((GDALRasterBandH) raster, TRUE, minMax);
        min = (float) minMax[0];
        max = (float) minMax[1];
    }

    if(Engine::getEngine()->getOptions().verbose) {
        std::cout << "terrain: " << gdalFile << " x: " << width << " y: " << height << "   min: " << min << " max: " << max << std::endl;
    }

    Vertex vert;

    vert.normal[0] = 0;
    vert.normal[1] = 1;
    vert.normal[2] = 0;

    float scale = Engine::getEngine()->getOptions().map_scalar;
    heightScale = 100.0f;

    gdal_data = std::vector<std::vector<float>>(height, std::vector<float>(width, 0.0f));

    float *lineData1 = new float[width];
    float *lineData2 = new float[width];

    float range = max - min;

    for(int z = 0; z < height-1; z++) {
        raster->RasterIO(GF_Read, 0, z, width, 1, lineData1, width, 1, GDT_Float32, 0, 0);
        raster->RasterIO(GF_Read, 0, z+1, width, 1, lineData2, width, 1, GDT_Float32, 0, 0);

        gdal_data[z].assign(lineData1, lineData1+width);
        gdal_data[z+1].assign(lineData2, lineData2+width);

        for(int x = 0; x < width-1; x++) {
            vert.pos[0] = x * scale;
            vert.pos[1] = heightScale * (lineData1[x]-min)/range;
            vert.pos[2] = z * scale;

            vert.texture[0] = x;// / float(width);
            vert.texture[1] = z;// / float(height);

            calcNormal(x, z, vert, min, range);

            geometry.push_back(vert);

            vert.pos[0] = (x+1) * scale;
            vert.pos[1] = heightScale * (lineData1[x+1]-min)/range;
            vert.pos[2] = z * scale;

            vert.texture[0] = (x+1);// / float(width);
            vert.texture[1] = z;// / float(height);

            calcNormal(x, z, vert, min, range);

            geometry.push_back(vert);

            vert.pos[0] = x * scale;
            vert.pos[1] = heightScale * (lineData2[x]-min)/range;
            vert.pos[2] = (z+1) * scale;

            vert.texture[0] = x;// / float(width);
            vert.texture[1] = (z+1);// / float(height);

            calcNormal(x, z, vert, min, range);

            geometry.push_back(vert);



            vert.pos[0] = x * scale;
            vert.pos[1] = heightScale * (lineData2[x]-min)/range;
            vert.pos[2] = (z+1) * scale;

            vert.texture[0] = x;// / float(width);
            vert.texture[1] = (z+1);// / float(height);

            calcNormal(x, z, vert, min, range);

            geometry.push_back(vert);

            vert.pos[0] = (x+1) * scale;
            vert.pos[1] = heightScale * (lineData2[x+1]-min)/range;
            vert.pos[2] = (z+1) * scale;

            vert.texture[0] = (x+1);// / float(width);
            vert.texture[1] = (z+1);// / float(height);

            calcNormal(x, z, vert, min, range);

            geometry.push_back(vert);

            vert.pos[0] = (x+1) * scale;
            vert.pos[1] = heightScale * (lineData1[x+1]-min)/range;
            vert.pos[2] = z * scale;

            vert.texture[0] = (x+1);// / float(width);
            vert.texture[1] = z;// / float(height);

            calcNormal(x, z, vert, min, range);

            geometry.push_back(vert);

        }
    }

   // for(int i = 0; i < geometry.size(); i++) {
     //   if(i % 6 == 0)
       // std::cout << i << ": " << geometry[i].pos[1] << std::endl;
    //}

    std::cout << "size: " << geometry.size() << std::endl;

    delete[] lineData1;
    delete[] lineData2;

    Vertex *geo = geometry.data();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); 
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * geometry.size(), geo, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(program->getLocation("vs_pos"),
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex,pos));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(program->getLocation("vs_norm"),
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex,normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(program->getLocation("vs_uv"),
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex,texture));

    texture = new Texture("../assets/desert.jpg", GL_TEXTURE_2D);

    //model = glm::translate(model, glm::vec3(width/2, 0, height/2));
}

void GDALTerrain::tick(float dt)
{

}

void GDALTerrain::render()
{
    if(!Engine::getEngine()->getOptions().update_partial)
        return;

    static int i = 1;
    program->bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    texture->bind(GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, i);

    if(i < geometry.size()-width*10)
        i += width*10;

    else {
        Engine::getEngine()->getOptions().loading_done = true;
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    program->unbind();
}

void GDALTerrain::calcNormal(int x, int z, Vertex& vert, float min, float max)
{
    glm::vec3 normal, center, up, down, left, right;

    if(x > 0 && z > 0) {
        center = glm::vec3(vert.pos[0], vert.pos[1], vert.pos[2]);

        up.z = z + 1;
        up.x = x;
        up.y = heightScale * (gdal_data[z + 1][x] - min) / max;

        down.z = z - 1;
        down.x = x;
        down.y = heightScale * (gdal_data[z - 1][x] - min) / max;

        left.z = z;
        left.x = x - 1;
        left.y = heightScale * (gdal_data[z][x - 1] - min) / max;

        right.z = z;
        right.x = x + 1;
        right.y = heightScale * (gdal_data[z][x + 1] - min) / max;

        normal += glm::cross(up-center, right-center);
        normal += glm::cross(right-center, down-center);
        normal += glm::cross(down-center, left-center);
        normal += glm::cross(left-center, up-center);
        normal = glm::normalize(normal);

        vert.normal[0] = normal.x;
        vert.normal[1] = normal.y;
        vert.normal[2] = normal.z;
    }

}

void GDALTerrain::center()
{
    model = glm::translate(model, glm::vec3(-width/2, 0, -height/2));
}