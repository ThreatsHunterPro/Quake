#pragma once

template <typename T>
class TPtr
{
public:
	TPtr() = default;
	virtual ~TPtr() = default;

public:
	inline virtual T* Get() const { return nullptr; };
};