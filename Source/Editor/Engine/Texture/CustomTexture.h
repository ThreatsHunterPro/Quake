#pragma once 
#include "../../../CoreMinimal.h"

class CustomTexture
{
	GLuint ID = -1;

	 int  width, height, channelsCount = -1;
public:

	FORCEINLINE GLuint GetTextureID() const { return ID; }

public:
	CustomTexture() = default;
	/// <summary>
	/// Directly loads the texture
	/// </summary>
	/// <param name="_path"></param>
	CustomTexture(const char* _path, const int _wrapParam, const int _filterParam);
	/// <summary>
	/// loads the texture with the correct channels
	/// </summary>
	/// <param name="_path">the texture path in Content/Textures</param>
	void LoadTexture(const char* _path, const int _wrapParam, const int _filterParam);
	/// <summary>
	/// Makes the texture active and binds it to the target
	/// </summary>
	/// <param name="_channel">the target to bind the texture to</param>
	void BindTexture(const GLuint& _target  );
};