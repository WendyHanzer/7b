#version 410

struct AmbientLight {
    vec3 color;
    float intensity;
    float diffIntensity;
};

struct DirectionalLight {
    AmbientLight ambient;
    vec3 direction;
};

struct Attenuation {
    float constant;
    float linear;
    float ex;
};

struct PointLight {
    AmbientLight ambient;
    Attenuation attenuation;
    vec3 pos;
};

struct SpotLight {
    PointLight point;
    vec3 direction;
    float cutoff;
};

uniform vec3 light_dir;
uniform vec3 cameraPos;
uniform float specularIntensity, specularPower;
uniform float ambientIntensity, diffuseIntensity;
uniform sampler2D tex;
uniform vec3 pointLightPos;
uniform vec3 spotLightDir;

in vec3 fs_norm;
in vec2 fs_uv;
in vec3 world_pos;
out vec4 glColor;

vec4 calcInternalLight(AmbientLight amb, vec3 lightDirection, vec3 normal)
{
    float diffFactor = dot(normal, -lightDirection);
    vec4 ambientColor = vec4(amb.color, 1.0) * amb.intensity;

    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);

    if(diffFactor > 0) {
        diffuseColor = vec4(amb.color, 1.0) * amb.diffIntensity * diffFactor;


        vec3 vertexToView = normalize(cameraPos - world_pos);
        vec3 lightReflect = normalize(reflect(-lightDirection, normal));
        float specularFactor = max(0.0, dot(vertexToView, lightReflect));

        if(specularFactor > 0) {
            specularFactor = pow(specularFactor, specularPower);
            specularColor = vec4(amb.color, 1.0) * specularIntensity * specularFactor;
        }
    }

    return ambientColor + diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight dir, vec3 normals)
{
    vec4 color = calcInternalLight(dir.ambient, dir.direction, normals);
    return color;
}

vec4 calcPointLight(PointLight pLight, vec3 normals)
{
    vec3 lightDir = world_pos - pLight.pos;
    float distance = length(lightDir);
    lightDir = normalize(lightDir);

    vec4 color = calcInternalLight(pLight.ambient, lightDir, normals);
    float attenuation = pLight.attenuation.constant +
                        (pLight.attenuation.linear * distance) +
                        (pLight.attenuation.ex * distance * distance);


    return color / attenuation;
}

vec4 calcSpotLight(SpotLight sLight, vec3 normals) {
    vec3 lightToPixel = normalize(world_pos - sLight.point.pos);
    float spotFactor = dot(lightToPixel, sLight.direction);

    if(spotFactor > sLight.cutoff) {
        vec4 color = calcPointLight(sLight.point, normals);
        return color * (1.0 - (1.0 - spotFactor) * 1.0 / (1.0 - sLight.cutoff));
    }

    else {
        return vec4(0,0,0,0);
    }
}

void main() {
    AmbientLight light;
    light.color = vec3(1,1,1);
    light.intensity = ambientIntensity;
    light.diffIntensity = diffuseIntensity;

    DirectionalLight d_light;
    d_light.ambient = light;
    d_light.direction = light_dir;

    Attenuation atten;
    atten.constant = 1;
    atten.linear = 0.005;
    atten.ex = 0.0;

    PointLight p_light;
    p_light.ambient = light;
    p_light.pos = cameraPos;
    p_light.attenuation = atten;

    SpotLight s_light;
    s_light.point = p_light;
    s_light.direction = normalize(spotLightDir);
    s_light.cutoff = 0.95;

    vec4 totalLight = vec4(0,0,0,0);

    totalLight += calcDirectionalLight(d_light, fs_norm);
    //totalLight += calcPointLight(p_light, fs_norm);
    totalLight += calcSpotLight(s_light, fs_norm);

    glColor = vec4((texture(tex, fs_uv) * totalLight).xyz, 1.0);
}
