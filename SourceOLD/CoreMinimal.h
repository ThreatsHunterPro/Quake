#pragma once
#include <iostream>
#include <functional>

#include "Runtime/Core/Containers/FString.h"
#include "Runtime/Core/Containers/TArray.h"
#include "Editor/Pointers/TWeakPtr.h"
#include "Editor/GarbageCollector/GarbageCollector.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common/shader.hpp"

// OBJECTS MACRO.H
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define FORCEINLINE __forceinline

using namespace std;
using namespace glm;

//template <typename T>
//TObjectPtr<T> NewObject()
//{
//}

//template <typename T>
//void DestroyObject(T* _pointeur)
//{
//	T* _object = new T();
//	const bool _exists = GarbageCollector::GetInstance().Register(_object);
//	return _exists ? TWeakPtr<T>(_object) : TSharedPtr<T>(_object);
//}