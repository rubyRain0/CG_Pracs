#version 400 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// Текстурный сэмплер
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
	vec4 t1 = texture(texture1, TexCoord);
	vec4 t2 = texture(texture2, TexCoord);
	FragColor = abs(t1/t2 - t2/t1);
	//FragColor = mix(t1,t2, 0.5);
	//FragColor = abs(t1 - t2);
 
}