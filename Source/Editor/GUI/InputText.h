#pragma once
#include "../../CoreMinimal.h"
class InputText
{

public:
	static bool MakeInputField(const char& _constChar, size_t _size)
	{

		char* _char = const_cast<char*>(&_constChar);
		if (ImGui::InputText(" ", _char, _size))
			return true;
		return false;
	}
	static bool MakeInputField(const char& _constChar, size_t _size, const std::function<void(void)>& _callback)
	{

		char* _char = const_cast<char*>(&_constChar);
		if (ImGui::InputText(" ", _char, _size))
		{
			_callback();
			return true;
		}
		return false;
	}
	
};

