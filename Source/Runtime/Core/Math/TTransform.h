#pragma once
#include "FVector/TVector.h"
#include "Quat.h"
#include "FMatrix.h"

typedef int T;

template<typename T>
struct TTransform
{
	static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>, "T must be floating point or an integer");

	FQuat Rotation;
	TVector<T> Translation;
	TVector<T> Scale3D;

	static TTransform<T> Identity;

public:
	TTransform()
	{
		Rotation = FQuat::Identity;
		Translation = TVector<T>::ZeroVector;
		Scale3D = TVector<T>((T)1, (T)1, (T)1);
	}
	TTransform(const FQuat& _rotation)
	{
		Rotation = _rotation;
		Translation = TVector<T>::ZeroVector;
		Scale3D = TVector<T>((T)1, (T)1, (T)1);
	}
	TTransform(const FRotator& _rotation)
	{
		FQuat _quatRotation = FQuat(_rotation, 0);
		Rotation = _quatRotation;
		Translation = TVector<T>::ZeroVector;
		Scale3D = TVector<T>((T)1, (T)1, (T)1);
	}
	TTransform(const FQuat& _rotation, const TVector<T>& _translation, const TVector<T>& _scale3D = TVector<T>(1.f, 1.f, 1.f))
	{
		Rotation = _rotation;
		Translation = _translation;
		Scale3D = _scale3D;
	}
	TTransform(const FRotator& _rotation, const TVector<T>& _translation, const TVector<T>& _scale3D = TVector<T>(1.f, 1.f, 1.f))
	{
		FQuat _quatRotation = FQuat(_rotation, 0);
		Rotation = _quatRotation;
		Translation = _translation;
		Scale3D = _scale3D;
	}

	TTransform(const FMatrix& _matrix)
	{
		SetFromMatrix(_matrix);
	}

	TTransform(const TVector<T>& _x, const TVector<T>& _y, const TVector<T>& _z, const TVector<T>& _translation)
	{
		SetFromMatrix(FMatrix(_x, _y, _z, _translation));
	}
public:
	FORCEINLINE TVector<T> GetLocation() const
	{
		return GetTranslation();
	}
	FORCEINLINE FRotator Rotator() const
	{
		FQuat _rotation;
		return _rotation.GetRotator();
	}
	FORCEINLINE T GetDeterminant() const
	{
		//#todo - vectorized version of this
		FVector4 _outScale3D;
		return _outScale3D.X * _outScale3D.Y * _outScale3D.Z;
	}
	FORCEINLINE FQuat GetRotation() const
	{
		return Rotation;
	}
	FORCEINLINE TVector<T> GetTranslation() const
	{
		return Translation;
	}
	FORCEINLINE TVector<T> GetScale3D() const
	{
		return Scale3D;
	}

	//TODO A REGARDER
	FORCEINLINE TTransform<T> GetRelativeTransform(const TTransform<T>& _other) const
	{
		// A * B(-1) = VQS(B)(-1) (VQS (A))
	// 
	// Scale = S(A)/S(B)
	// Rotation = Q(B)(-1) * Q(A)
	// Translation = 1/S(B) *[Q(B)(-1)*(T(A)-T(B))*Q(B)]
	// where A = this, B = _other
		TTransform<T> Result;

		if (_other.Rotation.IsNormalized() == false)
		{
			return TTransform<T>::Identity;
		}

		if (HasNegativeScale(Scale3D) || HasNegativeScale(_other.Scale3D))
		{
			return TTransform<T>::Identity;

			//TODO J'ai pas capte sur Unreal pls aidez moi

			/*GetRelativeTransformUsingMatrixWithScale(&Result, this, &_other);*/
		}
		else
		{
			// Scale = S(A)/S(B)
			TVector<T> _vSafeScale3D = Scale3D/_other.Scale3D;

			TVector<T> _vScale3D = Scale3D*_vSafeScale3D;

			//_vQTranslation = (  ( T(A).X - T(B).X ),  ( T(A).Y - T(B).Y ), ( T(A).Z - T(B).Z), 0.f );
			TVector<T> _vQTranslation = ((Translation.X - _other.Translation.X), (Translation.Y - _other.Translation.Y), (Translation.Z - _other.Translation.Z), 0.f);

			//Translation = 1/S(B)
			TVector<T> VTranslation = 1/_other.Scale3D;

			// Rotation = Q(B)(-1) * Q(A)	
			FQuat VRotation = -_other.Rotation * Rotation;

			Result.Scale3D = _vScale3D;
			Result.Translation = VTranslation;
			Result.Rotation = VRotation;
		}

		return Result;
	}

public:
	FORCEINLINE void SetComponents(const FQuat&InRotation, const TVector<T>&InTranslation, const TVector<T>&InScale3D)
	{
		Rotation = &InRotation;
		Translation = &InTranslation;
		Scale3D = &InScale3D;
	}
	FORCEINLINE void SetIdentity()
	{
		Rotation = FQuat::Identity;
		Translation = TVector<T>::ZeroVector;
		Scale3D = TVector<T>((T)1, (T)1, (T)1);
	}
	FORCEINLINE void SetIdentityZeroScale()
	{
		Rotation = FQuat::Identity;
		Translation = TVector<T>::ZeroVector;
		Scale3D = TVector<T>(0,0,0);
	}
	FORCEINLINE void SetTranslation(const TVector<T>& _newTranslation)
	{
		Translation = &_newTranslation;
	}
	FORCEINLINE void SetRotation(const FQuat& _newRotation)
	{
		Rotation =&_newRotation;
	}
	FORCEINLINE void SetScale3D(const TVector<T>& _newScale3D)
	{
		Scale3D = &_newScale3D;
	}
	FORCEINLINE void SetLocation(const TVector<T>& _origin)
	{
		Translation = &_origin;
	}



public:

	FORCEINLINE FString ToString() const
	{
		FRotator _r(GetRotation().GetRotator());
		TVector<T> _tr(GetTranslation());
		TVector<T> _s(GetScale3D());

		FString Output = FString::Format("Rotation: Pitch: {} Yaw: {} Roll: {} \n", _r.Pitch, _r.Yaw, _r.Roll);
		Output += FString::Format("Translation: {} {} {} \n", _tr.X, _tr.Y, _tr.Z);
		Output += FString::Format("Scale3D: {} {} {} \n", _s.X, _s.Y, _s.Z);

		return Output;
	}

	FORCEINLINE void ScaleTranslation(const TVector<T>& _scale3D)
	{
		TVector<T> _vectorInScale3D = &_scale3D;
		Translation *= _vectorInScale3D;
	}
	FORCEINLINE void ScaleTranslation(const T& _scale)
	{
		ScaleTranslation(TVector<T>(_scale));
	}
	FORCEINLINE void RemoveScaling(T _tolerance = SMALL_NUMBER)
	{
		Scale3D = TVector<T>(1,1,1);
		NormalizeRotation();
	}




	FORCEINLINE TVector<T> TransformPosition(const TVector<T>& _v)
	{
		TVector<T> _vector = TransformVector(_v);

		const TVector<T> _translatedVec = _vector +  Translation;

		TVector<T> _result;
		&_result = _translatedVec;
		return _result;
	}
	FORCEINLINE FQuat TransformRotation(const FQuat& _q) const
	{
		return GetRotation() * _q;
	}
	FORCEINLINE TVector<T> TransformVector(const TVector<T>& _v)
	{
		const TVector<T> _inputVector = &_v;

		//RotatedVec = Q.Rotate(Scale*V.X, Scale*V.Y, Scale*V.Z, 0.f)
		const TVector<T> _scaledVec = Scale3D *_inputVector;
		TVector<T> _rotatedVec = Rotation.RotateVector(_scaledVec);

		TVector<T> _result;
		&_result = _rotatedVec;
		return _result;
	}
	FORCEINLINE void SetFromMatrix(const FMatrix& _matrix)
	{
		FMatrix _m = _matrix;

		TVector<T> _scale = _m.ExtractScaling();
		Scale3D = &_scale;

		if (_matrix.Determinant() < 0.f)
		{
			Scale3D = Scale3D, TVector<float>(-1.f,1.f,1.f);
			_m.SetAxis(0, -_m.GetScaledAxis(EAxis::X));
		}

		FQuat _rotation =FQuat(_m);
		Rotation = &_rotation;
		TVector<T> InTranslation = InMatrix.GetOrigin();
		Translation = &InTranslation;

		Rotation = VectorNormalizeQuaternion(Rotation);
	}
	FORCEINLINE TTransform<T> GetScaled(T _scale) const
	{
		TTransform<T> _a(*this);

		T _vScale = &_scale;
		_a.Scale3D = VectorMultiply(_a.Scale3D, _vScale);

		return _a;
	}
	FORCEINLINE TTransform<T> GetScaled(TVector<T> _scale) const
	{
		TTransform<T> _a(*this);

		TVector<T>_vScale = &_scale;
		_a.Scale3D *= _vScale;

		return _a;
	}
	FORCEINLINE TVector<T> GetScaledAxis(EAxis::Type InAxis) const
	{
		if (InAxis == EAxis::X)
		{
			return TransformVector(TVector<T>(1.f, 0.f, 0.f));
		}
		else if (InAxis == EAxis::Y)
		{
			return TransformVector(TVector<T>(0.f, 1.f, 0.f));
		}

		return TransformVector(TVector<T>(0.f, 0.f, 1.f));
	}
	FORCEINLINE void MultiplyScale3D(const TVector<T>& _scale3DMultiplier)
	{
		Scale3D *= &_scale3DMultiplier;
	}
	FORCEINLINE void CopyTranslation(const TTransform<T>& _other)
	{
		Translation = _other.Translation;
	}
	FORCEINLINE void AddToTranslation(const TVector<T>& _deltaTranslation)
	{
		Translation +=&_deltaTranslation;
		DiagnosticCheckNaN_Translate();
	}
	FORCEINLINE void CopyRotation(const TTransform<T>& _other)
	{
		Rotation = _other.Rotation;
	}
	FORCEINLINE void CopyScale3D(const TTransform<T>& _other)
	{
		Scale3D = _other.Scale3D;
	}
	FORCEINLINE void NormalizeRotation()
	{
		Rotation = Rotation.Normalize();
	}
	FORCEINLINE bool HasNegativeScale(TVector<T> _scale)
	{
		return _scale.X < 0 || _scale.Y < 0 || _scale.Z < 0;
	}


}; 
template<typename T>
TTransform<T> TTransform<T>::Identity = TTransform<T>();
