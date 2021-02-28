#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight , Scene& scene_);
	virtual ~Renderer();
	void Render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	void SetViewport(const int width, const int height);
	float** GetGaussianMask(int radius, float STD);
	void applyConvolution(glm::vec3** im, float** mask, int radius);
	void applyLinearFogging();
	void applyExponentialFogging();
	void applyExponentialSquaredFogging();
	void loadShaders();
	Scene& scene;
	void LoadTextures();

	
private:
	void PutPixel(const int i, const int j, const float z, const glm::vec3& color);
	void UpdatePutPixel();
	void DrawLine(const glm::fvec3& p1, const glm::fvec3& p2, const glm::vec3& color);
	void plotLineLow(int x0, int y0, int  x1, int y1, const glm::vec3& color, glm::vec3 p1, glm::vec3 p2);
	void plotLineHigh(int x0, int y0, int x1, int y1, const glm::vec3& color, glm::vec3 p1, glm::vec3 p2);
	void DrawTriangle(const glm::fvec3& v1, const glm::fvec3& v2, const glm::fvec3& v3, const glm::vec3& color, const MeshModel& mesh, const Scene& scene, const Face& face);
	void allocateZBuffer();
	void allocateColorBuffer();
	void PostProcessing();
	void DrawBoundingBox(MeshModel& model , const Scene& scene , glm::fmat4x4 trasformation , const glm::vec3& color);
	glm::vec3 DrawFaceNormal(MeshModel& mesh, Face& face , glm::fmat4x4 trasformation, glm::fmat4x4 FinalTrasformation, const glm::vec3& color);
	void DrawVerticesNormal(MeshModel& mesh, glm::fmat4x4 trasformation, const glm::vec3& color, float normalLength);
	void DrawVerticesNormalPerFace(MeshModel& mesh, glm::fmat4x4 trasformation, const glm::vec3& color, float normalLength);
	void CreateBuffers(int w, int h);
	void CreateOpenGLBuffer();
	void InitOpenGLRendering();

	void ScanConversionTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 color);
	float getMin(float x, float y, float z);
	float getMax(float x, float y, float z);
	bool isInsideTheTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int x, int y);
	glm::vec3 getDirectionVector(glm::vec3 v1, glm::vec3 v2);
	float ZpointComputation(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 insidePoint);
	float area(int x1, int y1, int x2, int y2, int x3, int y3);

	void ScanConversionTriangleFlatShading(const glm::fvec3& v1, const glm::fvec3& v2, const glm::fvec3& v3, const  MeshModel& mesh ,  const Scene& scene , const Face& face);
	void ScanConversionTriangleGouraudShading(const glm::fvec3& v1, const glm::fvec3& v2, const glm::fvec3& v3, const  MeshModel& mesh, const Scene& scene , const Face& face);
	void ScanConversionTrianglePhongShading(const glm::fvec3& v1, const glm::fvec3& v2, const glm::fvec3& v3, const  MeshModel& mesh, const Scene& scene , const Face& face);
	glm::fmat4x4 afterProjectionMatrix;
	

	float* color_buffer_;
	int viewport_width_;
	int viewport_height_;
	float** Zbuffer;
	glm::vec3** localColorBuffer;
	GLuint gl_screen_tex_;
	GLuint gl_screen_vtc_;


	ShaderProgram colorShader;
	ShaderProgram skyboxShader;
	ShaderProgram cubeMapShader;
	Texture2D textureSky;
	GLuint cubeTex;
	GLuint cubeVAO, cubeVBO;
	GLuint skyboxVAO, skyboxVBO;
};
