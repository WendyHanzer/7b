#include "gdalterrain.hpp"
#include "lighting.hpp"
#include "texture.hpp"

#include <gdal_priv.h>
#include <cpl_conv.h>
#include <ogr_srs_api.h>
#include <ogr_spatialref.h>


GDALTerrain::GDALTerrain(Program *prog, const std::string& gdal_file)
    : program(prog), gdalFile(gdal_file)
{
    init();
}

GDALTerrain::~GDALTerrain()
{

}

void GDALTerrain::init()
{

}

void GDALTerrain::tick(float dt)
{

}

void GDALTerrain::render()
{

}
