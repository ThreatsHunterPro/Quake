#define STB_IMAGE_IMPLEMENTATION // a definir avec <stb_image.h> au dans le main
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CoreMinimal.h"
#include "Runtime/Managers/UGameInstance.h"
#include "Runtime/Objects/Actors/AActor.h"

#include "Editor/Pointers/TSharedPtr.h"
#include "Source/Editor/Engine/Engine.h"



using namespace std;
using namespace glm;

struct B;
struct A
{
	double value;
	TSharedPtr<B> b;

	A()
	{
		value = 4.2;
		cout << "A est construit !" << endl;
	}
	~A()
	{
		cout << "A est DEconstruit !" << endl;
	}

	void SetB(const TSharedPtr<B>& _b)
	{
		b = _b;
	}
};
struct B
{
	string name;
	TSharedPtr<A> a;

	B(const string& _name)
	{
		name = _name;
		cout << "B est construit !" << endl;
	}
	~B()
	{
		cout << "B est DEconstruit !" << endl;
	}

	void SetA(const TSharedPtr<A>& _a)
	{
		a = _a;
	}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	/*
	#pragma region GC

	GarbageCollector& _gc = GarbageCollector::GetInstance();

#pragma region TSoftObjectPtr

	_gc.Register(new int(42));
	_gc.Register(new char('b'));
	_gc.Register(new string("coucou"));
	_gc.Register(new A());

#pragma endregion

#pragma region TSharedPtr

	TSharedPtr<int> _intShared = TSharedPtr<int>(new int(3));
	cout << "valeur 1 : " << *_intShared << endl;
	cout << "count 1 : " << _intShared.Count() << endl << endl;

	TSharedPtr<int> _intShared2 = _intShared;
	cout << "valeur 2 : " << *_intShared2 << endl;
	cout << "count 1 : " << _intShared.Count() << endl;
	cout << "count 2 : " << _intShared2.Count() << endl << endl;

	*_intShared = 100;
	cout << "Changement de valeur !!!" << endl;
	cout << "valeur 1 : " << *_intShared << endl;
	cout << "valeur 2 : " << *_intShared2 << endl << endl;

	cout << "_intShared = NULL" << endl;
	_intShared = nullptr;
	try
	{
		if (!_intShared)
		{
			throw exception("_intShared est nul !");
		}
		cout << "valeur 1 : " << *_intShared << endl;
	}
	catch (const exception& _error)
	{
		cerr << _error.what() << endl;
	}

	try
	{
		if (!_intShared2)
		{
			throw exception("_intShared2 est nul !");
		}
		cout << "valeur 2 : " << *_intShared2 << endl;
	}
	catch (const exception& _error)
	{
		cerr << _error.what() << endl;
	}

	cout << "_intShared2 = NULL" << endl;
	_intShared2 = nullptr;
	try
	{
		if (!_intShared2)
		{
			throw exception("_intShared2 est nul !");
		}
		cout << "valeur 2 : " << *_intShared2 << endl;
	}
	catch (const exception& _error)
	{
		cerr << _error.what() << endl;
	}

#pragma endregion

#pragma region TWeakPtr

	//TODO

	//TSharedPtr<A> _a = TSharedPtr<A>(new A());
	//TSharedPtr<B> _b = TSharedPtr<B>(new B("Je m'appelle B"));

	//_a->SetB(_b);
	//_b->SetA(_a);

#pragma endregion

	cout << endl << endl << endl << endl;

#pragma endregion
	*/

	

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

	// Ouvre une fenêtre et crée son contexte OpenGl
	GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
	window = glfwCreateWindow(900, 900, "OutLiner", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialise GLEW
	glfwSwapInterval(1);


	glewExperimental = true; // Nécessaire dans le profil de base
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
	
	ImGui::StyleColorsDark();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	
	do {
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		ImGui::ShowDemoWindow();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
/*
	Engine* _engine = new Engine();
	_engine->Launch();
	delete _engine;
*/
	return 0;
	
	
	
}