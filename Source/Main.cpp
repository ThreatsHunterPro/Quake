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
	sf::Window window(sf::VideoMode(800, 600), "My window");

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}


	return 0;
	/*
	Engine* _engine = new Engine();
	_engine->Launch();
	delete _engine;
	*/
}