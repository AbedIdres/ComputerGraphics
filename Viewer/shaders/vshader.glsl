#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 model;	//inverse(modelWorldTransformation)*modelTransformation
uniform mat4 view;	// viewVolumeTransformation
uniform mat4 projection;	// AfterProjectTransforamtion * projectionTransformation

uniform mat4 scale;
uniform mat4 modelTransformation;
uniform mat4 inverserCameraTransformation;
uniform mat4 viewVolumeTransformation;

uniform mat4 finalTransformation;
uniform mat4 normalTransformation;




// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec4 fragPos;
out vec4 fragNormal;
out vec2 fragTexCoords;

void main()
{
	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader

	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec4(inverserCameraTransformation* modelTransformation * scale * vec4(pos, 1.0f));

	//normal transformation

	/*vec3 newNormal; 
	if(mapNormal){
		//newNormal = normalize(vec3(texture(nomralMap, fragTexCoords).rgb)*2 -1);
		newNormal = normalize(vec3(texture(nomralMap, fragTexCoords)));
		/*vec2 tmp = fragNormal.xy;
		newNormal = normalize(vec3(texture(nomralMap, tmp).rgb));*/

	/*}else{
		newNormal = normal;
	}*/

	vec3 temp = vec3(inverserCameraTransformation* modelTransformation * scale * vec4(normal,1.0f));
	vec3 pos_zero= vec3(inverserCameraTransformation* modelTransformation * scale  * vec4(0.0f, 0.0f, 0.0f, 1.0f));
	fragNormal = vec4(temp -  pos_zero, 1.0f);

	// Pass the vertex texture coordinates property as it is. Its interpolated value
	// will be avilable for us in the fragment shader
	fragTexCoords = texCoords;

	// This is an internal OpenGL variable, we must set a value to this variable
	gl_Position = vec4(viewVolumeTransformation*inverserCameraTransformation* modelTransformation * scale * vec4(pos, 1.0f));
//	gl_Position = gl_Position /gl_Position.w;
}