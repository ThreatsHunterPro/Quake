#version 330 core

out vec4 FragColor; 

#define dirSize 1
#define pointSize 1
#define spotSize 1

struct Lights{
    int dirLightsSize;
    int pointLightsSize;
    int spotLightsSize;

    //DirLight dirLights[dirLightsSize]
    //PointLight pointLights[lights.pointLightsSize];
    //SpotLight spotLights[lights.spotLightsSize];
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;   
    sampler2D emission;
    float shininess;
}; 

in vec3 position;
in vec3 normal;
in vec3 color;
in vec2 textureCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Lights lights;
uniform DirLight dirLights[dirSize];
uniform PointLight pointLights[pointSize];
uniform SpotLight spotLights[spotSize];

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // properties
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - position);
    vec3 result = vec3(0);

    // phase 1: Directional lighting
    for(int i = 0; i < dirSize; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < pointSize; i++)
        result += CalcPointLight(pointLights[i], norm, position, viewDir);
    // phase 3: Spot light
    for(int i = 0; i < spotSize; i++)
        result += CalcSpotLight(spotLights[i], norm, position, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, textureCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, textureCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, textureCoords));
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, textureCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, textureCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, textureCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, textureCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, textureCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, textureCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
