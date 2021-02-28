#include "Transform.h"

glm::fmat4x4  Transform::TansformationScale(const glm::fvec3 position)
{
	float x = position[0];
	float y = position[1];
	float z = position[2];

	glm::fvec4 vec1 = glm::fvec4(x, 0, 0, 0);
	glm::fvec4 vec2 = glm::fvec4(0, y, 0, 0);
	glm::fvec4 vec3 = glm::fvec4(0, 0, z, 0);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	return  glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));

}

glm::fmat4x4 Transform::TansformationTransition(const glm::fvec3 position)
{
	float x = position[0];
	float y = position[1];
	float z = position[2];

	glm::fvec4 vec1 = glm::fvec4(1.0f, 0, 0, x);
	glm::fvec4 vec2 = glm::fvec4(0, 1.0f, 0, y);
	glm::fvec4 vec3 = glm::fvec4(0, 0, 1.0f, z);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	return  glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));
}

glm::fmat4x4 Transform::TansformationRotateX(const float angle)
{

	glm::fvec4 vec1 = glm::fvec4(1.0f, 0, 0, 0);
	glm::fvec4 vec2 = glm::fvec4(0, cos(angle), -sin(angle), 0);
	glm::fvec4 vec3 = glm::fvec4(0, sin(angle), cos(angle), 0);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	return glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));
}

glm::fmat4x4 Transform::TansformationRotateY(const float angle)
{

	glm::fvec4 vec1 = glm::fvec4(cos(angle), 0, sin(angle), 0);
	glm::fvec4 vec2 = glm::fvec4(0, 1, 0, 0);
	glm::fvec4 vec3 = glm::fvec4(-sin(angle), 0, cos(angle), 0);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	return glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));
}

glm::fmat4x4 Transform::TansformationRotateZ(const float angle)
{
	glm::fvec4 vec1 = glm::fvec4(cos(angle), -sin(angle), 0, 0);
	glm::fvec4 vec2 = glm::fvec4(sin(angle), cos(angle), 0, 0);
	glm::fvec4 vec3 = glm::fvec4(0, 0, 1.0f, 0);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	return glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));
}

glm::fmat4x4 Transform::TansformationShear(const glm::fvec2 vector)
{
	float shearx = vector[0];
	float sheary = vector[1];

	glm::fvec4 vec1 = glm::fvec4(1.0f, 0, shearx, 0);
	glm::fvec4 vec2 = glm::fvec4(0, 1.0f, sheary, 0);
	glm::fvec4 vec3 = glm::fvec4(0, 0, 1.0f, 0);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	return glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));
}

glm::fmat4x4 Transform::getIdMat()
{
	glm::fvec4 vec1 = glm::fvec4(1.0f, 0, 0, 0);
	glm::fvec4 vec2 = glm::fvec4(0, 1.0f, 0, 0);
	glm::fvec4 vec3 = glm::fvec4(0, 0, 1.0f, 0);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	return glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));
}

glm::fvec3 Transform::Homogeneous2Euclidean(const glm::fvec4 vec)
{
	float x = vec[0];
	float y = vec[1];
	float z = vec[2];
	float w = vec[3];
	return glm::fvec3(x / w, y / w, z / w);
}

glm::fvec4 Transform::Euclidean2Homogeneous(const glm::fvec3 vec)
{
	float x = vec[0];
	float y = vec[1];
	float z = vec[2];

	return glm::fvec4(x, y, z, 1);
}

void Transform::resetMatrix(glm::fmat4x4& mat)
{
	glm::fvec4 vec1 = glm::fvec4(1.0f, 0, 0, 0);
	glm::fvec4 vec2 = glm::fvec4(0, 1.0f, 0, 0);
	glm::fvec4 vec3 = glm::fvec4(0, 0, 1.0f, 0);
	glm::fvec4 vec4 = glm::fvec4(0, 0, 0, 1.0f);

	mat = glm::transpose(glm::fmat4x4(vec1, vec2, vec3, vec4));

}
