cmake_minimum_required(VERSION 3.19)

project(Quake)

set(SFML_DIR "external/SFML-2.6.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "external/SFML-2.6.0/include")
set(SFML_INCLUDE_LIB "external/SFML-2.6.0/lib")

set(SFML_STATIC_LIBRARIES TRUE)

#load packages
list(APPEND CMAKE_PREFIX_PATH "Engine\\Libraries\\ReactPhysics3D")
find_package(ReactPhysics3D REQUIRED)
find_package(OpenGL REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "Engine\\Libraries\\imgui")
find_package(imgui REQUIRED)

set(CMAKE_PREFIX_PATH "external/freetype-2.13.0")
find_package(SFML COMPONENTS graphics window system audio network REQUIRED)


set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
    	sfml-graphics
    	sfml-window 
    	sfml-system
	sfml-audio
	sfml-network
	ReactPhysics3D::ReactPhysics3D
	imgui::imgui
)


# Compile external dependencies 
add_subdirectory (external)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/SFML-2.6.1/include/
	external/SFML-2.6.1/lib/
	.
)


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


# Récupération des fichiers .cpp dans les sous-dossiers de Source
file(GLOB_RECURSE SOURCES "Source/*.cpp")
# Récupération des fichiers .h dans les sous-dossiers de Source
file(GLOB_RECURSE HEADERS "Source/*.h")
# Récupération des fichiers .hpp dans les sous-dossiers de Source
file(GLOB_RECURSE HPP "Source/*.hpp")

# Ajout des sources à l'exécutable
add_executable(Quake ${SOURCES} ${HEADERS} ${HPP})

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .cpp
file(GLOB_RECURSE SRC_LIST "Source/*.cpp")
foreach(_source IN ITEMS ${SRC_LIST})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .h
file(GLOB_RECURSE HEADER_LIST "Source/*.h")
foreach(_header IN ITEMS ${HEADER_LIST})
    get_filename_component(_header_path "${_header}" PATH)
    file(RELATIVE_PATH _header_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${_header_path}")
    string(REPLACE "/" "\\" _group_path "${_header_path_rel}")
    source_group("${_group_path}" FILES "${_header}")
endforeach()

# Parcourir récursivement les sous-dossiers de Source pour les fichiers .h
file(GLOB_RECURSE HPP_LIST "Source/*.hpp")
foreach(_hpp IN ITEMS ${HPP_LIST})
    get_filename_component(_hpp_path "${_hpp}" PATH)
    file(RELATIVE_PATH _hpp_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/Source" "${_hpp_path}")
    string(REPLACE "/" "\\" _group_path "${_hpp_path_rel}")
    source_group("${_group_path}" FILES "${_hpp}")
endforeach()

#Includes
include_directories(Engine/Includes)

#Librairies
link_directories(Engine/Libraries)
target_link_libraries(Quake ${ALL_LIBS})


