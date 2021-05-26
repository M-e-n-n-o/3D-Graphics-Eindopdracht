#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <ostream>

#include "stb_image.h"

#include "models/Model.h"
#include "renderEngine/Loader.h"
#include "renderEngine/ObjLoader.h"
#include "renderEngine/Renderer.h"
#include "shaders/StaticShader.h"
#include "toolbox/Toolbox.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

static double updateDelta();

static GLFWwindow* window;


int main(void)
{
	#pragma region OPENGL_SETTINGS
    if (!glfwInit())
        throw "Could not inditialize glwf";
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGT, "Eindopdracht - Menno Bil", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glGetError();
	#pragma endregion

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
	    if (key == GLFW_KEY_ESCAPE)
	        glfwSetWindowShouldClose(window, true);
    });
	
	
    models::RawModel rawModel = renderEngine::LoadObjModel("res/Tree.obj");
    models::ModelTexture texture = { renderEngine::loader::LoadTexture("res/TreeTexture.png") };
    texture.shineDamper = 10;
    texture.reflectivity = 1;
    models::TexturedModel model = { rawModel, texture };
    entities::Entity entity(model, glm::vec3(0, -25, -50), glm::vec3(0, 0, 0), 1);
    entities::Light light(glm::vec3(0, 0, -30), glm::vec3(1, 1, 1));
	
    shaders::StaticShader shader;
    shader.init();
    renderEngine::renderer::Init(shader);

    entities::Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	
	// Main game loop
	while (!glfwWindowShouldClose(window))
	{
        // Update
        const double delta = updateDelta();
        entity.increaseRotation(glm::vec3(0, 1, 0));
        camera.move(window);

		// Render
        renderEngine::renderer::Prepare();
        shader.start();
        shader.loadSkyColor(renderEngine::renderer::SKY_COLOR);
        shader.loadLight(light);
        shader.loadViewMatrix(camera);
		
        renderEngine::renderer::Render(entity, shader);

		// Finish up
        shader.stop();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up
    shader.cleanUp();
    renderEngine::loader::CleanUp();
	glfwTerminate();
    return 0;
}

static double updateDelta()
{
    double currentTime = glfwGetTime();
    static double lastFrameTime = currentTime;
    double deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    return deltaTime;
}