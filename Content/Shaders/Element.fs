#version 330 core

out vec4 FragColor; 

#define dirSize 1
#define pointSize 1
#define spotSize 1

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

in VS_OUT {
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 textureCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform Material material;
uniform DirLight dirLights[dirSize];
uniform PointLight pointLights[pointSize];
uniform SpotLight spotLights[spotSize];
uniform sampler2D shadowMap;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir);

void main()
{
    //properties
    vec3 norm = normalize(fs_in.normal);
    vec3 viewDir = normalize(viewPos - fs_in.position);
    float gamma = 2.2;
    vec3 result = vec3(0);

    //phase 1: Directional lighting
    for(int i = 0; i < dirSize; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);
    //phase 2: Point lights
    for(int i = 0; i < pointSize; i++)
        result += CalcPointLight(pointLights[i], norm, fs_in.position, viewDir);
    //phase 3: Spot light
    //for(int i = 0; i < spotSize; i++)
    //    result += CalcSpotLight(spotLights[i], norm, fs_in.position, viewDir);

    vec4 toGamma = vec4(result, 1.0);
    FragColor.rgb = pow(toGamma.rgb, vec3(1.0/gamma));
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);    
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, fs_in.textureCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, fs_in.textureCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.textureCoords));

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, lightDir);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    return lighting;
    //return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, fs_in.textureCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, fs_in.textureCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.textureCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, lightDir);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    return lighting;
    //return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.textureCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.textureCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.textureCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, lightDir);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    return lighting;
    //return (ambient + diffuse + specular);
}

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).x; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(fs_in.normal, lightDir)), 0.005); 
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    if (projCoords.z > 1.0)
        shadow = 0.0;
    return shadow;
}