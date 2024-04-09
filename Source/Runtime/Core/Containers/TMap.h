#pragma once
#include<map>
#include<iostream>
#include<utility>

using namespace std;

template <typename TKey, typename TValue>
class TMap
{
	map<TKey, TValue> currentMap;

public:
	int Num() const
	{
		return currentMap.size();
	}
	bool IsEmpty() const
	{
		return currentMap.empty();
	}
	bool Contains(const TKey& _key) const
	{
		for (map<TKey, TValue>::const_iterator _it = currentMap.begin(); _it != currentMap.end(); _it++)
		{
			if (_it->first == _key)
			{
				return true;
			}
		}
		return false;
	}

	//map<TKey,TValue>::iterator& Begin() const
	//{
	//	return currentMap.begin();
	//}	

	//map::const_iterator& End() const
	//{
	//	return currentMap.end();
	//}

public:
	TMap()
	{
		currentMap = map<TKey, TValue>();
	}
public:

	void Append(const TMap<TKey, TValue>& _other)
	{
		//currentMap.insert(_other.Begin(), _other.End());
	}

	void Add(const TKey& _key, const TValue& _value)
	{
		currentMap.emplace(_key, _value);
	}

	void Empty()
	{
		currentMap.clear();
	}

#pragma region DEBUG

	void ReadAllValue()
	{
		for (map<TKey, TValue>::const_iterator _it = currentMap.begin(); _it != currentMap.end(); _it++)
		{
			cout << _it->first << " " << _it->second << endl;
		}
	}

#pragma endregion

public:
	int RemoveAt(const TKey& _key)
	{
		if (!Contains(_key))
			return Num();
		currentMap.erase(_key);
		return Num();
	}
public:
	TValue* Find(const TKey& _key)
	{
		for (map<TKey, TValue>::iterator _it = currentMap.begin(); _it != currentMap.end(); _it++)
		{
			if (_it->first == _key)
			{
				cout << _it->second << endl;
				return &_it->second;
			}
		}
		return nullptr;
	}

	const TKey* FindKey(const TValue& _value)
	{
		for (map<TKey, TValue>::const_iterator _it = currentMap.begin(); _it != currentMap.end(); _it++)
		{
			if (_it->second == _value)
			{
				cout << _it->first << endl;
				return &_it->first;
			}
		}
		return nullptr;
	}

public:
	TMap<TKey, TValue>& operator= (const TMap<TKey, TValue>& _other)
	{
		currentMap = _other.currentMap;
		return *this;
	}

	//TValue operator[] (const TKey& _key)
	//{
	//	for (map<TKey, TValue>::iterator _it = currentMap.begin(); _it != currentMap.end(); _it++)
	//	{
	//		if (_it->first == _key)
	//		{
	//			return &_it->second;
	//		}
	//	}
	//	return nullptr;
	//}
};

