#include "FMatrix.h"
#include "FVector/TVector.h"

FMatrix FMatrix::Identity = FMatrix(FVector(1,0,0),FVector(0,1,0),FVector(0,0,1), FVector(0, 0, 0));

FMatrix::FMatrix()
{
   *this = FMatrix::Identity;
}

FMatrix::FMatrix(const FVector& _inX, const FVector& _inY, const FVector& _inZ, const FVector& _inW)
{
    M[0][0] = _inX.X; M[0][1] = _inX.Y;  M[0][2] = _inX.Z;  M[0][3] = 0.0f;
    M[1][0] = _inY.X; M[1][1] = _inY.Y;  M[1][2] = _inY.Z;  M[1][3] = 0.0f;
    M[2][0] = _inZ.X; M[2][1] = _inZ.Y;  M[2][2] = _inZ.Z;  M[2][3] = 0.0f;
    M[3][0] = _inW.X; M[3][1] = _inW.Y;  M[3][2] = _inW.Z;  M[3][3] = 1.0f;
}

FMatrix::FMatrix(const FVector4& _inX, const FVector4& _inY, const FVector4& _inZ, const FVector4& _inW)
{
    M[0][0] = _inX.X; M[0][1] = _inX.Y;  M[0][2] = _inX.Z;  M[0][3] = _inX.W;
    M[1][0] = _inY.X; M[1][1] = _inY.Y;  M[1][2] = _inY.Z;  M[1][3] = _inY.W;
    M[2][0] = _inZ.X; M[2][1] = _inZ.Y;  M[2][2] = _inZ.Z;  M[2][3] = _inZ.W;
    M[3][0] = _inW.X; M[3][1] = _inW.Y;  M[3][2] = _inW.Z;  M[3][3] = _inW.W;
}

FMatrix::FMatrix(const mat3& _matrix3)
{
    M[0][0] = _matrix3[0][0]; M[0][1] = _matrix3[0][1];  M[0][2] = _matrix3[0][2];  M[0][3] = 0.f;
    M[1][0] = _matrix3[1][0]; M[1][1] = _matrix3[1][1];  M[1][2] = _matrix3[1][2];  M[1][3] = 0.f;
    M[2][0] = _matrix3[2][0]; M[2][1] = _matrix3[2][1];  M[2][2] = _matrix3[2][2];  M[2][3] = 0.f;
    M[3][0] = 0.f; M[3][1] = 0.f;  M[3][2] = 0.f;  M[3][3] = 1.f;
}

void FMatrix::SetIdentity()
{
    M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
    M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
    M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
    M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;
}

bool FMatrix::Equals(const FMatrix& _other, float _tolerance) const
{
    for (int _x = 0; _x < 4; _x++)
    {
        for (int _y = 0; _y < 4; _y++)
        {
            if (FMath::Abs(M[_x][_y] - _other.M[_x][_y]) > _tolerance)
            {
                return false;
            }
        }
    }

    return true;
}

FMatrix FMatrix::GetTransposed() const
{
    FMatrix	_result = FMatrix::Identity;

    _result.M[0][0] = M[0][0];
    _result.M[0][1] = M[1][0];
    _result.M[0][2] = M[2][0];
    _result.M[0][3] = M[3][0];

    _result.M[1][0] = M[0][1];
    _result.M[1][1] = M[1][1];
    _result.M[1][2] = M[2][1];
    _result.M[1][3] = M[3][1];

    _result.M[2][0] = M[0][2];
    _result.M[2][1] = M[1][2];
    _result.M[2][2] = M[2][2];
    _result.M[2][3] = M[3][2];

    _result.M[3][0] = M[0][3];
    _result.M[3][1] = M[1][3];
    _result.M[3][2] = M[2][3];
    _result.M[3][3] = M[3][3];

    return _result;
}

float FMatrix::Determinant() const
{
    return	M[0][0] * (
        M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
        M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
        M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
        ) -
        M[1][0] * (
            M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
            M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
            M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
            ) +
        M[2][0] * (
            M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
            M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
            M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
            ) -
        M[3][0] * (
            M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
            M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
            M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
            );
}

float FMatrix::RotDeterminant() const
{
    return
        M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
        M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
        M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
}

FMatrix FMatrix::TransposeAdjoint() const
{
    FMatrix _matrix = FMatrix::Identity;

    _matrix.M[0][0] = M[1][1] * M[2][2] - M[1][2] * M[2][1];
    _matrix.M[0][1] = M[1][2] * M[2][0] - M[1][0] * M[2][2];
    _matrix.M[0][2] = M[1][0] * M[2][1] - M[1][1] * M[2][0];
    _matrix.M[0][3] = 0.f;

    _matrix.M[1][0] = M[2][1] * M[0][2] - M[2][2] * M[0][1];
    _matrix.M[1][1] = M[2][2] * M[0][0] - M[2][0] * M[0][2];
    _matrix.M[1][2] = M[2][0] * M[0][1] - M[2][1] * M[0][0];
    _matrix.M[1][3] = 0.f;

    _matrix.M[2][0] = M[0][1] * M[1][2] - M[0][2] * M[1][1];
    _matrix.M[2][1] = M[0][2] * M[1][0] - M[0][0] * M[1][2];
    _matrix.M[2][2] = M[0][0] * M[1][1] - M[0][1] * M[1][0];
    _matrix.M[2][3] = 0.f;

    _matrix.M[3][0] = 0.f;
    _matrix.M[3][1] = 0.f;
    _matrix.M[3][2] = 0.f;
    _matrix.M[3][3] = 1.f;

    return _matrix;
}

void FMatrix::RemoveScaling(float _tolerance)
{
    const float _squareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
    const float _squareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
    const float _squareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);
    const float _scale0 = FMath::FloatSelect(_squareSum0 - _tolerance, FMath::InvSqrt(_squareSum0), float(1));
    const float _scale1 = FMath::FloatSelect(_squareSum1 - _tolerance, FMath::InvSqrt(_squareSum1), float(1));
    const float _scale2 = FMath::FloatSelect(_squareSum2 - _tolerance, FMath::InvSqrt(_squareSum2), float(1));
    M[0][0] *= _scale0;
    M[0][1] *= _scale0;
    M[0][2] *= _scale0;
    M[1][0] *= _scale1;
    M[1][1] *= _scale1;
    M[1][2] *= _scale1;
    M[2][0] *= _scale2;
    M[2][1] *= _scale2;
    M[2][2] *= _scale2;
}

FMatrix FMatrix::GetMatrixWithoutScale(float _tolerance) const
{
    FMatrix _result = (FMatrix&) * this;
    _result.RemoveScaling(_tolerance);
    return _result;
}

FVector FMatrix::ExtractScaling(float _tolerance)
{
    FVector _scale3D(0);

    // For each row, find magnitude, and if its non-zero re-scale so its unit length.
    const float _squareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
    const float _squareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
    const float _squareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

    if (_squareSum0 > _tolerance)
    {
        float _scale0 = FMath::Sqrt(_squareSum0);
        _scale3D.X = _scale0;
        float _invScale0 = 1.f / _scale0;
        M[0][0] *= _invScale0;
        M[0][1] *= _invScale0;
        M[0][2] *= _invScale0;
    }
    else
    {
        _scale3D.X = 0;
    }

    if (_squareSum1 > _tolerance)
    {
        float _scale1 = FMath::Sqrt(_squareSum1);
        _scale3D.Y = _scale1;
        float _invScale1 = 1.f / _scale1;
        M[1][0] *= _invScale1;
        M[1][1] *= _invScale1;
        M[1][2] *= _invScale1;
    }
    else
    {
        _scale3D.Y = 0;
    }

    if (_squareSum2 > _tolerance)
    {
        float _scale2 = FMath::Sqrt(_squareSum2);
        _scale3D.Z = _scale2;
        float _invScale2 = 1.f / _scale2;
        M[2][0] *= _invScale2;
        M[2][1] *= _invScale2;
        M[2][2] *= _invScale2;
    }
    else
    {
        _scale3D.Z = 0;
    }

    return _scale3D;
}

FVector FMatrix::GetScaleVector(float _tolerance)
{
    FVector _scale3D(1);

    // For each row, find magnitude, and if its non-zero re-scale so its unit length.
    for (int i = 0; i < 3; i++)
    {
        const float _squareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
        if (_squareSum > _tolerance)
        {
            _scale3D[i] = FMath::Sqrt(_squareSum);
        }
        else
        {
            _scale3D[i] = 0.f;
        }
    }

    return _scale3D;
}

FMatrix FMatrix::RemoveTranslation() const
{
    FMatrix _result = (FMatrix&) * this;
    _result.M[3][0] = 0.0f;
    _result.M[3][1] = 0.0f;
    _result.M[3][2] = 0.0f;
    return _result;
}

FMatrix FMatrix::ConcatTranslation(const FVector& Translation) const
{
    FMatrix _result = FMatrix::Identity;

    float* _dest = &_result.M[0][0];
    const float* _src = &M[0][0];
    const float* _trans = &Translation.X;

    _dest[0] = _src[0];
    _dest[1] = _src[1];
    _dest[2] = _src[2];
    _dest[3] = _src[3];
    _dest[4] = _src[4];
    _dest[5] = _src[5];
    _dest[6] = _src[6];
    _dest[7] = _src[7];
    _dest[8] = _src[8];
    _dest[9] = _src[9];
    _dest[10] = _src[10];
    _dest[11] = _src[11];
    _dest[12] = _src[12] + _trans[0];
    _dest[13] = _src[13] + _trans[1];
    _dest[14] = _src[14] + _trans[2];
    _dest[15] = _src[15];

    return _result;
}

float FMatrix::GetMinimumAxisScale() const
{
    const float _maxRowScaleSquared = FMath::Min(
        GetScaledAxis(EAxis::X).SquaredLength(),
        FMath::Min(
            GetScaledAxis(EAxis::Y).SquaredLength(),
            GetScaledAxis(EAxis::Z).SquaredLength()
        )
    );
    return FMath::Sqrt(_maxRowScaleSquared);
}

float FMatrix::GetMaximumAxisScale() const
{
    const float _maxRowScaleSquared = FMath::Max(
        GetScaledAxis(EAxis::X).SquaredLength(),
        FMath::Max(
            GetScaledAxis(EAxis::Y).SquaredLength(),
            GetScaledAxis(EAxis::Z).SquaredLength()
        )
    );
    return FMath::Sqrt(_maxRowScaleSquared);
}

void FMatrix::ScaleTranslation(const FVector& _inScale3D)
{
    M[3][0] *= _inScale3D.X;
    M[3][1] *= _inScale3D.Y;
    M[3][2] *= _inScale3D.Z;
}

FVector FMatrix::GetOrigin() const
{
    return FVector(M[3][0], M[3][1], M[3][2]);
}
FVector FMatrix::GetScaledAxis(EAxis::Type _inAxis) const
{
    switch (_inAxis)
    {
    case EAxis::X:
        return FVector(M[0][0], M[0][1], M[0][2]);

    case EAxis::Y:
        return FVector(M[1][0], M[1][1], M[1][2]);

    case EAxis::Z:
        return FVector(M[2][0], M[2][1], M[2][2]);

    default:
        return FVector::ZeroVector;
    }
}

void FMatrix::GetScaledAxes(FVector& _x, FVector& _y, FVector& _z) const
{
    _x.X = M[0][0]; _x.Y = M[0][1]; _x.Z = M[0][2];
    _y.X = M[1][0]; _y.Y = M[1][1]; _y.Z = M[1][2];
    _z.X = M[2][0]; _z.Y = M[2][1]; _z.Z = M[2][2];
}

FVector FMatrix::GetUnitAxis(EAxis::Type InAxis) const
{
    return GetScaledAxis(InAxis).GetSafeNormal();
}

void FMatrix::GetUnitAxes(FVector& _x, FVector& _y, FVector& _z) const
{
    GetScaledAxes(_x, _y, _z);
    _x.Normalize();
    _y.Normalize();
    _z.Normalize();
}

void FMatrix::SetAxis(int i, const FVector& _axis)
{
    if (i >= 0 && i <= 3)
    {
        M[i][0] = _axis.X;
        M[i][1] = _axis.Y;
        M[i][2] = _axis.Z;
    }
}

void FMatrix::SetOrigin(const FVector& NewOrigin)
{
    M[3][0] = NewOrigin.X;
    M[3][1] = NewOrigin.Y;
    M[3][2] = NewOrigin.Z;
}

void FMatrix::SetAxes(const FVector* _axis0, const FVector* _axis1, const FVector* _axis2, const FVector* _origin)
{
    if (_axis0 != NULL)
    {
        M[0][0] = _axis0->X;
        M[0][1] = _axis0->Y;
        M[0][2] = _axis0->Z;
    }
    if (_axis1 != NULL)
    {
        M[1][0] = _axis1->X;
        M[1][1] = _axis1->Y;
        M[1][2] = _axis1->Z;
    }
    if (_axis2 != NULL)
    {
        M[2][0] = _axis2->X;
        M[2][1] = _axis2->Y;
        M[2][2] = _axis2->Z;
    }
    if (_origin != NULL)
    {
        M[3][0] = _origin->X;
        M[3][1] = _origin->Y;
        M[3][2] = _origin->Z;
    }
}

FVector FMatrix::GetColumn(int _index) const
{
        return FVector(M[0][_index], M[1][_index], M[2][_index]);
}

void FMatrix::SetColumn(int _index, FVector _value)
{
    if (_index >= 0 && _index <= 3)
    {
        M[0][_index] = _value.X;
        M[1][_index] = _value.Y;
        M[2][_index] = _value.Z;
    }
}

void FMatrix::Mirror(EAxis::Type _mirrorAxis, EAxis::Type _flipAxis)
{
    if (_mirrorAxis == EAxis::X)
    {
        M[0][0] *= -1.f;
        M[1][0] *= -1.f;
        M[2][0] *= -1.f;

        M[3][0] *= -1.f;
    }
    else if (_mirrorAxis == EAxis::Y)
    {
        M[0][1] *= -1.f;
        M[1][1] *= -1.f;
        M[2][1] *= -1.f;

        M[3][1] *= -1.f;
    }
    else if (_mirrorAxis == EAxis::Z)
    {
        M[0][2] *= -1.f;
        M[1][2] *= -1.f;
        M[2][2] *= -1.f;

        M[3][2] *= -1.f;
    }

    if (_flipAxis == EAxis::X)
    {
        M[0][0] *= -1.f;
        M[0][1] *= -1.f;
        M[0][2] *= -1.f;
    }
    else if (_flipAxis == EAxis::Y)
    {
        M[1][0] *= -1.f;
        M[1][1] *= -1.f;
        M[1][2] *= -1.f;
    }
    else if (_flipAxis == EAxis::Z)
    {
        M[2][0] *= -1.f;
        M[2][1] *= -1.f;
        M[2][2] *= -1.f;
    }
}

FMatrix FMatrix::ApplyScale(float _scale) const
{
    FMatrix _scaleMatrix(
        FVector4(_scale, 0.0f, 0.0f, 0.0f),
        FVector4(0.0f, _scale, 0.0f, 0.0f),
        FVector4(0.0f, 0.0f, _scale, 0.0f),
        FVector4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    return _scaleMatrix * ((FMatrix&) * this);
}

FString FMatrix::ToString() const
{
    FString _output;
    _output.Append(FString::Format("[{} {} {} {}] \n", M[0][0], M[0][1], M[0][2], M[0][3]));
    _output.Append(FString::Format("[{} {} {} {}] \n", M[1][0], M[1][1], M[1][2], M[1][3]));
    _output.Append(FString::Format("[{} {} {} {}] \n", M[2][0], M[2][1], M[2][2], M[2][3]));
    _output.Append(FString::Format("[{} {} {} {}] \n", M[3][0], M[3][1], M[3][2], M[3][3]));
    return _output;
}

mat4 FMatrix::ToMat4()
{
    return mat4
    (
        M[0][0], M[0][1], M[0][2], M[0][3],
        M[1][0], M[1][1], M[1][2], M[1][3],
        M[2][0], M[2][1], M[2][2], M[2][3],
        M[3][0], M[3][1], M[3][2], M[3][3]
    );
}


const mat4 FMatrix::ToMat4()const 
{
    return mat4
    (
        M[0][0], M[0][1], M[0][2], M[0][3],
        M[1][0], M[1][1], M[1][2], M[1][3],
        M[2][0], M[2][1], M[2][2], M[2][3],
        M[3][0], M[3][1], M[3][2], M[3][3]
    );
}

void FMatrix::operator*=(const FMatrix& _other)
{
    VectorMatrixMultiply(this, this, &_other);
}

void FMatrix::operator*=(const mat4& _other)
{
    VectorMatrixMultiply(this, this, &_other);
}

FMatrix FMatrix::operator*(const FMatrix& _other) 
{
    FMatrix _result = FMatrix::Identity;
    VectorMatrixMultiply(&_result, this, &_other);
    return _result;
}

FMatrix FMatrix::operator*(const mat4& _other)
{
    FMatrix _result = FMatrix::Identity;
    VectorMatrixMultiply(&_result, this, &_other);
    return _result;
}

FMatrix FMatrix::operator+(const FMatrix& _other) const
{
    FMatrix _resultMat = FMatrix::Identity;

    for (int X = 0; X < 4; X++)
    {
        _resultMat.M[X][0] = M[X][0] + _other.M[X][0];
        _resultMat.M[X][1] = M[X][1] + _other.M[X][1];
        _resultMat.M[X][2] = M[X][2] + _other.M[X][2];
        _resultMat.M[X][3] = M[X][3] + _other.M[X][3];
    }
    return _resultMat;
}

FMatrix FMatrix::operator+(const mat4& _other) const
{
    FMatrix _resultMat = FMatrix::Identity;

    for (int X = 0; X < 4; X++)
    {
        _resultMat.M[X][0] = M[X][0] + _other[X][0];
        _resultMat.M[X][1] = M[X][1] + _other[X][1];
        _resultMat.M[X][2] = M[X][2] + _other[X][2];
        _resultMat.M[X][3] = M[X][3] + _other[X][3];
    }
    return _resultMat;
}

void FMatrix::operator+=(const FMatrix& _other)
{
    *this = *this + _other;
}

void FMatrix::operator+=(const mat4& _other)
{
    *this = *this + _other;
}

FMatrix FMatrix::operator*(float _other) const
{
    FMatrix _resultMat = FMatrix::Identity;

    for (int X = 0; X < 4; X++)
    {
        _resultMat.M[X][0] = M[X][0] * _other;
        _resultMat.M[X][1] = M[X][1] * _other;
        _resultMat.M[X][2] = M[X][2] * _other;
        _resultMat.M[X][3] = M[X][3] * _other;
    }
    return _resultMat;
}

void FMatrix::operator*=(float _other)
{
    *this = *this * _other;
}

bool FMatrix::operator==(const FMatrix& _other) const
{
    for (int X = 0; X < 4; X++)
    {
        for (int Y = 0; Y < 4; Y++)
        {
            if (M[X][Y] != _other.M[X][Y])
            {
                return false;
            }
        }
    }

    return true;
}

bool FMatrix::operator==(const mat4& _other) const
{
    for (int X = 0; X < 4; X++)
    {
        for (int Y = 0; Y < 4; Y++)
        {
            if (M[X][Y] != _other[X][Y])
            {
                return false;
            }
        }
    }

    return true;
}

bool FMatrix::operator!=(const FMatrix& _other) const
{
    return !(*this == _other);
}

bool FMatrix::operator!=(const mat4& _other) const
{
    return !(*this == _other);
}

FMatrix FMatrix::operator=(const FMatrix& _other)
{
    for (int X = 0; X < 4; X++)
    {
        M[X][0] = _other.M[X][0];
        M[X][1] = _other.M[X][1];
        M[X][2] = _other.M[X][2];
        M[X][3] = _other.M[X][3];
    }
    return *this;
}

FMatrix FMatrix::operator=(const mat4& _other)
{
    for (int X = 0; X < 4; X++)
    {
        M[X][0] = _other[X][0];
        M[X][1] = _other[X][1];
        M[X][2] = _other[X][2];
        M[X][3] = _other[X][3];
    }
    return *this;
}

void FMatrix::VectorMatrixMultiply(FMatrix* _result, const FMatrix* _matrix1, const FMatrix* _matrix2)
{
    typedef float Float4x4[4][4];
    const Float4x4& _a = *((const Float4x4*)_matrix1);
    const Float4x4& _b = *((const Float4x4*)_matrix2);
    Float4x4 _temp;
    _temp[0][0] = _a[0][0] * _b[0][0] + _a[0][1] * _b[1][0] + _a[0][2] * _b[2][0] + _a[0][3] * _b[3][0];
    _temp[0][1] = _a[0][0] * _b[0][1] + _a[0][1] * _b[1][1] + _a[0][2] * _b[2][1] + _a[0][3] * _b[3][1];
    _temp[0][2] = _a[0][0] * _b[0][2] + _a[0][1] * _b[1][2] + _a[0][2] * _b[2][2] + _a[0][3] * _b[3][2];
    _temp[0][3] = _a[0][0] * _b[0][3] + _a[0][1] * _b[1][3] + _a[0][2] * _b[2][3] + _a[0][3] * _b[3][3];

    _temp[1][0] = _a[1][0] * _b[0][0] + _a[1][1] * _b[1][0] + _a[1][2] * _b[2][0] + _a[1][3] * _b[3][0];
    _temp[1][1] = _a[1][0] * _b[0][1] + _a[1][1] * _b[1][1] + _a[1][2] * _b[2][1] + _a[1][3] * _b[3][1];
    _temp[1][2] = _a[1][0] * _b[0][2] + _a[1][1] * _b[1][2] + _a[1][2] * _b[2][2] + _a[1][3] * _b[3][2];
    _temp[1][3] = _a[1][0] * _b[0][3] + _a[1][1] * _b[1][3] + _a[1][2] * _b[2][3] + _a[1][3] * _b[3][3];

    _temp[2][0] = _a[2][0] * _b[0][0] + _a[2][1] * _b[1][0] + _a[2][2] * _b[2][0] + _a[2][3] * _b[3][0];
    _temp[2][1] = _a[2][0] * _b[0][1] + _a[2][1] * _b[1][1] + _a[2][2] * _b[2][1] + _a[2][3] * _b[3][1];
    _temp[2][2] = _a[2][0] * _b[0][2] + _a[2][1] * _b[1][2] + _a[2][2] * _b[2][2] + _a[2][3] * _b[3][2];
    _temp[2][3] = _a[2][0] * _b[0][3] + _a[2][1] * _b[1][3] + _a[2][2] * _b[2][3] + _a[2][3] * _b[3][3];

    _temp[3][0] = _a[3][0] * _b[0][0] + _a[3][1] * _b[1][0] + _a[3][2] * _b[2][0] + _a[3][3] * _b[3][0];
    _temp[3][1] = _a[3][0] * _b[0][1] + _a[3][1] * _b[1][1] + _a[3][2] * _b[2][1] + _a[3][3] * _b[3][1];
    _temp[3][2] = _a[3][0] * _b[0][2] + _a[3][1] * _b[1][2] + _a[3][2] * _b[2][2] + _a[3][3] * _b[3][2];
    _temp[3][3] = _a[3][0] * _b[0][3] + _a[3][1] * _b[1][3] + _a[3][2] * _b[2][3] + _a[3][3] * _b[3][3];
    memcpy(_result, &_temp, 16 * sizeof(float));
}

void FMatrix::VectorMatrixMultiply(FMatrix* _result, const FMatrix* _matrix1, const mat4* _matrix2)
{
    typedef float Float4x4[4][4];
    const Float4x4& _a = *((const Float4x4*)_matrix1);
    const Float4x4& _b = *((const Float4x4*)_matrix2);
    Float4x4 _temp;
    _temp[0][0] = _a[0][0] * _b[0][0] + _a[0][1] * _b[1][0] + _a[0][2] * _b[2][0] + _a[0][3] * _b[3][0];
    _temp[0][1] = _a[0][0] * _b[0][1] + _a[0][1] * _b[1][1] + _a[0][2] * _b[2][1] + _a[0][3] * _b[3][1];
    _temp[0][2] = _a[0][0] * _b[0][2] + _a[0][1] * _b[1][2] + _a[0][2] * _b[2][2] + _a[0][3] * _b[3][2];
    _temp[0][3] = _a[0][0] * _b[0][3] + _a[0][1] * _b[1][3] + _a[0][2] * _b[2][3] + _a[0][3] * _b[3][3];

    _temp[1][0] = _a[1][0] * _b[0][0] + _a[1][1] * _b[1][0] + _a[1][2] * _b[2][0] + _a[1][3] * _b[3][0];
    _temp[1][1] = _a[1][0] * _b[0][1] + _a[1][1] * _b[1][1] + _a[1][2] * _b[2][1] + _a[1][3] * _b[3][1];
    _temp[1][2] = _a[1][0] * _b[0][2] + _a[1][1] * _b[1][2] + _a[1][2] * _b[2][2] + _a[1][3] * _b[3][2];
    _temp[1][3] = _a[1][0] * _b[0][3] + _a[1][1] * _b[1][3] + _a[1][2] * _b[2][3] + _a[1][3] * _b[3][3];

    _temp[2][0] = _a[2][0] * _b[0][0] + _a[2][1] * _b[1][0] + _a[2][2] * _b[2][0] + _a[2][3] * _b[3][0];
    _temp[2][1] = _a[2][0] * _b[0][1] + _a[2][1] * _b[1][1] + _a[2][2] * _b[2][1] + _a[2][3] * _b[3][1];
    _temp[2][2] = _a[2][0] * _b[0][2] + _a[2][1] * _b[1][2] + _a[2][2] * _b[2][2] + _a[2][3] * _b[3][2];
    _temp[2][3] = _a[2][0] * _b[0][3] + _a[2][1] * _b[1][3] + _a[2][2] * _b[2][3] + _a[2][3] * _b[3][3];

    _temp[3][0] = _a[3][0] * _b[0][0] + _a[3][1] * _b[1][0] + _a[3][2] * _b[2][0] + _a[3][3] * _b[3][0];
    _temp[3][1] = _a[3][0] * _b[0][1] + _a[3][1] * _b[1][1] + _a[3][2] * _b[2][1] + _a[3][3] * _b[3][1];
    _temp[3][2] = _a[3][0] * _b[0][2] + _a[3][1] * _b[1][2] + _a[3][2] * _b[2][2] + _a[3][3] * _b[3][2];
    _temp[3][3] = _a[3][0] * _b[0][3] + _a[3][1] * _b[1][3] + _a[3][2] * _b[2][3] + _a[3][3] * _b[3][3];
    memcpy(_result, &_temp, 16 * sizeof(float));
}
