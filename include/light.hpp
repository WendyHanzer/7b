#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "gl.hpp"

#include <glm/glm.hpp>

struct AmbientLight
{
public:
    AmbientLight(const glm::vec3& c, float i, float diff)
        : color(c), intensity(i), diffIntensity(diff) {}

    glm::vec3 color;
    float intensity;
    float diffIntensity;
};

struct DirectionalLight : public AmbientLight
{
public:
    DirectionalLight(const glm::vec3 & c, const glm::vec3& dir, float i, float diff)
        : AmbientLight(c, i, diff), direction(dir) {}

    glm::vec3 direction;
};

struct PointLight : public AmbientLight
{
public:
    PointLight(const glm::vec3& c, const glm::vec3 &p, float i, float diff)
        : AmbientLight(c, i, diff), pos(p) {}

    struct {
        float constant, linear, exp;
    } attenuation;

    glm::vec3 pos;
};

using Light = AmbientLight;

#endif // LIGHT_HPP