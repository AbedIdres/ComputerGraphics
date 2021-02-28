#version 330 core

//uniform sampler2D texture;
out vec4 frag_color;
in vec3 fragTexCoords;
uniform samplerCube skybox;
void main()
{
	
	frag_color = texture(skybox, fragTexCoords);
}



