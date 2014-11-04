#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/texture.h>

#include <iostream>
#include <fstream>

Mesh::Mesh(const char *fileName)
{
}

void Mesh::init()
{
    
}

void Mesh::render()
{

}

std::vector<Vertex> Mesh::load(const std::string& fileName)
{
    std::vector<Vertex> geometry;
    std::ifstream fileCheck(fileName);
    if(!fileCheck) {
        std::cerr << "Unable to open mesh file: " << fileName << std::endl;
        exit(1);
    }
    fileCheck.close();

    Assimp::Importer importer;
    
    auto scene = importer.ReadFile(fileName.c_str(), aiProcessPreset_TargetRealtime_Fast);
    
    if(!scene) {
        std::cerr << "unable to open assimp scene for file: " << fileName << std::endl;
        std::cerr << "assimp error: " << importer.GetErrorString() << std::endl;
        exit(1);
    }

    Vertex vert;

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        auto mesh = scene->mMeshes[i];

        for(unsigned int j = 0; j < mesh->mNumFaces; j++) {
            const auto& face = mesh->mFaces[j];

            for(unsigned int k = 0; k < face.mNumIndices; k++) {
                const auto& vertex = mesh->mVertices[face.mIndices[k]];

                vert.pos[0] = vertex.x;
                vert.pos[1] = vertex.y;
                vert.pos[2] = vertex.z;

                const auto& textureVertex = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][face.mIndices[k]] : aiVector3D(0,0,0);

                vert.texture[0] = textureVertex.x;
                vert.texture[1] = textureVertex.y;

                const auto& normals = mesh->mNormals[face.mIndices[k]];
                vert.normal[0] = normals.x;
                vert.normal[1] = normals.y;
                vert.normal[2] = normals.z;

                geometry.push_back(vert);
            }
        }
    }

    return geometry;
}

