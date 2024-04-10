#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

typedef unsigned int uInt;

class FString
{
	string text;

private:
	uInt GetLength(const string& _string) const
	{
		return static_cast<uInt>(_string.size());
	}

public:
	FString();
	FString(const char* _string);
	FString(const FString& _other);

#pragma region Getter
	const uInt Length() const
	{
		return static_cast<uInt>(text.size());
	}
	const string& GetText() const
	{
		return text;
	}
	const string::const_iterator Begin() const
	{
		return text.begin();
	}
	const string::const_iterator End() const
	{
		return text.end();
	}
	const bool IsEmpty() const
	{
		return text.empty();
	}
#pragma endregion

#pragma region Method
	FString& Append(const char* _string);
	FString& Append(const char _char);
	FString& Append(const FString& _string);

	bool Contains(const char* _string);
	bool Contains(FString _string);
	bool EndsWith(const char* _string);
	bool EndsWith(FString _string);
	bool StartsWith(const char* _string);
	bool StartsWith(FString _string);
	bool Equals(FString _string);

	void Empty();

	uInt Find(const char* _string);
	uInt Find(FString _string);
	uInt FindChar(const char _char);
	uInt FindLastChar(const char _char);

	static FString FromInt(const int _int);
	static FString SanitizeFloat(const float _float);

	void InsertAt(const uInt _index, const char* _string);
	void InsertAt(const uInt _index, FString _string);
	void RemoveAt(const uInt _index, const int _size);
	void Replace(const char* _oldText, const char* _newText);
	void Replace(const FString& _oldText, const FString& _newText);

	FString ToLower();
	FString ToUpper();
	void Display();

	FString Trim();
	FString SubString(size_t _begin) const;
	FString SubString(size_t _begin, size_t _end) const;
#pragma endregion

#pragma region Format
private:
	template<typename... _args>
	static void WriteArgToStream(stringstream& ss, vector<string>& _list, _args...) {}

	template<typename _first_arg, typename... _args>
	static void WriteArgToStream(stringstream& ss, vector<string>& _list, _first_arg first_arg, _args... args);

public:
	/**
	* @brief How to use format ?
	* @brief Example: FString::Format("Hello {}", "world");
	* @brief Example: FString::Format("Hello {}, how are you ? {}", "world", "fine");
	* @brief Result: "Hello world, how are you ? fine.
	* 
	* @param _text: first parameter is text which will be formatted. Add {} is each param you want format
	* @param _args: Will be the arguments that replace the {}
	*
	* 
	* @return FString formated	
	*/
	template<typename ...Args>
	static FString Format(const char* _text, Args... _args);

#pragma endregion

#pragma region Operator
	FString& operator = (const char* _string);
	FString& operator = (const FString& _string);
	bool operator == (const char* _string);
	bool operator == (const FString& _string);
	bool operator != (const char* _string);
	bool operator != (const FString& _string);
	FString& operator += (const char _c);
	FString& operator += (const char* _string);
	FString& operator += (const FString& _string);
	const char operator [] (const uInt& _index);
	const char* operator* ();
	FString operator + (const char* _text);
	FString operator + (const FString& _text);
#pragma endregion
};

template <typename _first_arg, typename ... _args>
void FString::WriteArgToStream(stringstream& ss, vector<string>& _list, _first_arg first_arg, _args... args)
{
	if (!_list.empty())
	{
		ss << _list[0]; //récupère le premier element de la liste
		_list.erase(_list.begin()); //on le supprime
	}
	ss << first_arg; //On balance l'argument dans le stringstream
	WriteArgToStream(ss, _list, args...);
}

template<typename ...Args>
inline FString FString::Format(const char* _text, Args... _args)
{
	std::vector<string> res;
	std::string _tmp = std::string(_text);
	int pos = _tmp.find("{}");
	while (pos != std::string::npos)
	{
		res.push_back(_tmp.substr(0, pos));
			_tmp.erase(0, pos + 2);
		pos = _tmp.find("{}");
	}
	if (!_tmp.empty())
		res.push_back(_tmp);

	stringstream ss;
	WriteArgToStream(ss, res, _args...); //on va appeler cette methode tout le long qu'il y ai des args grossièrement
	if (res.size()>1)
		ss << res.back();
	return FString(ss.str().c_str());
}

//ostream& operator << (ostream& _stream, const FString& _string)
//{
//	_stream << _string.GetText();
//	return _stream;
//}