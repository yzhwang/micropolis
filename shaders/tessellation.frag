#version 420 compatibility

in vec4 color;
out vec4 frag_color;

void main (void)
{
	frag_color = color;
}