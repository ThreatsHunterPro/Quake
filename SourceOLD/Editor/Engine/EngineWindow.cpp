#include "EngineWindow.h"

EngineWindow::EngineWindow()
{
	title = "Quake";
	size = vec2(1920, 1080);
	bgColor = vec4(0.2f, 0.3f, 0.3f, 1.0f);
	mainWindow = nullptr;
}

EngineWindow::~EngineWindow()
{

}


#pragma region Start

void EngineWindow::Start()
{
	InitGLFW();
}

void EngineWindow::InitGLFW()
{
	if (!glfwInit())
	{
		cerr << "Failed to initialize GLFW" << endl;
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	mainWindow = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	if (mainWindow == nullptr)
	{
		cerr << "Failed to create window !" << endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(mainWindow);
	glfwSetFramebufferSizeCallback(mainWindow, ResizeWindow);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		glfwTerminate();
		return;
	}

	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

#pragma endregion

#pragma region Update

void EngineWindow::Update() const
{
	UpdateWindow();
}

void EngineWindow::UpdateWindow() const
{
	glfwSwapBuffers(mainWindow);
}

#pragma endregion

#pragma region Stop

void EngineWindow::Stop() const
{
	StopWindow();
}

void EngineWindow::StopWindow() const
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void EngineWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

#pragma endregion

void ResizeWindow(GLFWwindow* _window, const int _width, const int _height)
{
	glViewport(0, 0, _width, _height);
}