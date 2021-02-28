#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include "Face.h"
#include <map>
#include "Texture2D.h"

#define X_FIRST  0
#define Y_FIRST  1
#define Z_FIRST  2

#define AMBIENT  0
#define DIFFUSE  1
#define SPECURAL  2

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};


class MeshModel
{
public:
	static enum shadingType { Flat, Gauraud, Phong, None };
	static enum modelType { Object, Camera, Light};

	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords , const std::string& model_name);
	MeshModel::MeshModel(const MeshModel& ref);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	std::vector<glm::vec3> getVertices()const;
	std::vector<glm::vec2> getTextureCoordinates()const;
	std::vector<glm::vec3> getNormals()const;
	int GetFacesCount() const;
	int GetVerticesCount() const;
	const std::string& GetModelName() const;
	const glm::vec3& GetVertexAtIndex(int i) const;

	int isTexture = 0; // 0 - no texture, 1 - is texture.
	Texture2D texture;
	bool  isNormalMap = false;
	Texture2D nomralMap;
	void usePlanarMap();
	void useCylindricalMap();
	void useSphericalMap();
	void LoadTextures(const char* path);
	void LoadNormalMap(const char* path);

	bool isToon;
	int numOfColorBits = 255;


	float k1;
	float k2;
	float k3;
	int k4;
	
	void setFaceNormal(int index, const glm::fvec3 normal);
	std::vector<Face> getFaces() const;
	void outputFacesAndVertices();
	std::vector<glm::vec3> getFacesNormals();
	std::vector<glm::vec3> getFacesCenters();
	std::vector<glm::vec3> getVerticesNormals();
	std::vector<glm::vec3> getVerticesNormalsPerFace() const;

	glm::vec3 getScale();
	glm::vec3 getRotate();
	glm::vec3 getTranslate();
	glm::fmat4x4 getObjectTransformation() const;

	glm::vec3 getWorldScale();
	glm::vec3 getWorldRotate();
	glm::vec3 getWorldTranslate();
	glm::fmat4x4 getWorldTransformation() const;

	glm::fmat4x4 getTransformation() const;

	float getMaxDitancePoints();

	void setModelInMiddle();
	void setMinMaxVertices();
	void setVerteciesNormals();

	void setObjectTransformationUpdates(const glm::vec3 nScale, const glm::vec3 nRotate, const glm::vec3 nTrasnlate);
	void setWorldTransformationUpdates(const glm::vec3 nScale, const glm::vec3 nRotate, const glm::vec3 nTrasnlate);
	void setObjectTransformation(const glm::fmat4x4 transform);
	void setWorldTransformation(const glm::fmat4x4 transform);

	void setFrame(glm::fvec3 center, glm::fmat3x3 CoordinateSystem);
	void updateFrame( glm::fmat4x4 transform);
	void SetColor(const glm::vec3 _color);
	glm::vec3 GetColor()const;
	const glm::fvec3& getCenter() const;
	const glm::fmat3x3& getCoordinateSystem();
	glm::fmat4x4 getNormalTransformation() const;


	GLuint getVBO() const;
	GLuint getVAO() const;
	std::vector<Vertex> getVertexes() const;


	bool displayBoundingBox = false;

	

	bool displayFaceNormals = false;
	float FaceNormalsLength = 100.0f;

	bool displayVerticesNormals = false;
	float VerticesNormalsLength = 100.0f;

	bool displayVerticesNormalsPerFace = false;
	float VerticesNormalsPerFaceLength = 100.0f;

	float minX_ = FLT_MAX;
	float minY_ = FLT_MAX;
	float minZ_ = FLT_MAX;
	float maxX_ = FLT_MIN;
	float maxY_ = FLT_MIN;
	float maxZ_ = FLT_MIN;

	std::map<int, std::vector<int>> vertcisAdjacent;

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	shadingType shadingType = Flat;
	modelType   modelType = Object;
	glm::fmat4x4 finalTransformation;
	glm::fmat4x4 normalTransformation;

	
protected:
	GLuint vbo;
	GLuint vao;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Rotate = glm::vec3(0, 0, 0);
	glm::vec3 Translate = glm::vec3(0, 0, 0);

	glm::vec3 WorldScale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 WorldRotate = glm::vec3(0, 0, 0);
	glm::vec3 WorldTranslate = glm::vec3(0, 0, 0);


	glm::fmat4x4 ObjectTransformation;
	glm::fmat4x4 WorldTransformation;

	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<glm::vec2> textureCoords_;
	std::string model_name_;


	std::vector<glm::vec3> verticesNormals_;
	std::vector<glm::vec3> facesNormals_;
	std::vector<glm::vec3> facesCenters_;
	
	glm::vec3 color;
	
	std::vector<Vertex> modelVertices;

	glm::vec3 center;
	glm::fmat3x3 CoordinateSystem;
};
