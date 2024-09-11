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

void main()
{
	vec3 ambient = 0.1 * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * userColor;
	fragColor = mix(texture(tex, texCoords), texture(tex2, texCoords), 0.4) * vec4(result, 1.0);
}