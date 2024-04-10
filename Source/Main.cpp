#define STB_IMAGE_IMPLEMENTATION // a definir avec <stb_image.h> au dans le main

#include "CoreMinimal.h"
#include "Runtime/Managers/UGameInstance.h"
#include "Runtime/Objects/Actors/AActor.h"

#include "Editor/Pointers/TSharedPtr.h"
#include "Source/Editor/Engine/Engine.h"
#include <reactphysics3d/reactphysics3d.h>
#include "Runtime/PhysicsCore/CollisionShape.h"

using namespace std;
using namespace glm;
using namespace reactphysics3d;

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

	FCollisionShape _shape;

	_shape.MakeBox(FVector(100, 500, 600));
	_shape.GetBox().ToString().Display();


	Engine* _engine = new Engine();
	_engine->Launch();
	delete _engine;
	
	//PhysicsCommon _physics;
	
	//PhysicsWorld::WorldSettings _settings;
	//_settings.worldName = "le monde de THOMAS";
	//_settings.defaultVelocitySolverNbIterations = 20;
	//_settings.isSleepingEnabled = false;
	//_settings.gravity = Vector3(0, -9.81, 0);

	
	
	//PhysicsWorld* _world = _physics.createPhysicsWorld();
	//
	//_world->setIsGravityEnabled(true);
	//_world->setGravity(FVector().ToReactVector3())

	//
	//
	//Transform _tranforms = Transform::identity();
	//RigidBody* _body = _world->createRigidBody(_tranforms);
	//_body->enableGravity(false);
	//
	//SphereShape* _sphere = _physics.createSphereShape(3.0f);
	//
	//Collider* _collider = _body->addCollider(_sphere, _tranforms);
	//
	//
	//const float timeStep = 1.0f / 60.0f;
	//
	//// Step the simulation a few steps
	//for (int i = 0; i < 20; i++) {
	//	_world->update(timeStep);
	//	// Get the updated position of the body
	//	const Transform& transform = _body->getTransform();
	//	const Vector3& position = transform.getPosition();
	//	// Display the position of the body
	//	std::cout << " Body Position : (" << position.x << "," <<
	//		position.y << ", " << position.z << ")" << std::endl;
	//}

	// Array with the vertices coordinates of the convex mesh
	//float vertices[24] = { -3 , -3 , 3,
	//3, -3, 3,
	//3, -3, -3,
	//3, -3, -3,
	//-3, 3 , 3,
	//3, 3, 3,
	//3, 3, -3,
	//-3, 3 , -3 };
	//// Vertex array with all vertices of the mesh
	//rp3d::VertexArray vertexArray(vertices, 3 * sizeof(float),
	//	24, rp3d::VertexArray::DataType::VERTEX_FLOAT_TYPE);
	//// Compute the convex mesh using only the array of vertices
	//std::vector < rp3d::Message > messages;
	//ConvexMesh* convexMesh = _physics.createConvexMesh(
	//	vertexArray, messages);
	//// Display the messages (info , warning and errors )
	//if (messages.size() > 0) {
	//	for (const rp3d::Message& message : messages) {
	//		std::string messageType;
	//		switch (message.type) {
	//		case rp3d::Message::Type::Information:
	//			messageType = " info ";
	//			break;
	//		case rp3d::Message::Type::Warning:
	//			messageType = " warning ";
	//			break;
	//		case rp3d::Message::Type::Error:
	//			messageType = " error ";
	//			break;
	//		}
	//		std::cout << " Message (" << messageType << "): " <<
	//			message.text << std::endl;
	//	}
	//}
	//assert(convexMesh != nullptr);

	
	
	//Vector3 scaling(1, 1, 1);
	//// Create the ConvexMeshShape
	//ConvexMeshShape* convexMeshShape = _physics.createConvexMeshShape(convexMesh, scaling);	
}