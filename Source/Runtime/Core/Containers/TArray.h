#pragma once
#include <iostream>

using namespace std;

template <typename Type, typename SizeType = size_t>
class TArray
{
	Type* tArray;
    SizeType count;

public:
    inline SizeType Num() const
    {
        return count;
    }
    inline Type* GetArray()const
    {
        return tArray;
    }
    inline bool IsEmpty() const
    {
        return count == 0;
    }
    inline bool IsValidIndex(const SizeType& _index) const
    {
        return _index >= 0 && _index < count;
    }
    inline Type Top() const
    {
        if (IsEmpty()) return Type();
        return tArray[0];
    }
    inline Type Last() const
    {
        if (IsEmpty()) return Type();
        return tArray[count - 1];
    }
    inline Type* begin() const 
    {
        return tArray;
    }
    inline Type* end() const
    {
        return tArray + count;
    }

public:
    // Constructor, initializes element number counters.
    TArray()
    {
        tArray = nullptr;
        count = 0;
    }

    // Copy constructor.
    TArray(TArray<Type, SizeType>& _other)
    {
        tArray = _other.tArray;
        count = _other.count;
    }

    // Move constructor.
    TArray(TArray<Type, SizeType>&& _other)
    {
        tArray = _other.tArray;
        count = _other.count;

        _other.tArray = nullptr;
        _other.count = 0;
    }

    // Initializer list constructor
    TArray(const initializer_list<Type>& _initList)
    {
        count = _initList.size();
        if (IsEmpty()) return;

        tArray = new Type[count];

        int _index = 0;
        for (const initializer_list<Type>::value_type& _element : _initList)
        {
            tArray[_index] = _element;
            _index++;
        }
    }

    // Constructor from a raw array of elements.
    TArray(const Type* _otherArray, const SizeType& _count)
    {
        count = _count;
        tArray = new Type[count];

        for (size_t _index = 0; _index < count; _index++)
        {
            tArray[_index] = _otherArray[_index];
        }
    }

    ~TArray()
    {
        if (!tArray)
            return;
        delete[] tArray;
    }

public:
    // Adds
    SizeType Add(const Type& _element)
    {
        count++;
        Type* _newArray = new Type[count];

        for (size_t _index = 0; _index < count - 1; _index++)
        {
            _newArray[_index] = tArray[_index];
        }

        _newArray[count - 1] = _element;
        delete[] tArray;
        tArray = _newArray;

        return count;
    }
    SizeType Append(const TArray<Type>& _elements)
    {
        const size_t& _elementsCount = _elements.Num();
        for (size_t _index = 0; _index < _elementsCount; _index++)
        {
            Add(_elements[_index]);
        }

        return count;
    }
    SizeType Append(const Type* _elements, const SizeType& _count)
    {
        for (size_t _index = 0; _index < _count; _index++)
        {
            Add(_elements[_index]);
        }

        return count;
    }
    SizeType Append(const initializer_list<Type>& _initList)
    {
        for (const auto& _element : _initList)
        {
            Add(_element);
        }

        return count;
    }
    SizeType Insert(const TArray<Type>& _elements, const SizeType _index)
    {
        const size_t& _elementsCount = _elements.Num();
        count += _elementsCount;
        Type* _newArray = new Type[count];

        for (size_t _currentIndex = 0; _currentIndex < _index; _currentIndex++)
        {
            _newArray[_currentIndex] = tArray[_currentIndex];
        }
        
        for (size_t _currentIndex = 0; _currentIndex < _elementsCount; _currentIndex++)
        {
            _newArray[_index + _currentIndex] = _elements[_currentIndex];
        }

        for (size_t _currentIndex = _index; _currentIndex < count; _currentIndex++)
        {
            _newArray[_currentIndex + _elementsCount] = tArray[_currentIndex];
        }

        delete[] tArray;
        tArray = _newArray;

        return count;
    }
    SizeType Insert(Type&& _element, const SizeType& _index)
    {
        count++;
        Type* _newArray = new Type[count];

        for (size_t _currentIndex = 0; _currentIndex < _index; _currentIndex++)
        {
            _newArray[_currentIndex] = tArray[_currentIndex];
        }

        _newArray[_index] = _element;
        _element = Type();

        for (size_t _currentIndex = _index + 1; _currentIndex < count; _currentIndex++)
        {
            _newArray[_currentIndex + _elementsCount] = tArray[_currentIndex];
        }

        delete[] tArray;
        tArray = _newArray;

        return count;
    }
    SizeType Insert(const initializer_list<Type>& _initList, const SizeType& _index)
    {
        const size_t& _elementsCount = _elements.Num();
        count += _elementsCount;
        Type* _newArray = new Type[count];

        for (size_t _currentIndex = 0; _currentIndex < _index; _currentIndex++)
        {
            _newArray[_currentIndex] = tArray[_currentIndex];
        }

        int _listIndex = 0;
        for (const auto& _element : _initList)
        {
            _newArray[_index + ++_listIndex] = _element;
        }

        for (size_t _currentIndex = _index + 1; _currentIndex < count; _currentIndex++)
        {
            _newArray[_currentIndex + _elementsCount] = tArray[_currentIndex];
        }

        delete[] tArray;
        tArray = _newArray;

        return count;
    }
    SizeType Insert(const Type* _elements, const SizeType& _count, const SizeType& _index)
    {
        count += _count;
        Type* _newArray = new Type[count];

        for (size_t _currentIndex = 0; _currentIndex < _index; _currentIndex++)
        {
            _newArray[_currentIndex] = tArray[_currentIndex];
        }

        for (size_t _currentIndex = 0; _currentIndex < _elementsCount; _currentIndex++)
        {
            _newArray[_index + _currentIndex] = _elements[_currentIndex];
        }

        for (size_t _currentIndex = _index + 1; _currentIndex < count; _currentIndex++)
        {
            _newArray[_currentIndex + _elementsCount] = tArray[_currentIndex];
        }

        delete[] tArray;
        tArray = _newArray;

        return count;
    }

    // Removes
    void Empty()
    {
        delete tArray;
        tArray = nullptr;
        count = 0;
    }
    SizeType RemoveBack()
    {
        if (IsEmpty()) return 0;

        count--;
        Type* _newArray = new Type[count];

        for (size_t _index = 0; _index < count; _index++)
        {
            _newArray[_index] = tArray[_index];
        }

        delete[] tArray;
        tArray = _newArray;

        return count;
    }
    SizeType Remove(const Type& _element)
    {
        const SizeType& _index = Find(_element);
        if (_index == -1) return count;

        return RemoveAt(_index);
    }
    SizeType RemoveAll(const Type& _element)
    {
        const TArray<SizeType>& _indexes = FindAll(_element);
        if (_indexes.IsEmpty()) return count;

        _indexes.Display();

        const SizeType& _indexesCount = _indexes.Num();
        for (size_t _index = 0; _index < _indexesCount; _index++)
        {
            RemoveAt(_indexes[_index] - _index);
        }

        // Retourne le nombre d'éléments effacés
        return _indexesCount;
    }
    void RemoveAt(const SizeType& _index)
    {
        if (!IsValidIndex(_index)) return;

        Type* _newArray = new Type[count - 1];

        bool _hasRemoved = false;
        for (size_t _currentIndex = 0; _currentIndex < count; _currentIndex++)
        {
            if (_currentIndex == _index)
            {
                _hasRemoved = true;
                continue;
            }
            _newArray[_currentIndex - _hasRemoved] = tArray[_currentIndex];
        }

        delete[] tArray;
        tArray = _newArray;
        count--;
    }

    // Checks
    bool Contains(const Type& _element) const
    {
        for (size_t _index = 0; _index < count; _index++)
        {
            if (tArray[_index] == _element) return true;
        }

        return false;
    }
    SizeType Find(const Type& _element)
    {
        for (size_t _index = 0; _index < count; _index++)
        {
            if (tArray[_index] == _element) return _index;
        }

        return -1;
    }
    TArray<SizeType> FindAll(const Type& _element)
    {
        TArray<SizeType> _indexes;

        for (size_t _index = 0; _index < count; _index++)
        {
            if (tArray[_index] == _element)
            {
                _indexes.Add(_index);
            }
        }

        return _indexes;
    }
    SizeType FindLast(const Type& _element)
    {
        if (IsEmpty()) return -1;

        for (size_t _index = count - 1; _index >= 0; _index--)
        {
            if (tArray[_index] == _element) return _index;
        }

        return -1;
    }
    void Display() const
    {
        for (size_t _index = 0; _index < count; _index++)
        {
            cout << tArray[_index] << " ";
        }
        cout << endl;
    }

public:
    TArray<Type>& operator = (const TArray<Type>& _other)
    {
        tArray = _other.tArray;
        count = _other.count;
        return *this;
    }
    Type operator [] (const SizeType& _index) const
    {
        return tArray[_index];
    }
};