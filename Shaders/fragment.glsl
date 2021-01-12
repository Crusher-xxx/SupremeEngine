#version 460 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D crate_texture;
uniform sampler2D face_texture;
uniform float mixing_coeff;

void main()
{
    FragColor = mix(texture(crate_texture, TexCoord), texture(face_texture, vec2(TexCoord.x, TexCoord.y)), mixing_coeff);
}