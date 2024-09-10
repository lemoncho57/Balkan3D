#version 410 core
out vec4 fragColor;

in vec4 color;
in vec2 texCoords;

uniform vec3 userColor;
uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	fragColor = mix(texture(tex, texCoords), texture(tex2, texCoords), 0.4) * vec4(userColor, 1.0);
}