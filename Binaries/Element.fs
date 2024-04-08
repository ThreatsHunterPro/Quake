#version 330 core

out vec4 FragColor;
  
struct Light 
{
    vec3 position; // Point light
    vec3 direction; // Directionnal

    // SpotLight
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
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
uniform float time;
uniform Light light;
uniform Material material;

void main()
{
    //vec3 lightDir = normalize(light.position - position);
    //float theta = dot(lightDir, normalize(-light.direction));
    //vec3 result = vec3(0);
    //if (theta > light.cutOff)
    //{
    //    float distance = length(light.position - position);
    //    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    //    // ambient
    //    vec3 ambient = light.ambient * texture(material.diffuse, textureCoords).rgb;
    //    // diffuse 
    //    vec3 norm = normalize(normal);
    //    //vec3 lightDir = normalize(light.position - position); // Point light
    //    //vec3 lightDir = normalize(-light.direction); // Directionnal
    //    float diff = max(dot(norm, lightDir), 0.0);
    //    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCoords).rgb;  
    //    // specular
    //    vec3 viewDir = normalize(viewPos - position);
    //    vec3 reflectDir = reflect(-lightDir, norm);  
    //    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //    vec3 specularMap = vec3(texture(material.specular, textureCoords));
    //    vec3 specular = light.specular * spec * texture(material.specular, textureCoords).rgb;  
    //    // emission
    //    vec2 myTexCoords = textureCoords;
    //    myTexCoords.x = myTexCoords.x + 0.045f; // slightly shift texture on x for better alignment
    //    vec3 emissionMap = vec3(texture(material.emission, myTexCoords + vec2(0.0, time * 0.75f)));
    //    vec3 emissionMask = step(vec3(1.0f), vec3(1.0f) - specularMap);
    //    vec3 emission = emissionMap * emissionMask * (sin(time) * 0.5f + 0.5f) * 2.0;
    //    //emission *= attenuation;
    //    // Attenuation
    //    //ambient *= attenuation;
    //    diffuse *= attenuation;
    //    specular *= attenuation;
    //    float epsilon = light.cutOff - light.outerCutOff;
    //    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    //    diffuse  *= intensity;
    //    specular *= intensity;
    //    result = ambient + diffuse + specular /*+ emission*/;
    //}
    //else
    //{
    //    result = light.ambient * vec3(texture(material.diffuse, textureCoords));
    //}
    // FragColor = vec4(result, 1.0);

    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, textureCoords).rgb;
    
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, textureCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, textureCoords).rgb;  
    
    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    //ambient *= intensity; // Hide everything outside conesight
    diffuse *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient *= attenuation; 
    diffuse *= attenuation;
    specular *= attenuation;   
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}