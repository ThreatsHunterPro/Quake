#pragma once
#include "..\..\Runtime\Core\Containers\TArray.h"
#include "TObjectPtr.h"
#include "../GarbageCollector/GarbageCollector.h"

template <typename T>
class TSharedPtr : public TSmartPtr<T>
{
	int* count;

public:
	inline int Count() const
	{
		return *count;
	}

public:
	TSharedPtr() : TSmartPtr<T>(nullptr)
	{
		count = nullptr;
	}
	TSharedPtr(T* _pointer) : TSmartPtr<T>(_pointer)
	{
		count = new int(1);
	}
	TSharedPtr(const TSharedPtr& _other) : TSmartPtr<T>(_other.pointer)
	{
		count = _other.count;
		(*count)++;
	}
	~TSharedPtr()
	{
		Unregister();
	}

public:
	void Unregister()
	{
		if (!count) return;

		(*count)--;
		if ((*count) == 0)
		{
			GarbageCollector::GetInstance().AddToCleanup<T>(TSharedPtr<T>::pointer);
			delete count;
		}
	}

public:
	TSharedPtr<T>& operator=(const TSharedPtr<T>& _other)
	{
		// Si _other n'est pas la même instance que this
		if (this && this != &_other)
		{
			Unregister();
			TSmartPtr<T>::pointer = _other.pointer;
			count = _other.count;
			(*count)++;
		}

		return *this;
	}

	template <typename T>
	friend class TWeakPtr;
};