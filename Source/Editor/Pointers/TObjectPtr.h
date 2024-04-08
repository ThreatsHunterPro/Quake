#pragma once

using namespace std;

class TObjectPtr
{
public:
	virtual ~TObjectPtr() {};
};

template <typename T>
class TSmartPtr : public TObjectPtr
{
protected:
	T* pointer;

public:
	T* Get() const
	{
		return pointer;
	}

public:
	TSmartPtr(T* _pointer)
	{
		pointer = _pointer;
	}

public:
	void operator()(nullptr_t)
	{
		pointer = nullptr;
	}
	bool operator!() const
	{
		return pointer == nullptr;
	}
	T& operator*() const
	{
		return *pointer;
	}
	T* operator->() const
	{
		return pointer;
	}
};