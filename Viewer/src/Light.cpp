#include "Light.h"

Light::Light(MeshModel& mesh, lightType typeLights):MeshModel(mesh)
{
	modelType = MeshModel::modelType::Light;
	typeOfLight = typeLights;
}

Light::~Light()
{
	
}

glm::fvec3 Light::calculateAmbient(glm::fvec3 MeshModelAmbientColor, glm::fvec3 LightAmbientColor)
{
	glm::fvec3 Ia = Utils::twoVectorsComponentMulti(MeshModelAmbientColor, LightAmbientColor);
	return Ia;
}

glm::fvec3 Light::calculateDiffuse(glm::fvec3 MeshModelDiffuseColor, glm::fvec3 LightDiffuseColor, glm::fvec3 Normal , glm::fvec3 lightDirection)
{
	Normal = glm::normalize(Normal);
	lightDirection = glm::normalize(lightDirection);

	glm::fvec3 Id = Utils::twoVectorsComponentMulti(MeshModelDiffuseColor, LightDiffuseColor);

	Id = Id * glm::dot(lightDirection, Normal);

	return Id;
}

glm::fvec3 Light::calculateSpecular(glm::fvec3 MeshModelSpecularColor, glm::fvec3 LightSpecularColor, glm::fvec3 Normal, glm::fvec3 MeshPoint, glm::fvec3 lightcenter, glm::fvec3 cameraCenter, float Alpha)
{
	glm::fvec3 Is = Utils::twoVectorsComponentMulti(MeshModelSpecularColor, LightSpecularColor);

	glm::fvec3 lightDirection = glm::normalize(MeshPoint -lightcenter );
	glm::fvec3 CameraDirection = glm::normalize(cameraCenter - MeshPoint);
	glm::fvec3 faceNoraml = glm::normalize(Normal);

	//R = 2*n*dot_product(n,L) - L   // When L goes from the vertex to the light source

	//glm::fvec3 reflection = glm::normalize(-2.0f * glm::dot(lightDirection, Normal)*Normal  + lightDirection);
	glm::vec3 reflection = glm::reflect(lightDirection, Normal);
	
	float degree = glm::clamp(glm::dot(reflection, CameraDirection), 0.0f, 360.0f);
	float power = glm::clamp(pow(degree, Alpha),0.0f, 1.0f);
	Is = Is * power;

	return Is;
}

glm::fvec3 Light::calculateColor(const MeshModel& mesh, const glm::fvec3 Normal, const glm::fvec3 MeshPoint, const glm::fvec3 modelcenter, const  glm::fvec3 lightcenter, const glm::fvec3 cameraCenter, const float Alpha )
{
	glm::fvec3 AmbientLight = calculateAmbient(mesh.ambientColor, ambientColor);
	glm::fvec3 DiffuseLight;
	glm::fvec3 SpecularLight;

	if (typeOfLight == lightType::Parallel) {

		glm::fvec3 lightDirection = -1.0f* Utils::applyTransformationToNormal(direction, normalTransformation);

		DiffuseLight = calculateDiffuse(mesh.diffuseColor, diffuseColor, Normal, lightDirection);

		SpecularLight = calculateSpecularParallel(mesh.specularColor, specularColor, Normal, MeshPoint, lightDirection, cameraCenter, Alpha);

	}
	else if((typeOfLight == lightType::Point)) {

		glm::fvec3 lightDirection = glm::normalize( lightcenter -  MeshPoint);

		DiffuseLight = calculateDiffuse(mesh.diffuseColor, diffuseColor, Normal, lightDirection);
		SpecularLight = calculateSpecular(mesh.specularColor, specularColor, Normal, MeshPoint, lightcenter, cameraCenter, Alpha);
	}

	

	glm::fvec3 light = AmbientLight + DiffuseLight + SpecularLight;

	return light;
}

glm::fvec3 Light::calculateSpecularParallel(glm::fvec3 MeshModelSpecularColor, glm::fvec3 LightSpecularColor, glm::fvec3 Normal, glm::fvec3 MeshPoint, glm::fvec3 lightDirection, glm::fvec3 cameraCenter, float Alpha)
{
	glm::fvec3 Is = Utils::twoVectorsComponentMulti(MeshModelSpecularColor, LightSpecularColor);
	glm::fvec3 CameraDirection = glm::normalize(cameraCenter-MeshPoint );
	glm::fvec3 faceNoraml = glm::normalize(Normal);

	//R = 2*n*dot_product(n,L) - L   // When L goes from the vertex to the light source

	//glm::fvec3 reflection = glm::normalize(2.0f * glm::dot(lightDirection, Normal) * Normal - lightDirection);
	glm::vec3 reflection = -(glm::reflect(lightDirection, Normal));

	//float degree = glm::dot(reflection, CameraDirection);
	float degree = glm::clamp(glm::dot(reflection, CameraDirection), 0.0f, 360.0f);
	float power = pow(degree, Alpha);
	Is = Is * power;

	return Is;
}

bool Light::getTypeOfLight() const
{
	if (typeOfLight == Point)
	{
		return true;
	}
	return false;
}



