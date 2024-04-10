#version 330 core

out vec4 color;

in vec4 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//color = vec4(1, 0, 0, 1); // static color
	color = ourColor; // change shader color
	//color = texture(texture2, texCoord); // apply one texture
	//color = texture(texture2, texCoord) * ourColor; // apply one texture
	//color = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2); // mix multiple textures
	//color = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2) * ourColor; // mix multiple textures
} 