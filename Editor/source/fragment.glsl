#version 410 core
out vec4 fragColor;

in vec4 color;
in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

uniform vec3 userColor;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 camPos;

void main()
{
	vec3 ambient = 0.1 * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float spec = pow(max(dot(lightDir, reflectDir),0.0),32);
	vec3 specular = 0.5 * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * userColor;
	fragColor = mix(texture(tex, texCoords), texture(tex2, texCoords), 0.4) * vec4(result, 1.0);
}