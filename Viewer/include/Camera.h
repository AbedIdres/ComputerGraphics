#pragma once
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include "Utils.h"
#include "MeshModel.h"
class Camera : public MeshModel
{
public:
	Camera(MeshModel& mesh, glm::vec3& eye_, glm::vec3& at_, glm::vec3& up_);
	virtual ~Camera();

	void SetCameraLookAt(const glm::vec3& eye_, const glm::vec3& at_, const glm::vec3& up_);
	void SetViewVolumeCoordinates(const float right_, const float left_, const float top_, const float bottom_, const float near_, const float far_);
	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4& GetViewTransformation() const;

	void SetPerspectiveData(const float near_, const float far_, const float _fovy, const float _aspectRatio);
	void setProjection(const int Projection);
	void SetZoom(const float _zoom);
	bool GetProjection() const;

	void updateLookAt();

	glm::vec3 getEye()const;
	glm::vec3 getAt()const;
	glm::vec3 getUp()const;

	float GetRight() const;
	float GetLeft() const;
	float GetTop() const;
	float GetBottom() const;
	float GetNear() const;
	float GetFar() const;
	float GetFovy() const;
	float GetAspectRatio() const;

	float GetZoom() const;

	bool GetOrthographicOrPerspective() const;

	void setCameraDirection();
	void setLookAtOrTransformation(const bool flag);
	bool GetLookAtOrTransformation() const;

	float ZMinPerspective = 0.f;
	float right;
	float left;
	float top;
	float bottom;



	float _near;
	float _far;
	float fovy;
	float aspectRatio;
	float Pnear;
	float Pfar;
private:
	glm::mat4x4 view_transformation_;
	glm::mat4x4 view_transformation_inverse;
	glm::mat4x4 projection_transformation_;
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;


	

	float zoom;

	bool lookAtOrTransformation;	// true = transformation. false = lookAt
	bool OrthographicOrPerspective; // true = Orthographic. false = perspective
	
};
