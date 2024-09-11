#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec4 color;
out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;

uniform mat4 camMatrix;
uniform mat4 projMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = projMatrix * camMatrix * modelMatrix * vec4(aPos, 1.0);
	color = aColor;
	texCoords = aTexCoords;
	normal = aNormal;
	fragPos = vec3(modelMatrix * vec4(aPos, 1.0));
}