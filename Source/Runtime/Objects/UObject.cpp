#include "UObject.h"

UObject::UObject(UWorld* _world)
{
	world = _world;
}

void UObject::BeginDestroy()
{
	// is to remove pour le GC
	// est appelé quand le gc marque
}

void UObject::FinishDestroy()
{
	// est appelé quand le gc balaye
}