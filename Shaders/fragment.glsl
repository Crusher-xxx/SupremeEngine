#version 460 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float k;

void main()
{
    FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x, TexCoord.y)), k);
}