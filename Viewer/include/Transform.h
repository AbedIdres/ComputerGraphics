#pragma once
#include <glm/glm.hpp>
class Transform
{
public:
	static glm::fmat4x4 TansformationScale(const glm::fvec3 position);
	static glm::fmat4x4 TansformationTransition(const glm::fvec3 position);
	static glm::fmat4x4 TansformationRotateX(const float angle);
	static glm::fmat4x4 TansformationRotateY(const float angle);
	static glm::fmat4x4 TansformationRotateZ(const float angle);
	static glm::fmat4x4 TansformationShear(const glm::fvec2 vector);
	static glm::fmat4x4 getIdMat();
	static void resetMatrix(glm::fmat4x4& mat);

	static glm::fvec3 Homogeneous2Euclidean(const glm::fvec4 vec);
	static glm::fvec4 Euclidean2Homogeneous(const glm::fvec3 vec);
};

