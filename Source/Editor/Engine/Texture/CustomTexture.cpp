#include "CustomTexture.h"


CustomTexture::CustomTexture(const char* _path, const int _wrapParam, const int _filterParam)
{
	LoadTexture(_path, _wrapParam , _filterParam);
}

void CustomTexture::LoadTexture(const char* _path, const int _wrapParam, const int _filterParam)
{ 
	glGenTextures(1, &ID);
	unsigned char* _data  ;
	 _data = stbi_load(string("../Content/Textures/" + string(_path)).c_str(), &width, &height, &channelsCount, 0);
	if (_data)
	{
		GLenum _format = GLenum();
		if (channelsCount == 1)
			_format = GL_RED;
		else if (channelsCount == 3)
			_format = GL_RGB;
		else if (channelsCount == 4)
			_format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, _format, width, height, 0, _format, GL_UNSIGNED_BYTE, _data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterParam);
	}
	else
	{
		cout << "Texture failed to load at path: " << _path << endl;
	}

	stbi_image_free(_data);
}

void CustomTexture::BindTexture(const GLuint& _target )
{
	glActiveTexture(GL_TEXTURE0 + _target);
	glBindTexture(GL_TEXTURE_2D, ID);
}
