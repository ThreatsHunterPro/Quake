#pragma once
#include "..\..\Runtime\Core\Containers\TArray.h"
#include "../Pointers/TSoftObjectPtr.h"

class GarbageCollector
{
	TArray<TObjectPtr*> allPointers;
	TArray<void*> garbages;

public:
	static GarbageCollector& GetInstance();

public:
	~GarbageCollector();

private:
	void Cleanup();

public:
	template <typename T>
	void Register(T* _pointer)
	{
		const function<void(T*)>& _destructor = [](T* _ptr) { 
			cout << "DESTRUCTION !" << endl;
			delete _ptr; 
		};
		TSoftObjectPtr<T>* _object = new TSoftObjectPtr<T>(_pointer, _destructor);
		allPointers.Add(_object);
	}
	template <typename T>
	void AddToCleanup(void* _pointer)
	{
		if (!_pointer || garbages.Contains(_pointer)) return;

		for (TObjectPtr* _object : allPointers)
		{
			if (TSoftObjectPtr<T>* _softObject = dynamic_cast<TSoftObjectPtr<T>*>(_object))
			{
				if (_softObject->Get() == _pointer) return;
			}
		}

		garbages.Add(_pointer);
	}
};