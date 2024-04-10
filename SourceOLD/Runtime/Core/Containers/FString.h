#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef unsigned int uInt;

class FString
{
	string text;

public:
	const bool IsEmpty() const
	{
		return text.empty();
	}
	const uInt Length() const
	{
		return static_cast<uInt>(text.size());
	}
	const string::const_iterator& Begin() const
	{
		return text.begin();
	}
	const string::const_iterator& End() const
	{
		return text.end();
	}

public:
	FString();
	FString(const char* _text);
	FString(const FString& _text);

public:
	// Adds
	FString& Append(const char* _text);
	FString Append(const FString& _other);
	void InsertAt(const uInt& _index, const char* _text);
	void InsertAt(const uInt& _index, const FString& _other);

	// Removes
	void RemoveAt(const uInt& _index, const int _count);
	void Replace(const char* _oldText, const char* _textToRemove);
	void Replace(const FString& _oldText, const FString& _textToRemove);
	void Empty();

	// Checks
	bool Contains(const char* _text);
	bool Contains(const FString& _other);
	bool EndsWith(const char* _text);
	bool EndsWith(const FString& _other);
	bool StartWith(const char* _text);
	bool StartWith(const FString& _other);
	bool Equals(const FString& _other);

	// Find
	uInt Find(const char* _text);
	uInt Find(const FString& _other);
	uInt FindChar(const char _letter);
	uInt FindLastChar(const char _letter);

	// Converts
	FString FromInt(const int _value);
	FString SanitizeFloat(const float _value);
	FString	ToLower();
	FString	ToUpper();

	void Display() const;

public:
	FString& operator = (const char* _text);
	FString& operator = (const FString& _text);
	bool operator == (const char* _text);
	bool operator == (const FString& _text);
	bool operator != (const char* _text);
	bool operator != (const FString& _text);
	FString& operator += (const char* _text);
	FString& operator += (const FString& _text);
	const char* operator[] (const uInt& _index);
	string operator* ();
};