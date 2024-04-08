cmake_minimum_required(VERSION 3.19)
project(Quake)

find_package(OpenGL REQUIRED)# Compile external dependencies 
add_subdirectory (external)


set(SFML_DIR "D:/code/Thomas/Quake/external/SFML-2.6.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "D:/code/Thomas/Quake/external/SFML-2.6.1/include")
set(SFML_INCLUDE_LIB "D:/code/Thomas/Quake/external/SFML-2.6.1/lib")

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS graphics window system audio network REQUIRED)


set(CMAKE_PREFIX_PATH "D:/code/Thomas/Quake/external/freetype-2.13.0")

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


set(ALL_LIBS
	${OPENGL_LIBRARY}
        #sfml-network
	glfw
	GLEW_1130
        sfml-graphics
        sfml-window 
        sfml-system	
	sfml-audio
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