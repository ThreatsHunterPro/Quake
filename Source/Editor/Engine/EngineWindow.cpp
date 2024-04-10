#include "EngineWindow.h"
#include "Source/Editor/Engine/Widgets/PlaceActorsWidget.h"
#include "Source/Editor/Engine/Widgets/DetailsWindow.h"

#include "Source/Editor/Engine/Widgets/WorldSettings.h"
EngineWindow::EngineWindow()
{
	title = "Quake";
	size = FVector2(1920, 1080);
	bgColor = FColor(51, 85, 85, 255);
	mainWindow = nullptr;

	widgets.Add(new PlaceActorsWidget(FString("test"), this));
	widgets.Add(new WorldSettingsWidget(FString("Wolrd"), this));
	//widgets.Add(new PlaceActorsWidget(FString("test"), this));
	widgets.Add(new DetailsWindow(FString("Details"), this));
}

EngineWindow::~EngineWindow()
{
	for (size_t i = 0; i < widgets.Num(); i++)
	{
		delete widgets[i];
	}
	widgets.Empty();
}


#pragma region Start

void EngineWindow::Start()
{
	InitGLFW();
	InitImGUI();
=======
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
>>>>>>> main
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
	mainWindow = glfwCreateWindow(size.X, size.Y, title.GetText().c_str(), nullptr, nullptr);
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

	glClearColor((float)bgColor.color.RGB.R/255.f, (float)bgColor.color.RGB.G/255.f, (float)bgColor.color.RGB.B/255.f, (float)bgColor.color.RGB.A/255.f);
}

void EngineWindow::InitImGUI()
{
	//Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
}

#pragma endregion

#pragma region Update

void EngineWindow::Update()
{
	UpdateWidgets();
	UpdateWindow();
}

void EngineWindow::UpdateWidgets()
{
	//Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Draw widgets
	const int _widgetsCount = widgets.Num();
	for (int _widgetIndex = 0; _widgetIndex < _widgetsCount; _widgetIndex++)
	{
		Widget* _widget = widgets[_widgetIndex];
		if (!_widget) continue;
		_widget->Draw();
	}
	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EngineWindow::UpdateWindow()
{
	glfwSwapBuffers(mainWindow);
}

#pragma endregion

#pragma region Stop

void EngineWindow::Stop()
{
	StopImGUI();
	StopWindow();
}

void EngineWindow::StopImGUI()
{
	// Stop widgets
	const int _widgetsCount = widgets.Num();
	for (int _widgetIndex = 0; _widgetIndex < _widgetsCount; _widgetIndex++)
	{
		Widget* _widget = widgets[_widgetIndex];
		if (!_widget) continue;
		_widget->Stop();
	}

	// Clean ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EngineWindow::StopWindow()
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