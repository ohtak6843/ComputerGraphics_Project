#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec4 vColor;

out vec3 FragPos;
out vec3 Normal;
out vec4 out_Color;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main(void)
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);
	FragPos = vec3(modelTransform * vec4(vPos, 1.0f));
	Normal = mat3(transpose(inverse(modelTransform))) * vNormal;

	out_Color = vColor;
}