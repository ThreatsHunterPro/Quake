#include "UObject.h"

UObject::UObject(UWorld* _world)
{
	world = _world;
}

void UObject::BeginDestroy()
{
	// is to remove pour le GC
	// est appel� quand le gc marque
}

void UObject::FinishDestroy()
{
	// est appel� quand le gc balaye
}