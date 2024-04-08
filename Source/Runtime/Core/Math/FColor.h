#pragma once
#include "..\Containers\FString.h"
#include "..\..\..\CoreMinimal.h"

struct FColor
{
	union Color
	{
		struct
		{
			int R;
			int G;
			int B;
			int A;
		} RGB;

		struct
		{
			int H;
			int S;
			int L;
			int A;
		} HSL;

		struct
		{
			int C;
			int M;
			int Y;
			int K;
		} CMYK;
	} color;
	

public:
	FColor();
	FColor( int _r, int _g, int _b,int _a);
	FColor(const FVector& _vector);
	FColor(const FColor& _other);

public:
	static FColor FromHex(const FString& _string);
	static FColor MakeRandomColor();
	FString ToHex() const;
	FString ToString() const;

private:
	FString FromDecToHex(int _value) const;
	int FromHexToDec(const FString& _string) const;

public:
	bool operator != (const FColor& _color)
	{
		return !operator==(_color);
	}
	bool operator == (const FColor& _color)
	{
		return ToHex() == _color.ToHex();
	}
	void operator += (const FColor& _color)
	{
		color.RGB.A = (color.RGB.A + _color.color.RGB.A < 0) ? 0 : (color.RGB.A += _color.color.RGB.A > 255) ? 255 : color.RGB.A + _color.color.RGB.A;
		color.RGB.R = (color.RGB.R + _color.color.RGB.R < 0) ? 0 : (color.RGB.R += _color.color.RGB.R > 255) ? 255 : color.RGB.R + _color.color.RGB.R;
		color.RGB.G = (color.RGB.G + _color.color.RGB.G < 0) ? 0 : (color.RGB.G += _color.color.RGB.G > 255) ? 255 : color.RGB.G + _color.color.RGB.G;
		color.RGB.B = (color.RGB.B + _color.color.RGB.B < 0) ? 0 : (color.RGB.B += _color.color.RGB.B > 255) ? 255 : color.RGB.B + _color.color.RGB.B;
	}
};

const FColor Black = { 0, 0, 0, 255 };
const FColor Blue = {0,0, 255, 255};
const FColor Cyan = {0, 255, 255, 255};
const FColor Emerald = {0, 170, 70, 255};
const FColor Green = {0, 255, 0, 255};
const FColor Magenta = {255, 0, 255, 255};
const FColor Orange = {255, 100, 0, 255};
const FColor Purple = {180, 0, 255, 255};
const FColor Red = {255, 0, 0, 255};
const FColor Silver = {220, 220, 220, 255};
const FColor Transparent = {0, 0, 0, 0};
const FColor Turquoise = {50, 140, 170, 255};
const FColor White = {255, 255, 255, 255};
const FColor Yellow = {255, 255, 0, 255};