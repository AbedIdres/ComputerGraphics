#pragma once

#include <vector>
#include <memory>

#include "Camera.h"
#include "MeshModel.h"
#include "Light.h"

class Scene {
public:
	Scene();

	void AddModel(const std::shared_ptr<MeshModel>& mesh_model);
	int GetModelCount() const;
	MeshModel& GetModel(int index) const;
	MeshModel& GetActiveModel() const;
	std::vector<std::shared_ptr<MeshModel>> GetModels()const;
	
	void AddCamera(const std::shared_ptr<Camera>& camera);
	int GetCameraCount() const;
	Camera& GetCamera(int index) const;
	Camera& GetActiveCamera() const;

	void AddLight(const std::shared_ptr<Light>& light);
	int GetLightCount() const;
	Light& GetLight(int index) const;
	Light& GetActiveLight() const;

	void SetActiveCameraIndex(int index);
	int GetActiveCameraIndex() const;
	bool isEnv = false;
	void SetActiveModelIndex(int index);
	int GetActiveModelIndex() const;

	void SetActiveLightIndex(int index);
	int GetActiveLightIndex() const;

	void SetCamOrWorldView(const bool view);
	bool GetCamOrWorldView() const;
	
	bool isTexture = false;
	int textureFactor = 8;

	void cleanupScene();

	bool getShowAxis() const ;

	void setShowAxis(bool show);

	void deleteActiveCamera();
	void deleteActiveModel();
	void deleteActiveLight();
	
	void clearCameras();
	void clearModels();
	void ClearLights();

	glm::fvec3 backgroundColor = glm::fvec3(0.8f, 0.8f, 0.8f);
	bool grayScales = false;

	bool gaussianBlurring = false;
	float gaussianSTD = 1;
	int maskRadius = 1;

	bool bloom = false;
	float threshold = 1;

	bool fogEffect = false;
	glm::vec3 fogColor = glm::vec3(0.4, 0.4, 0.4);
	int fogType = 0; // 0 - none, 1 - linear, 2 - Exponential, 3 - Exponential Squared
	float fogDensity = 1.0f;
	float fogStart = 0 ;
	float fogEnd = 10.0f ; // check what value should be initialized with
	float fogDistance = 0;

	bool renderFrame = false;
	int renderStatus = 0; // 0 - frame not rendered , 1 - rendering frame, 2-finished rendering 

	std::vector<std::shared_ptr<MeshModel>> mesh_models_;
	std::vector<std::shared_ptr<Camera>> cameras_;
	std::vector<std::shared_ptr<Light>> Lights_;

	int active_camera_index_;
	int active_model_index_;
	int active_light_index_;

	bool CamOrWorldView ; //true for camera view, false for World
	bool wireFrame = false; //true for showing wirefram false otherwise
};