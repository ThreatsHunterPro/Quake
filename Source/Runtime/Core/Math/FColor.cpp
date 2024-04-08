#include "FColor.h"
#include <random>
#include "FVector/TVector.h"

FColor::FColor()
{
	color.RGB = { 0,0,0,0 };
	color.CMYK = { 0,0,0,0 };
	color.HSL = { 0,0,0,0 };
}

FColor::FColor( int _r, int _g, int _b, int _a)
{
	color.RGB = { _r, _g, _b, _a };
	color.HSL = { _r, _g, _b, _a };
	color.CMYK = { _r, _g, _b, _a };
}

FColor::FColor(const FVector& _vector)
{
	color.RGB = { 0,0,0,0};
	color.HSL = { 0,0,0,0};
	color.CMYK = { 0,0,0,0};
	//A = 255
	//R = _vector.x;
	//G = _vector.y;
	//B = _vector.z;
}

FColor::FColor(const FColor& _other)
{
	color = _other.color;
}

FColor FColor::FromHex(const FString& _string)
{
	FColor _tempColor;
	FString _temp = _string;

	if (_string.Length() != 8)
		return _tempColor;

	FString _rString;
	_rString += _temp[0];
	_rString += _temp[1];
	_tempColor.color.RGB.R = _tempColor.FromHexToDec(FString(_rString));

	FString _gString;
	_gString += _temp[2];
	_gString += _temp[3];
	_tempColor.color.RGB.G = _tempColor.FromHexToDec(FString(_gString));

	FString _bString;
	_bString += _temp[4];
	_bString += _temp[5];
	_tempColor.color.RGB.B = _tempColor.FromHexToDec(FString(_bString));

	FString _aString;
	_aString += _temp[6];
	_aString += _temp[7];
	_tempColor.color.RGB.A = _tempColor.FromHexToDec(FString(_aString));


	return _tempColor;
}

FColor FColor::MakeRandomColor()
{
	FColor _tempColor;
	_tempColor.color.RGB.A = 255;

	_tempColor.color.RGB.R = rand() % 256;
	_tempColor.color.RGB.G = rand() % 256;
	_tempColor.color.RGB.B = rand() % 256;

	return _tempColor;
}

FString FColor::ToHex() const
{
	FString _hexString = "";

	_hexString += FromDecToHex(color.RGB.R);
	_hexString += FromDecToHex(color.RGB.G);
	_hexString += FromDecToHex(color.RGB.B);
	_hexString += FromDecToHex(color.RGB.A);

	return _hexString;
}

FString FColor::ToString() const
{
	return FString::Format("{} - {} - {} - {}", color.RGB.R, color.RGB.R, color.RGB.B, color.RGB.A);
}

FString FColor::FromDecToHex(int _value) const
{
	int _dR = _value / 16;
	int _uR = _value % 16;
	char _cdR = _dR <= 9 ? (char)(48 + _dR) : (char)(55 + _dR);
	char _cuR = _uR <= 9 ? (char)(48 + _uR) : (char)(55 + _uR);

	string _s = string({ _cdR, _cuR });
	FString _string = FString(_s.c_str());
	return _string; 
}

int FColor::FromHexToDec(const FString& _string) const
{
	FString _temp = _string;
	int _dr = (_temp[0] < 65) ? (_temp[0] - 48) * 16 : (_temp[0] - 55) * 16;
	int _uR = (_temp[1] < 65) ? (_temp[1] - 48) : (_temp[1] - 55);
	
	return _dr + _uR;
}