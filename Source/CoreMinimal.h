#pragma once
#include <iostream>
#include <functional>

#include "Runtime/Core/Containers/FString.h"
#include "Runtime/Core/Containers/TArray.h"
#include "Editor/Pointers/TWeakPtr.h"
#include "Editor/GarbageCollector/GarbageCollector.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common/shader.hpp"
#include "Source/Runtime/Core/Math/MathFwd.h"

// PATH
#define VERTEX_SHADER_PATH "StandardShading.vertexshader"
#define FRAGMENT_SHADER_PATH "StandardShading.fragmentshader"

// OBJECTS MACRO.H
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define BASE __super
#define FORCEINLINE __forceinline

using namespace std;
using namespace glm;
