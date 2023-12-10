#version 330 core

in vec3 FragPos;
in vec3 Normal;
//in vec4 out_Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D outTexture;

void main()
{
    float ambientLight = 0.3;
    vec3 ambient = ambientLight * lightColor;

    vec3 normalVector = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseLight = max(dot(normalVector, lightDir), 0.0);
    vec3 diffuse = diffuseLight * lightColor;

    float shininess = 128.0;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalVector);
    float specularLight = max(dot(viewDir, reflectDir), 0.0);
    vec3 specular = pow(specularLight, shininess) * lightColor;

    vec4 result = texture(outTexture, TexCoord);
    result = vec4((ambient + diffuse), 1.0) * result + vec4(specular, 1.0);

    FragColor = result;
}