#pragma once 

template<typename T> struct TVector;
template<typename T> struct TTransform;

using FVector3d = TVector<double>;
using FVector3i = TVector<int>;
using FVector = TVector<float>;

using FTransformd = TVector<double>;
using FTransformi = TVector<int>;
using FTransform = TVector<float>;
