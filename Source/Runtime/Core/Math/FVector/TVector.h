#pragma once
#include <iostream>
#include "../../Containers/FString.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;
class FString;
class FMath;

#define SMALL_NUMBER 1.e-8f

template<typename T>
struct TVector
{
	static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "T must be floating point or an integer");

#pragma region Var
	T X;
	T Y;
	T Z;

	static TVector<T> ZeroVector;
	static TVector<T> UpVector;
	static TVector<T> ForwardVector;
	static TVector<T> RightVector;

	T XYZ[3] = { X,Y,Z };
#pragma endregion Var

public:
	TVector() : TVector(0) {}
	/// <summary>
	/// X,Y,Z are Equals
	/// </summary>T
	/// <param name="_value"></param>
	TVector(T _value)
	{
		X = Y = Z = _value;
	}
	TVector(T _x, T _y, T _z)
	{
		X = _x;
		Y = _y;
		Z = _z;
	}
	TVector(const TVector<T>& _other)
	{
		X = _other.X;
		Y = _other.Y;
		Z = _other.Z;
	}
	//TVector<T>(const FVector4& _vector)
	//TVector<T>(const FLinearColor& _color);
	//TVector<T>(const FVector2D& _vector, float _z);

public:
	static T Distance(const TVector<T>& _vectorA, const TVector<T>& _vectorB)
	{
		return sqrt(pow(_vectorB.X - _vectorA.X, 2) + pow(_vectorB.Y - _vectorA.Y, 2) + pow(_vectorB.Z - _vectorA.Z, 2));
	}
	/// <summary>
	/// sqrt(pow(x - _other.x, 2) + pow(y - _other.y, 2) + pow(z - _other.z, 2));
	/// </summary>
	/// <param name="_other"></param>
	/// <returns></returns>
	T Distance(const TVector<T>& _other) const
	{
		return sqrt(pow(X - _other.X, 2) + pow(Y - _other.Y, 2) + pow(Z - _other.Z, 2));
	}
	/// <summary>
	/// x = y * _vectorB.z - z * _vectorB.y;
	/// y = z * _vectorB.x - x * _vectorB.z;</summary>
	/// z = x * _vectorB.y - y * _vectorB.x;<param name="_vectorB"></param>
	/// <returns></returns>
	TVector CrossProduct(const TVector<T>& _vectorB)
	{
		TVector<T> _result;
		_result.X = Y * _vectorB.Z - Z * _vectorB.Y;
		_result.Y = Z * _vectorB.X - X * _vectorB.Z;
		_result.Z = X * _vectorB.Y - Y * _vectorB.X;

		return _result;
	}
	/// <summary>
	/// x * _vectorB.x + y * _vectorB.y + z * _vectorB.z;
	/// </summary>
	/// <param name="_vectorB"></param>
	/// <returns></returns>
	const T DotProduct(const TVector<T>& _vectorB)
	{
		return X * _vectorB.X + Y * _vectorB.Y + Z * _vectorB.Z;
	}
	/// <summary>
	/// sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	/// </summary>
	/// <returns></returns>
	T Length() const
	{
		return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
	}
	/// <summary>
	/// Safely returns the normal (if the value is too small)
	/// </summary>
	/// <returns></returns>
	TVector<T> GetSafeNormal() const
	{
		const float _squareSum = X * X + Y * Y + Z * Z;
		if (_squareSum == 1)
			return *this;
		if (_squareSum < SMALL_NUMBER)
			return ZeroVector;

		return Normalize();
	}
	/// <summary>
	/// x / Magnitude(), y / Magnitude(), z / Magnitude()
	/// </summary>
	/// <returns></returns>
	TVector Normalize() const
	{
		TVector<T> _result = TVector<T>(X / Length(), Y / Length(), Z / Length());
		return _result;
	}
	/// <summary>
	/// pow(Magnitude(),2)
	/// </summary>
	/// <returns></returns>
	T SquaredLength() const
	{
		return pow(X, 2) + pow(Y, 2) + pow(Z, 2);
	}
	/// <summary>
	/// "(x,y,z)" Is used in the operator<<() (no need to use it manually to cout)
	/// </summary>
	/// <returns></returns>
	FString ToString() const
	{
		return FString::Format("X={} Y={} Z={}", X, Y, Z);
	}
	vec3 ToVec3()
	{
		return vec3(X, Y, Z);
	}

#pragma region Operator 

	//inverse
	TVector<T> operator-()
	{
		TVector<T> _result;
		_result.X = -X;
		_result.Y = -Y;
		_result.Z = -Z;
		return _result;
	}

	//+
	TVector<T> operator+(const TVector<T>& _other)
	{
		TVector<T> _result = TVector<T>(*this);
		_result.X += _other.X;
		_result.Y += _other.Y;
		_result.Z += _other.Z;

		return _result;
	}
	TVector<T> operator+(const T _other)
	{
		return operator+(TVector<T>(_other));
	}
	TVector<T> operator+(const vec3& _other)
	{
		TVector<T> _result = TVector<T>(*this);
		_result.X += _other.x;
		_result.Y += _other.y;
		_result.Z += _other.z;

		return _result;
	}

	//-
	TVector<T> operator-(const TVector<T>& _other)
	{
		TVector<T> _result = TVector<T>(*this);
		_result.X -= _other.X;
		_result.Y -= _other.Y;
		_result.Z -= _other.Z;

		return _result;
	}
	TVector<T> operator-(const T _other)
	{
		return operator-(TVector<T>(_other));
	}
	TVector<T> operator-(const vec3& _other)
	{
		TVector<T> _result = TVector<T>(*this);
		_result.X -= _other.x;
		_result.Y -= _other.y;
		_result.Z -= _other.z;

		return _result;
	}

	//*
	TVector<T> operator*(const TVector<T>& _other)
	{
		TVector<T> _result = TVector<T>(*this);
		_result.X *= _other.X;
		_result.Y *= _other.Y;
		_result.Z *= _other.Z;

		return _result;
	}
	TVector<T> operator*(const T _other)
	{
		return operator*(TVector<T>(_other));
	}
	TVector<T> operator*(const vec3& _other)
	{
		TVector<T> _result = TVector<T>(*this);
		_result.X *= _other.x;
		_result.Y *= _other.y;
		_result.Z *= _other.z;

		return _result;
	}

	// /
	TVector<T> operator/(const TVector<T>& _other)
	{
		if (_other.X == 0 || _other.Y == 0 || _other.Z == 0)
		{
			cerr << "[TVector<T>::operator/] => a value is equal to 0";
			return TVector<T>();
		}

		TVector<T> _result = TVector<T>(*this);

		_result.X /= _other.X;
		_result.Y /= _other.Y;
		_result.Z /= _other.Z;

		return _result;
	}
	TVector<T> operator/(const T _other) 
	{
		return operator/(TVector<T>(_other));
	}
	TVector<T> operator/(const vec3& _other)
	{
		if (_other.x == 0 || _other.y == 0 || _other.z == 0)
		{
			cerr << "[TVector<T>::operator/] => a value is equal to 0";
			return TVector<T>();
		}

		TVector<T> _result = TVector<T>(*this);

		_result.X /= _other.x;
		_result.Y /= _other.y;
		_result.Z /= _other.z;

		return _result;
	}

	//+=
	TVector<T> operator+=(const TVector<T>& _other)
	{
		X = X + _other.X;
		Y = Y + _other.Y;
		Z = Z + _other.Z;
		return *this;
	}
	TVector<T> operator+=(const T _other)
	{
		return operator+=(TVector<T>(_other));
	}
	TVector<T> operator+=(const vec3& _other)
	{
		X = X + _other.x;
		Y = Y + _other.y;
		Z = Z + _other.z;
		return *this;
	}

	//-=
	TVector<T> operator-=(const TVector<T>& _other)
	{
		X = X - _other.X;
		Y = Y - _other.Y;
		Z = Z - _other.Z;
		return *this;
	}
	TVector<T> operator-=(const T _other)
	{
		return operator-=(TVector<T>(_other));
	}
	TVector<T> operator-=(const vec3& _other)
	{
		X = X - _other.x;
		Y = Y - _other.y;
		Z = Z - _other.z;
		return *this;
	}

	//*= 
	TVector<T> operator*=(const TVector<T>& _other)
	{
		X = X * _other.X;
		Y = Y * _other.Y;
		Z = Z * _other.Z;
		return *this;
	}
	TVector<T> operator*=(const T _other)
	{
		return operator*=(TVector<T>(_other));
	}
	TVector<T> operator*=(const vec3& _other)
	{
		X = X * _other.x;
		Y = Y * _other.y;
		Z = Z * _other.z;
		return *this;
	}

	// /=
	TVector<T> operator/=(const TVector<T>& _other)
	{
		if (_other.X == 0 || _other.Y == 0 || _other.Z == 0)
		{
			cerr << "[TVector<T>::operator/] => a value is equal to 0";
			return TVector<T>();
		}

		X = X / _other.X;
		Y = Y / _other.Y;
		Z = Z / _other.Z;

		return *this;
	}
	TVector<T> operator/=(const T _other)
	{
		return operator/=(TVector<T>(_other));
	}
	TVector<T> operator/=(const vec3& _other)
	{
		if (_other.x == 0 || _other.y == 0 || _other.z == 0)
		{
			cerr << "[TVector<T>::operator/] => a value is equal to 0";
			return TVector<T>();
		}

		X = X / _other.x;
		Y = Y / _other.y;
		Z = Z / _other.z;

		return *this;
	}

	//=
	TVector<T> operator=(const TVector<T>& _other) 
	{
		X = _other.X;
		Y = _other.Y;
		Z = _other.Z;
		return *this;
	}
	TVector<T> operator=(const T _other)
	{
		return operator=(TVector<T>(_other));
	}
	TVector<T> operator=(const vec3& _other)
	{
		X = _other.x;
		Y = _other.y;
		Z = _other.z;
		return *this;
	}

	//crossProduct
	TVector<T> operator^(const TVector<T>& _other)
	{
		return CrossProduct(_other);
	}

	//dotProduct
	TVector<T> operator|(const TVector<T>& _other)
	{
		return DotProduct(_other);
	}

	//Checks
	bool operator==(const TVector<T>& _other)
	{
		return X == _other.X && Y == _other.Y && Z == _other.Z;
	}
	bool operator==(const vec3& _other)
	{
		return X == _other.x && Y == _other.y && Z == _other.z;
	}

	bool operator!=(const TVector<T>& _other)
	{
		return !operator==(_other);
	}
	bool operator!=(const vec3& _other)
	{
		return !operator==(_other);
	}

	T& operator[](int _index)
	{
		return XYZ[_index];
	}
#pragma endregion Operator 


};



template<typename T>
TVector<T> TVector<T>::ZeroVector = TVector<T>(0);

template<typename T>
TVector<T> TVector<T>::UpVector = TVector<T>(0, 0, 1);

template<typename T>
TVector<T> TVector<T>::ForwardVector = TVector<T>(1, 0, 0);

template<typename T>
TVector<T> TVector<T>::RightVector = TVector<T>(0, 1, 0);