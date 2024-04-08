#include "FString.h"

#pragma region Constructors

FString::FString()
{
	text = string();
}

FString::FString(const char* _text)
{
	text = string(_text);
}

FString::FString(const FString& _text)
{
	text = _text.text;
}

#pragma endregion

#pragma region Adds

FString& FString::Append(const char* _text)
{
	text.append(_text);
	return *this;
}

FString FString::Append(const FString& _other)
{
	return Append(_other.text.c_str());
}

void FString::InsertAt(const uInt& _index, const char* _text)
{
	const string::const_iterator& _startIt = text.begin() + _index;
	text.insert(_startIt, *_text);
}

void FString::InsertAt(const uInt& _index, const FString& _other)
{
	InsertAt(_index, _other.text.c_str());
}

#pragma endregion

#pragma region Removes

void FString::RemoveAt(const uInt& _index, const int _count)
{
	const string::const_iterator& _startIt = text.begin() + _index;
	const string::const_iterator& _endIt = _startIt + _count;
	text.erase(_startIt, _endIt);
}

void FString::Replace(const char* _oldText, const char* _textToRemove)
{
	while (true)
	{
		const uInt& _pos = Find(_oldText);
		if (_pos == -1) break;

		const string::iterator& _startIt = text.begin() + _pos;
		const string::iterator& _endIt = _startIt + strlen(_oldText);
		text.replace(_startIt, _endIt, _textToRemove, strlen(_textToRemove));
	}
}

void FString::Replace(const FString& _oldText, const FString& _textToRemove)
{
	Replace(_oldText.text.c_str(), _textToRemove.text.c_str());
}

void FString::Empty()
{
	text.clear();
}

#pragma endregion

#pragma region Checks

bool FString::Contains(const char* _text)
{
	return Find(_text) != -1;
}

bool FString::Contains(const FString& _other)
{
	return Find(_other) != -1;
}

bool FString::EndsWith(const char* _text)
{
	const uInt& _pos = static_cast<const uInt&>(text.find_last_of(_text));
	const uInt& _finalPos = Length() - static_cast<uInt>(strlen(_text)) - 1;
	return _pos == _finalPos;
}

bool FString::EndsWith(const FString& _other)
{
	return EndsWith(_other.text.c_str());
}

bool FString::StartWith(const char* _text)
{
	return Find(_text) == 0;
}

bool FString::StartWith(const FString& _other)
{
	return Find(_other) == 0;
}

bool FString::Equals(const FString& _other)
{
	return operator==(_other);
}

#pragma endregion

#pragma region Finds

uInt FString::Find(const char* _text)
{
	const uInt& _pos = static_cast<const uInt&>(text.find(string(_text)));
	return _pos != string::npos ? _pos : -1;
}

uInt FString::Find(const FString& _other)
{
	return Find(_other.text.c_str());
}

uInt FString::FindChar(const char _letter)
{
	return Find(&_letter);
}

uInt FString::FindLastChar(const char _letter)
{
	const uInt& _pos = static_cast<const uInt&>(text.find_last_of(_letter));
	return _pos != string::npos ? _pos : -1;
}

#pragma endregion

#pragma region Converts

FString FString::FromInt(const int _value)
{
	return FString(to_string(_value).c_str());
}

FString FString::SanitizeFloat(const float _value)
{
	return FString(to_string(_value).c_str());
}

FString FString::ToLower()
{
	string _lowerText = text;

	for (char& _letter : _lowerText)
	{
		_letter = tolower(_letter);
	}

	return FString(_lowerText.c_str());
}

FString FString::ToUpper()
{
	string _lowerText = text;

	for (char& _letter : _lowerText)
	{
		_letter = toupper(_letter);
	}

	return FString(_lowerText.c_str());
}

void FString::Display() const
{
	cout << text << endl;
}

#pragma endregion

#pragma region Operators

FString& FString::operator=(const char* _text)
{
	text = _text;
	return *this;
}

FString& FString::operator=(const FString& _text)
{
	text = _text.text;
	return *this;
}

bool FString::operator==(const char* _text)
{
	return text == _text;
}

bool FString::operator==(const FString& _text)
{
	return text == _text.text;
}

bool FString::operator!=(const char* _text)
{
	return text != _text;
}

bool FString::operator!=(const FString& _text)
{
	return text != _text.text;
}

FString& FString::operator += (const char* _text)
{
	text += _text;
	return *this;
}

FString& FString::operator+=(const FString& _text)
{
	text += _text.text;
	return *this;
}

const char* FString::operator [] (const uInt& _index)
{
	return &text[_index];
}

string FString::operator*()
{
	return text;
}

#pragma endregion