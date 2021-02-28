#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>
#include <iostream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "ShaderProgram.h"
#include "InitShader.h"
#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"
#include "MeshModel.h"
#include <iostream>
#include <iomanip>


/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
glm::vec4 clear_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);
void ChangeFrameSize(int width, int height, Renderer& renderer);
std::shared_ptr<Camera> MakeCamera();
std::shared_ptr<Camera> MakeDefaultCamera();
std::shared_ptr<Light> MakePointLight();
std::shared_ptr<Light> MakeParallelLight();


void testing();
/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}
int windowWidth = 1000, windowHeight = 1000;
int main(int argc, char **argv)
{
	
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Or & Abed Project");
	if (!window)
		return 1;

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	glViewport(0,0,1000,1000);

	Scene scene = Scene();
	//setting up default camera
	scene.AddCamera(MakeDefaultCamera());
	scene.SetActiveCameraIndex(0);
	


	Renderer& renderer = Renderer(frameBufferWidth, frameBufferHeight ,scene);
	renderer.loadShaders();
	renderer.LoadTextures();
	
	
	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	 

    while (!glfwWindowShouldClose(window))
    {
		// Poll and process events
		glfwPollEvents();

		// Imgui stuff
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		DrawImguiMenus(io, scene);
		ImGui::Render();


		// Clear the screen and depth buffer
		glClearColor(scene.backgroundColor[0], scene.backgroundColor[1], scene.backgroundColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render scene
		renderer.Render(scene);

		// Imgui stuff
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap front and back buffers
		glfwSwapBuffers(window);
    }

	Cleanup(window);
	return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	

	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	
	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		// TODO: Set new aspect ratio
		ChangeFrameSize(frameBufferWidth, frameBufferHeight, renderer);
		scene.GetActiveCamera().aspectRatio = frameBufferWidth / frameBufferHeight;
		//renderer.SetViewport(frameBufferWidth, frameBufferHeight);
		
	}

	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		if (io.KeysDown[65])
		{
			// A key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
	}

	if (!io.WantCaptureMouse)
	{
		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			// Left mouse button is down
		}
	}

	renderer.Render(scene);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}


void ChangeFrameSize(int width, int height, Renderer& renderer)
{
	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, windowWidth, windowHeight);
	renderer.SetViewport(windowWidth, windowHeight);


}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

std::shared_ptr<Camera> MakeCamera() {
	
	MeshModel mesh = MeshModel(*(Utils::LoadMeshModel("../computergraphics2021-or-and-abed/Data/camera.obj")));
	glm::vec3 nEye = glm::vec3(0, 0, 0);
	glm::vec3 nAt = glm::vec3(0, 0, -1);
	glm::vec3 nUp = glm::vec3(0, 1, 0);
	return std::make_shared<Camera>(mesh, nEye, nAt, nUp);
}

std::shared_ptr<Camera> MakeDefaultCamera()
{
	MeshModel mesh = MeshModel(*(Utils::LoadMeshModel("../computergraphics2021-or-and-abed/Data/camera.obj")));
	glm::vec3 nEye = glm::vec3(0, 0, 1);
	glm::vec3 nAt = glm::vec3(0, 0, -1);
	glm::vec3 nUp = glm::vec3(0, 1, 0);
	auto cam = std::make_shared<Camera>(mesh, nEye, nAt, nUp);

	glm::fvec3 scale = glm::fvec3(1,1,1);
	glm::fvec3 Rotate = glm::fvec3(0, 0, 0);
	glm::fvec3 Translate = glm::fvec3(0, 0, 1);

	cam->setObjectTransformationUpdates(scale, Rotate, Translate);
	return cam;
}

std::shared_ptr<Light> MakePointLight()
{
	MeshModel mesh = MeshModel(*(Utils::LoadMeshModel("../computergraphics2021-or-and-abed/Data/Sphere.obj")));
	return std::make_shared<Light>(mesh , Light::lightType::Point);
}

std::shared_ptr<Light> MakeParallelLight()
{
	MeshModel mesh = MeshModel(*(Utils::LoadMeshModel("../computergraphics2021-or-and-abed/Data/arrow.obj")));
	return std::make_shared<Light>(mesh , Light::lightType::Parallel);
}


void testing()
{
	glm::fvec3 p1 = glm::fvec3(0, 0, 0);
	glm::fvec3 p2 = glm::fvec3(4, 0, 0);
	glm::fvec3 p3 = glm::fvec3(2, 2, 0);

	glm::fvec2 insidePoint = glm::fvec2(2, 1);

	glm::fvec3 w = Utils::triangleInterpolation(p1, p2, p3, insidePoint);
	std::cout <<  w[0]<< " -- " << w[0] << " -- " << w[0] <<std::endl;


}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	float  windowsWidth = (float)(io.DisplaySize.x) / 2;
	float  windowsHeight = (float)(io.DisplaySize.y) / 2;
	float minWindow = glm::min(windowsWidth, windowsHeight);
	float maxWindow = glm::max(windowsWidth, windowsHeight);

	/**
	 * MeshViewer menu
	 */
	ImGui::Begin("MeshViewer Menu");

	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene.AddModel(Utils::LoadMeshModel(outPath));
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Add"))
		{
			if (ImGui::MenuItem("Add Object", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene.AddModel(Utils::LoadMeshModel(outPath));
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			if (ImGui::MenuItem("Add Camera", "CTRL+C"))
			{
				scene.AddCamera(MakeCamera());

			}
			if (ImGui::BeginMenu("Add Light"))
			{
				if (ImGui::MenuItem("point light source", "CTRL+P"))
				{
					scene.AddLight(MakePointLight());
				}
				if (ImGui::MenuItem("parallel light source", "CTRL+L"))
				{
					scene.AddLight(MakeParallelLight());
				}
				ImGui::EndMenu();
			}
			
			
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	//// Controls
	//ImGui::ColorEdit3("Clear ", (float*)&clear_color);
	//// TODO: Add more controls as needed
	static int camera_selected = 0;
	static int model_selected = -1;
	static int light_selected = -1;

	if (ImGui::Button("Test")) {
		testing();
	}


	if (scene.GetModelCount() != 0 ||  scene.GetCameraCount() != 0 || scene.GetLightCount() != 0) {
		if (ImGui::Button("Clear Screen and selection")) {
			scene.cleanupScene();
			camera_selected = 0;
			model_selected = -1;
			light_selected = -1;
		}
	}

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;

	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Scene"))
		{
			//---------------------------------Scene --------------------------
			if (ImGui::CollapsingHeader("Scene Actions", ImGuiTreeNodeFlags_None))
			{
				if (ImGui::Button("enable environment mapping")) {
					//model1.LoadEnvironmentMap(" ");
					scene.isEnv = true;
				}
				ImGui::Checkbox("WireFram", &scene.wireFrame);
				ImGui::ColorEdit3("background color", (float*)&scene.backgroundColor);
				
				if (ImGui::Button("Reset color")) {
					
					scene.backgroundColor = glm::fvec3(0.8f, 0.8f, 0.8f);
				}
				if (ImGui::CollapsingHeader("Post Proccessing ", ImGuiTreeNodeFlags_None))
				{
					static bool  gaussuanBlurOptions = false;
					static bool  BloomOptions = false;
					static bool  FogOptions = false;
					static bool  GrayOptions = false;
					ImGui::Checkbox("Gray Scale", &GrayOptions);
					if (GrayOptions)
						scene.grayScales = true;
					else
					{
						scene.grayScales = false;
					}
					

					ImGui::Checkbox("Gaussian blurring", &gaussuanBlurOptions);
					if(gaussuanBlurOptions){
						scene.gaussianBlurring = true;
						ImGui::SliderInt("Mask Radius", &scene.maskRadius, 1, 5);
						ImGui::SliderFloat("Mask STD", &scene.gaussianSTD, 0.1f, 5.0f);
					}
					else
					{
						scene.gaussianBlurring = false;
					}

					ImGui::Checkbox("Bloom", &BloomOptions);
					if (BloomOptions) {
						scene.bloom = true;
						ImGui::SliderFloat("Threshold: ", &scene.threshold, 0.3f, 1.0f);
					}
					else
					{
						scene.bloom = false;
					}
					ImGui::Checkbox("Fog effect", &FogOptions);
					if (FogOptions)
					{
						scene.fogEffect = true;
						float color[3] = { scene.fogColor[0], scene.fogColor[1], scene.fogColor[2] };
						ImGui::ColorEdit3("Choose the fog color: ", (float*)&color);
						scene.fogColor[0] = color[0];
						scene.fogColor[1] = color[1];
						scene.fogColor[2] = color[2];
						ImGui::RadioButton("None", &scene.fogType, 0);
						ImGui::SameLine();
						ImGui::RadioButton("Linear", &scene.fogType, 1);
						ImGui::SameLine();
						ImGui::RadioButton("Exponential", &scene.fogType, 2);
						ImGui::SameLine();
						ImGui::RadioButton("Exponential Squred", &scene.fogType, 3);
						switch (scene.fogType)
						{
						case (1):
							ImGui::SliderFloat("Start Fog: ", &scene.fogStart, -10.0f, 10.0f);
							ImGui::SliderFloat("End Fog: ", &scene.fogEnd, 1.0f, 15.0f);
							break;

						case(2):
							//ImGui::SliderFloat("Distance Fog: ", &scene.fogDistance, 0.0f, 3.0f);
							ImGui::SliderFloat("Density Fog: ", &scene.fogDensity, 0.0f, 3.0f);
							break;

						case(3):
							ImGui::SliderFloat("Density Fog: ", &scene.fogDensity, 0.0f, 2.5f);
							break;
						default:
							break;
						}
					}
					
					//else
					//{
					//	scene.fogEffect = false;
					//}
				}
				ImGui::Checkbox("Create Texture", &scene.isTexture);
				if (scene.isTexture)
				{
					ImGui::SliderInt("Choose your texture factor", &scene.textureFactor, 1, 100);
				}

			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Cameras"))
		{
			//---------------------------------Camera --------------------------
			if (ImGui::CollapsingHeader("Camera Actions", ImGuiTreeNodeFlags_None))
			{
				
				/*if (scene.GetCameraCount() != 0) {
					if (ImGui::Button("Clear Cameras")) {
						camera_selected = 0;
						scene.clearCameras();
					}
				}*/
				if (ImGui::TreeNode("Active camera selection:"))
				{

					if (scene.GetCameraCount() == 0) {
						ImGui::Text("please add camera");
					}
					else {
						for (int n = 0; n < scene.GetCameraCount(); n++)
						{

							//sprintf(buf, ((scene.GetModels())[n])->GetModelName() + "model", n);

							const std::string name = " camera #" + std::to_string(n + 1);
							// copying the contents of the
							if (ImGui::Selectable(name.c_str(), camera_selected == n)) {
								camera_selected = n;
								//scene.SetActiveCameraIndex(n);
							}
					
						
						}
					}
					ImGui::TreePop();
				}

		
				if (camera_selected != -1 && scene.GetCameraCount() != 0 && camera_selected != 0) {
					if (ImGui::Button("delete")) {
						camera_selected = 0;
						scene.deleteActiveCamera();
					}
				}
				if (camera_selected != -1 && scene.GetCameraCount() != 0) {
		
					Camera& cam = scene.GetCamera(camera_selected);

					if (scene.GetActiveCameraIndex() != camera_selected) {
						if (ImGui::Button("To Camera View")) {
							scene.SetActiveCameraIndex(camera_selected);
						}
							
					}
					/*if (!scene.GetCamOrWorldView()) {
						if (ImGui::Button("To Camera View"))
							scene.SetCamOrWorldView(true);
					}
					else
					{
						if (ImGui::Button("To World View"))
							scene.SetCamOrWorldView(false);
					}*/

					static int update = 0;
					ImGui::RadioButton("Transformation", &update, 1); ImGui::SameLine();
					ImGui::RadioButton("Lookat", &update, 0);

					cam.setLookAtOrTransformation(update);
					//scene.GetActiveCamera().SetCameraLookAt();
					if (ImGui::TreeNode("Active camera params:"))
					{
				
						glm::vec3 glmEye = cam.getEye();
						glm::vec3 glmAt = cam.getAt();
						glm::vec3 glmUp = cam.getUp();


						static float vecEye[3] = { 0.10f, 0.20f, 0.30f };
						static float vecAt[3] = { 0.10f, 0.20f, 0.30f };
						static float vecUp[3] = { 0.10f, 0.20f, 0.30f };


						for (int i = 0; i < 3; i++) {
							vecEye[i] = glmEye[i];
							vecAt[i] = glmAt[i];
							vecUp[i] = glmUp[i];
						}

						static bool symmetriceye = false;
				
						ImGui::Checkbox("symmetric", &symmetriceye);
						if (symmetriceye) {
							ImGui::SliderFloat("Eye", &vecEye[0], -1 , 1);
							vecEye[1]=vecEye[0];
							vecEye[2] = vecEye[0];
						}
						else {
							ImGui::SliderFloat("Eye X", &vecEye[0], -1 , 1);
							ImGui::SliderFloat("Eye Y", &vecEye[1], -1 , 1);
							ImGui::SliderFloat("Eye Z", &vecEye[2], -1 , 1);
						}
			
				
						if (ImGui::Button("Reset eye")) {
							vecEye[0] = 0.f;
							vecEye[1] = 0.f;
							vecEye[2] = 0.f;
						}
						ImGui::SliderFloat("at X", &vecAt[0], -1 , 1);
						ImGui::SliderFloat("at Y", &vecAt[1], -1 , 1);
						ImGui::SliderFloat("at Z", &vecAt[2], -1 , 1);
						if (ImGui::Button("Reset at")) {
							vecAt[0] = 0.f;
							vecAt[1] = 0.f;
							vecAt[2] = -1.f;
						}
						ImGui::SliderFloat3("Up (x,y,z)", vecUp , -1.0, 1.0);
						if (ImGui::Button("Reset up")) {
							vecUp[0] = 0.f;
							vecUp[1] = 1.f;
							vecUp[2] = 0.f;
						}

						for (int i = 0; i < 3; i++) {
							glmEye[i] = vecEye[i];
							glmAt[i] = vecAt[i];
							glmUp[i] = vecUp[i];
						}
						cam.SetCameraLookAt(glmEye, glmAt, glmUp);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("Active camera Projection Type:"))
					{
						static int Projection = 1;
						ImGui::RadioButton("Orthographic", &Projection, 1); ImGui::SameLine();
						ImGui::RadioButton("Perspective", &Projection, 0);

						if (Projection) {
							float nRight, nLeft, nTop, nBottom, nNear, nFar;
							nRight = cam.GetRight();
							nLeft = cam.GetLeft();
							nTop = cam.GetTop();
							nBottom = cam.GetBottom();
							nNear = cam.GetNear();
							nFar = cam.GetFar();

							ImGui::SliderFloat(":Right ", &nRight , 0.0f, 1.0f);
							ImGui::SliderFloat(":Left ", &nLeft,  -1 , 0.0f);
							ImGui::SliderFloat(" :Top ", &nTop, 0.0f, 1.0f);
							ImGui::SliderFloat(" :Bottom", &nBottom, -1, 0.0f);
							ImGui::SliderFloat(" :Near: ", &nNear ,0.1f, 0.1f);
							ImGui::SliderFloat(" :Far: ", &nFar, 0.5, 2000.0f);

							cam.SetViewVolumeCoordinates(nRight, nLeft, nTop, nBottom, nNear, nFar);
					
						}
						else
						{
							float nNear, nFar, nFovy, nAspectRatio, nZoom;
							nNear = cam.GetNear();
							nFar = cam.GetFar();
							nFovy = cam.GetFovy();
							nAspectRatio = windowsWidth / windowsHeight;
							nZoom = cam.GetZoom();

							ImGui::SliderFloat(" :Near ", &nNear,0.1f, 0.1f);
							ImGui::SliderFloat(" :Far ", &nFar, 10.0f, 2500.0f);
							ImGui::SliderFloat(":Angle of Field of View Y ", &nFovy,0.001f, 3.14f);
							ImGui::SliderFloat(" :Width", &nAspectRatio, 0.1f, 100.0f);
							ImGui::SliderFloat("Zoom: ", &nZoom, 1.0f, 2.0f);
							ImGui::SliderFloat("Zmin: ", &cam.ZMinPerspective, 0.00001f, 2.0f);
							cam.SetZoom(nZoom);
							cam.SetPerspectiveData(nNear, nFar, nFovy, nAspectRatio);
						}

						cam.setProjection(Projection);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("Camera model Transformation"))
					{
						glm::vec3 Rotate = cam.getRotate();
						glm::vec3 Translate = cam.getTranslate();
						glm::fvec3 scale = cam.getScale();

						if (ImGui::CollapsingHeader("Rotating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Rotate X", &Rotate[0], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Y", &Rotate[1], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Z", &Rotate[2], -180.0f, 180.0f);
							if (ImGui::Button("Reset Rotating")) {
								Rotate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}
						if (ImGui::CollapsingHeader("Translating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Translate X", &Translate[0], -1, 1);
							ImGui::SliderFloat("Translate Y", &Translate[1], -1, 1);
							ImGui::SliderFloat("Translate Z", &Translate[2], -1, 1);
							if (ImGui::Button("Reset trasnalte")) {
								Translate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}

						cam.setObjectTransformationUpdates(scale, Rotate, Translate);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("Camera model world Transformation:"))
					{


						glm::vec3 worldRotate = cam.getWorldRotate();
						glm::vec3 worldTranslate = cam.getWorldTranslate();

						if (ImGui::CollapsingHeader("Rotating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Rotate X", &worldRotate[0], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Y", &worldRotate[1], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Z", &worldRotate[2], -180.0f, 180.0f);
							if (ImGui::Button("Reset Rotating")) {
								worldRotate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}
						if (ImGui::CollapsingHeader("Translating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Translate X", &worldTranslate[0], -1, 1);
							ImGui::SliderFloat("Translate Y", &worldTranslate[1], -1, 1);
							ImGui::SliderFloat("Translate Z", &worldTranslate[2], -1, 1);
							if (ImGui::Button("Reset Translating")) {
								worldTranslate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}
						glm::fvec3 worldScale = glm::fvec3(1.0f, 1.0f, 1.0f);
						cam.setWorldTransformationUpdates(worldScale, worldRotate, worldTranslate);
						ImGui::TreePop();
					}
					cam.updateLookAt();


				}

			}
		ImGui::EndTabItem();
		}
		//---------------------------------Model --------------------------

		if (ImGui::BeginTabItem("Models"))
		{
			if (ImGui::CollapsingHeader("Models Actions", ImGuiTreeNodeFlags_None))
			{
				
				if (scene.GetModelCount() != 0) {
					if (ImGui::Button("Clear Models")) {
						model_selected = -1;
						scene.clearModels();
					}
				}

				ImGui::Separator();
		
				if (ImGui::TreeNode("Active model selection:"))
				{


					for (int n = 0; n < scene.GetModelCount(); n++)
					{

						//sprintf(buf, ((scene.GetModels())[n])->GetModelName() + "model", n);
						const std::string name = " model #"+ std::to_string(n+1)+ ": " +scene.GetModels()[n]->GetModelName() ;
						// copying the contents of the
						if (ImGui::Selectable(name.c_str(), model_selected == n)) {
							model_selected = n;
							scene.SetActiveModelIndex(n);
						}

					}
					if (scene.GetModelCount() == 0) {
						ImGui::Text("please select one or more model");
					}
					ImGui::TreePop();
				}
				if (model_selected != -1 && scene.GetModelCount() != 0) {
					if (ImGui::Button("delete")) {
						model_selected = -1;
						scene.deleteActiveModel();
					}
				}
				if (model_selected != -1 && scene.GetModelCount() != 0) {
					MeshModel& model1 = scene.GetActiveModel();
					if (ImGui::TreeNode("model Transformation"))
					{

						glm::vec3 scale = model1.getScale();
						glm::vec3 Rotate = model1.getRotate();
						glm::vec3 Translate = model1.getTranslate();


						if (ImGui::CollapsingHeader("Scalling", ImGuiTreeNodeFlags_None))
						{
							static bool symmetric = false;
							ImGui::Checkbox("symmetric", &symmetric);
							if (symmetric) {
								ImGui::SliderFloat("Scale", &scale[0], -2.0f, 2.0f);
								scale = glm::vec3(scale[0], scale[0], scale[0]);
							}
							else {
								ImGui::SliderFloat("Scale X", &scale[0], -2.0f, 2.0f);
								ImGui::SliderFloat("Scale Y", &scale[1], -2.0f, 2.0f);
								ImGui::SliderFloat("Scale Z", &scale[2], -2.0f, 2.0f);
							}
							if (ImGui::Button("Reset scale")) {
								scale = glm::vec3(1.0f, 1.0f, 1.0f);
							}
						}

						if (ImGui::CollapsingHeader("Rotating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Rotate X", &Rotate[0], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Y", &Rotate[1], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Z", &Rotate[2], -180.0f, 180.0f);
							if (ImGui::Button("Reset Rotating")) {
								Rotate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}
						if (ImGui::CollapsingHeader("Translating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Translate X", &Translate[0], -1, 1);
							ImGui::SliderFloat("Translate Y", &Translate[1], -1, 1);
							ImGui::SliderFloat("Translate Z", &Translate[2], -1, 1);
							if (ImGui::Button("Reset trasnalte")) {
								Translate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}


						//ImGui::SliderFloat3("Rotate		[x,y,z]", Rotate, 0.0f, 359.9f);
						//ImGui::SliderFloat3("Translate	[x,y,z]", Translate, 0.0f, 1.0f);
						model1.setObjectTransformationUpdates(scale, Rotate, Translate);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("model world Transformation:"))
					{

						glm::vec3 worldScale = model1.getWorldScale();
						glm::vec3 worldRotate = model1.getWorldRotate();
						glm::vec3 worldTranslate = model1.getWorldTranslate();
						if (ImGui::CollapsingHeader("Scalling", ImGuiTreeNodeFlags_None))
						{
							static bool symmetric = false;
							ImGui::Checkbox("symmetric", &symmetric);
							if (symmetric) {
								ImGui::SliderFloat("Scale", &worldScale[0], -2.0f, 2.0f);
								worldScale = glm::vec3(worldScale[0], worldScale[0], worldScale[0]);
							}
							else {
								ImGui::SliderFloat("Scale X", &worldScale[0], -2.0f, 2.0f);
								ImGui::SliderFloat("Scale Y", &worldScale[1], -2.0f, 2.0f);
								ImGui::SliderFloat("Scale Z", &worldScale[2], -2.0f, 2.0f);
							}
							if (ImGui::Button("Reset scale")) {
								worldScale = glm::vec3(1.0f, 1.0f, 1.0f);
							}
						}

						if (ImGui::CollapsingHeader("Rotating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Rotate X", &worldRotate[0], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Y", &worldRotate[1], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Z", &worldRotate[2], -180.0f, 180.0f);
							if (ImGui::Button("Reset Rotating")) {
								worldRotate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}
						if (ImGui::CollapsingHeader("Translating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Translate X", &worldTranslate[0], -1, 1);
							ImGui::SliderFloat("Translate Y", &worldTranslate[1], -1, 1);
							ImGui::SliderFloat("Translate Z", &worldTranslate[2], -1, 1);
							if (ImGui::Button("Reset Translating")) {
								worldTranslate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}
						//ImGui::SliderFloat3("Rotate		[x,y,z]", Rotate, 0.0f, 359.9f);
						//ImGui::SliderFloat3("Translate	[x,y,z]", Translate, 0.0f, 1.0f);
						model1.setWorldTransformationUpdates(worldScale, worldRotate, worldTranslate);
						ImGui::TreePop();
					}
					if (ImGui::TreeNode("model color or texture selection:")) {
						bool isColor = ImGui::RadioButton("Color", &model1.isTexture, 0);
						ImGui::SameLine();
						bool isTex = ImGui::RadioButton("Texture", &model1.isTexture, 1);
						if (model1.isTexture == 0) {
							glm::vec3 currMeshColor = model1.GetColor();
							float Color[3] = { currMeshColor[0], currMeshColor[1],currMeshColor[2] };
							ImGui::ColorEdit3("choose color", (float*)&Color);

							for (int i = 0; i < 3; i++) {
								currMeshColor[i] = Color[i];
							}
							model1.SetColor(currMeshColor);

							ImGui::ColorEdit3("ambient color", (float*)&model1.ambientColor);
							ImGui::ColorEdit3("diffuse color", (float*)&model1.diffuseColor);
							ImGui::ColorEdit3("specular color", (float*)&model1.specularColor);
							
						}
						else if (model1.isTexture == 1) {
							if (ImGui::Button("Add Texture")) {
								nfdchar_t* outPath = NULL;
								nfdresult_t result = NFD_OpenDialog("jpg", NULL, &outPath);
								if (result == NFD_OKAY) {

									//MeshModel& model = scene.GetActiveModel();
									if (&model1 != nullptr) {
										
										model1.LoadTextures(outPath);
									}
									free(outPath);
								}
								else if (result == NFD_CANCEL) {
								}
								else {
								}

							}
							if (ImGui::Button("Planar Projection")) {
								model1.usePlanarMap();
							}
							if (ImGui::Button("Cylindrical Projection")) {
								model1.useCylindricalMap();
							}
							if (ImGui::Button("Use Spherical Projection")) {
								model1.useSphericalMap();
							}
							static bool  normalMapping = false;
							ImGui::Checkbox("enable normal mapping", &normalMapping);
							
							if (normalMapping) {
								if (ImGui::Button("Add Normal map")) {
									nfdchar_t* outPath = NULL;
									nfdresult_t result = NFD_OpenDialog("jpg", NULL, &outPath);
									if (result == NFD_OKAY) {

										//MeshModel& model = scene.GetActiveModel();
										if (&model1 != nullptr) {

											model1.LoadNormalMap(outPath);
											model1.isNormalMap = true;
										}
										free(outPath);
									}
									else if (result == NFD_CANCEL) {
									}
									else {
									}

								}
							}
							else {
								model1.isNormalMap = false;
							}
							static bool  envMapping = false;
							if (ImGui::Button("enable environment mapping")) {
								//	//model1.LoadEnvironmentMap(" ");
								scene.isEnv = true;
							}
								
							//}
							/*	nfdchar_t* outPath = NULL;
								nfdresult_t result = NFD_OpenDialog("jpg", NULL, &outPath);
								if (result == NFD_OKAY) {

									//MeshModel& model = scene.GetActiveModel();
									if (&model1 != nullptr) {

										model1.LoadEnvironmentMap(outPath);
										model1.isEnvMap = true;
									}
									free(outPath);
								}
								else if (result == NFD_CANCEL) {
								}
								else {
								}*/
							//}

								//model1.isEnvMap = true;

							/*if (envMapping) {
								model1.isEnvMap = true;
							}*/

							
						}
						static bool toon = model1.isToon;
						ImGui::Text("Toon shading:");
						//if (ImGui::Checkbox("Toon Shading Effect", &toon)) {
							ImGui::SliderInt("Number of color bits", &model1.numOfColorBits, 2, 255);
							//model1.isToon = toon;
						//}
						//model1.numOfColorBits = 256 - model1.numOfColorBits;
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("Shading options:")) {
						
						static int shadingType = -1;
						if (ImGui::Selectable("flat shading", shadingType == 0)) {
							model1.shadingType = MeshModel::shadingType::Flat;
							shadingType = 0;
						};
						if (ImGui::Selectable("gauraud shading", shadingType == 1)) {
							model1.shadingType = MeshModel::shadingType::Gauraud;
							shadingType = 1;
						};
						if (ImGui::Selectable("phong shading", shadingType == 2)) {
							model1.shadingType = MeshModel::shadingType::Phong;
							shadingType = 2;
						};
						if (ImGui::Selectable("none", shadingType == 3)) {
							model1.shadingType = MeshModel::shadingType::None;
							shadingType = 3;
						};
						if (ImGui::Checkbox("Render Frame", &scene.renderFrame)) {
							scene.renderStatus = 1;
						}
						else {
							scene.renderStatus = 0;
						}

						ImGui::TreePop();
					}

					float MaxNormalLenthg = glm::min(windowsHeight, windowsWidth)/2;

					ImGui::Checkbox("Display Bounding Box", &model1.displayBoundingBox);
					
					if (ImGui::CollapsingHeader("Face Normals", ImGuiTreeNodeFlags_None))
					{
						ImGui::Checkbox("Display Face Normals", &model1.displayFaceNormals);
						ImGui::SliderFloat("Face Normals Length", &model1.FaceNormalsLength, 0, MaxNormalLenthg);
					}

					if (ImGui::CollapsingHeader("vertices Normals", ImGuiTreeNodeFlags_None))
					{
						ImGui::Checkbox("Display vertices Normals", &model1.displayVerticesNormals);
						ImGui::SliderFloat("vertices Normals Length", &model1.VerticesNormalsLength, 0, MaxNormalLenthg);
					}

					if (ImGui::CollapsingHeader("vertices Normals Per Face", ImGuiTreeNodeFlags_None))
					{
						ImGui::Checkbox("Display vertices Normals Per Face", &model1.displayVerticesNormalsPerFace);
						ImGui::SliderFloat("vertices Normals Per Face Length", &model1.VerticesNormalsPerFaceLength, 0, MaxNormalLenthg);
					}
				}
			}
		ImGui::EndTabItem();
		}
		//---------------------------------Light --------------------------

		if (ImGui::BeginTabItem("Lights"))
		{
			if (ImGui::CollapsingHeader("Light Actions", ImGuiTreeNodeFlags_None))
			{
				
				if (scene.GetLightCount() != 0) {
					if (ImGui::Button("Clear Lights")) {
						light_selected = -1;
						scene.ClearLights();
					}
				}

				ImGui::Separator();

				if (ImGui::TreeNode("Active lights selection:"))
				{


					for (int n = 0; n < scene.GetLightCount(); n++)
					{

						//sprintf(buf, ((scene.GetModels())[n])->GetModelName() + "model", n);
						const std::string name = " light #" + std::to_string(n + 1) ;
						// copying the contents of the
						if (ImGui::Selectable(name.c_str(), light_selected == n)) {
							light_selected = n;
							scene.SetActiveLightIndex(n);
						}

					}
					if (scene.GetLightCount() == 0) {
						ImGui::Text("please select one or more lights");
					}
					ImGui::TreePop();
				}
				if (light_selected != -1 && scene.GetLightCount() != 0) {

					ImGui::Checkbox("Power ", &scene.GetActiveLight().power);
					ImGui::SameLine();
					if (scene.GetActiveLight().power) {
						ImGui::Text(" ON");
					}
					else {
						ImGui::Text(" OFF");
					}

					if (ImGui::Button("delete")) {
						light_selected = -1;
						scene.deleteActiveLight();
					}
				}
				if (light_selected != -1 && scene.GetLightCount() != 0) {
					MeshModel& model1 = scene.GetActiveLight();
					if (ImGui::TreeNode("model Transformation"))
					{

						glm::vec3 Rotate = model1.getRotate();
						glm::vec3 Translate = model1.getTranslate();
						glm::vec3 scale = model1.getScale();

						if (ImGui::CollapsingHeader("Translating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Translate X", &Translate[0], -1, 1);
							ImGui::SliderFloat("Translate Y", &Translate[1], -1, 1);
							ImGui::SliderFloat("Translate Z", &Translate[2], -1, 1);
							if (ImGui::Button("Reset trasnalte")) {
								Translate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}

						if (ImGui::CollapsingHeader("Rotating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Rotate X", &Rotate[0], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Y", &Rotate[1], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Z", &Rotate[2], -180.0f, 180.0f);
							if (ImGui::Button("Reset Rotating")) {
								Rotate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}

						
						model1.setObjectTransformationUpdates(scale, Rotate, Translate);
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("model world Transformation:"))
					{

						glm::vec3 worldScale = model1.getWorldScale();
						glm::vec3 worldRotate = model1.getWorldRotate();
						glm::vec3 worldTranslate = model1.getWorldTranslate();

						if (ImGui::CollapsingHeader("Translating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Translate X", &worldTranslate[0], -1, 1);
							ImGui::SliderFloat("Translate Y", &worldTranslate[1], -1, 1);
							ImGui::SliderFloat("Translate Z", &worldTranslate[2], -1 , 1);
							if (ImGui::Button("Reset trasnalte")) {
								worldTranslate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}

						if (ImGui::CollapsingHeader("Rotating", ImGuiTreeNodeFlags_None))
						{
							ImGui::SliderFloat("Rotate X", &worldRotate[0], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Y", &worldRotate[1], -180.0f, 180.0f);
							ImGui::SliderFloat("Rotate Z", &worldRotate[2], -180.0f, 180.0f);
							if (ImGui::Button("Reset Rotating")) {
								worldRotate = glm::vec3(0.0f, 0.0f, 0.0f);
							}
						}

						model1.setWorldTransformationUpdates(worldScale, worldRotate, worldTranslate);
						ImGui::TreePop();
					}
					if (ImGui::TreeNode("model color selection:")) {

						ImGui::ColorEdit3("ambient color", (float*)&model1.ambientColor);
						ImGui::ColorEdit3("diffuse color", (float*)&model1.diffuseColor);
						ImGui::ColorEdit3("specular color", (float*)&model1.specularColor);
						
						ImGui::TreePop();
					}

				}
				if (light_selected != -1 && scene.GetLightCount() != 0 ) {
					Light& Light = scene.GetActiveLight();
					ImGui::SliderFloat("alpha", &Light.alpha, 0.1, 5.0f);
				}

			}
		ImGui::EndTabItem();
		}
	ImGui::EndTabBar();
	}
	ImGui::End();


	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */
	
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
}