#pragma once
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include "Utils.h"
#include "MeshModel.h"

class Light : public MeshModel
{
public:
	static enum lightType { Parallel, Point};
	Light::Light(MeshModel& mesh , lightType typeLights);
	virtual ~Light();
	glm::fvec3 calculateAmbient(glm::fvec3 MeshModelAmbientColor, glm::fvec3 LightAmbientColor );
	glm::fvec3 calculateDiffuse(glm::fvec3 MeshModelDiffuseColor, glm::fvec3 LightDiffuseColor, glm::fvec3 Normal, glm::fvec3 lightDirection);
	glm::fvec3 calculateSpecular(glm::fvec3 MeshModelSpecularColor, glm::fvec3 LightSpecularColor, glm::fvec3 Normal, glm::fvec3 MeshPoint ,glm::fvec3 lightcenter, glm::fvec3 cameraCenter , float Alpha);
	glm::fvec3 calculateColor(const MeshModel& mesh, const glm::fvec3 Normal, const glm::fvec3 MeshPoint, const glm::fvec3 modelcenter, const  glm::fvec3 lightcenter, const glm::fvec3 cameraCenter, const float Alpha);
	glm::fvec3 calculateSpecularParallel(glm::fvec3 MeshModelSpecularColor, glm::fvec3 LightSpecularColor, glm::fvec3 Normal, glm::fvec3 MeshPoint, glm::fvec3 lightDirection, glm::fvec3 cameraCenter, float Alpha);
	bool getTypeOfLight() const;
	lightType typeOfLight;
	float alpha = 1;
	bool power = true;
	glm::fvec3 direction = glm::fvec3(0.0f,1.0f,0.0f);
private:

};
