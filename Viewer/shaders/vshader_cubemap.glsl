#version 330 core

layout(location = 0) in vec3 pos;





uniform mat4 inverserCameraTransformation;
uniform mat4 viewVolumeTransformation;





// These outputs will be available in the fragment shader as inputs
out vec3 fragTexCoords;

void main()
{


	// This is an internal OpenGL variable, we must set a value to this variable
	vec4 temp1 = vec4(viewVolumeTransformation*inverserCameraTransformation* vec4(pos, 1.0f));
	gl_Position = temp1.xyww;
	fragTexCoords = pos;
}