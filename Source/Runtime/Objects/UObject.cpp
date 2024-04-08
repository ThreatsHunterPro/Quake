#include "UObject.h"

void UObject::BeginDestroy()
{
	// is to remove pour le GC
	// est appelé quand le gc marque
}

void UObject::FinishDestroy()
{
	// est appelé quand le gc balaye
}