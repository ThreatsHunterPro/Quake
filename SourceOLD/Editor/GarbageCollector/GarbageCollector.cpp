#include "GarbageCollector.h"

GarbageCollector& GarbageCollector::GetInstance()
{
	static GarbageCollector _instance;
	return _instance;
}

GarbageCollector::~GarbageCollector()
{
	for (TObjectPtr* _pointer : allPointers)
	{
		delete _pointer;
	}

	Cleanup();
}

void GarbageCollector::Cleanup()
{
	for (void* _pointer : garbages)
	{
		delete _pointer;
	}

	garbages.Empty();
}