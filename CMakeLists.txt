cmake_minimum_required(VERSION 3.19)
project(Quake)

find_package(OpenGL REQUIRED)

if( WIN32 )
	list ( APPEND CMAKE_PREFIX_PATH "C:\\Program Files(x86)\\ReactPhysics3D")
  	list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files\\ReactPhysics3D")

elseif ( APPLE )
	list ( APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/ReactPhysics3D ")
endif ()
find_package (ReactPhysics3D REQUIRED)

# Compile external dependencies 
add_subdirectory (external)



# Headers files
#set (REACTPHYSICS3D_HEADERS
#    "external/reactphysics3d/include/reactphysics3d/configuration.h"
#    "external/reactphysics3d/include/reactphysics3d/decimal.h"
#    "external/reactphysics3d/include/reactphysics3d/reactphysics3d.h"
#    "external/reactphysics3d/include/reactphysics3d/body/Body.h"
#    "external/reactphysics3d/include/reactphysics3d/body/RigidBody.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/ContactPointInfo.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/ContactManifoldInfo.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/ContactPair.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/broadphase/DynamicAABBTree.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/CollisionDispatch.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/VoronoiSimplex.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/GJK/GJKAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/SAT/SATAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsSphereAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsCapsuleAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInput.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/narrowphase/NarrowPhaseInfoBatch.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/AABB.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexPolyhedronShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/BoxShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/CapsuleShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/CollisionShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/ConvexMeshShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/SphereShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/TriangleShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/ConcaveMeshShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/shapes/HeightFieldShape.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/RaycastInfo.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/Collider.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/TriangleVertexArray.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/PolygonVertexArray.h"
#    "external/reactphysics3d/include/reactPhysics3D/collision/VertexArray.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/TriangleMesh.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/HeightField.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/ConvexMesh.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/HalfEdgeStructure.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/ContactManifold.h"
#    "external/reactphysics3d/include/reactphysics3d/constraint/BallAndSocketJoint.h"
#    "external/reactphysics3d/include/reactphysics3d/constraint/ContactPoint.h"
#    "external/reactphysics3d/include/reactphysics3d/constraint/FixedJoint.h"
#    "external/reactphysics3d/include/reactphysics3d/constraint/HingeJoint.h"
#    "external/reactphysics3d/include/reactphysics3d/constraint/Joint.h"
#    "external/reactphysics3d/include/reactphysics3d/constraint/SliderJoint.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/Entity.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/EntityManager.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/PhysicsCommon.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/ConstraintSolverSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/ContactSolverSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/DynamicsSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/CollisionDetectionSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/SolveBallAndSocketJointSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/SolveFixedJointSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/SolveHingeJointSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/SolveSliderJointSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/PhysicsWorld.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/EventListener.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/Island.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/Islands.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/Material.h"
#    "external/reactphysics3d/include/reactphysics3d/engine/OverlappingPairs.h"
#    "external/reactphysics3d/include/reactphysics3d/systems/BroadPhaseSystem.h"
#    "external/reactphysics3d/include/reactphysics3d/components/Components.h"
#    "external/reactphysics3d/include/reactphysics3d/components/BodyComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/RigidBodyComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/TransformComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/ColliderComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/JointComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/BallAndSocketJointComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/FixedJointComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/HingeJointComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/components/SliderJointComponents.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/CollisionCallback.h"
#    "external/reactphysics3d/include/reactphysics3d/collision/OverlapCallback.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/mathematics.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/mathematics_common.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/mathematics_functions.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/Matrix2x2.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/Matrix3x3.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/Quaternion.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/Transform.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/Vector2.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/Vector3.h"
#    "external/reactphysics3d/include/reactphysics3d/mathematics/Ray.h"
#    "external/reactphysics3d/include/reactphysics3d/memory/MemoryAllocator.h"
#    "external/reactphysics3d/include/reactphysics3d/memory/PoolAllocator.h"
#    "external/reactphysics3d/include/reactphysics3d/memory/SingleFrameAllocator.h"
#    "external/reactphysics3d/include/reactphysics3d/memory/HeapAllocator.h"
#    "external/reactphysics3d/include/reactphysics3d/memory/DefaultAllocator.h"
#    "external/reactphysics3d/include/reactphysics3d/memory/MemoryManager.h"
#    "external/reactphysics3d/include/reactphysics3d/containers/Stack.h"
#    "external/reactphysics3d/include/reactphysics3d/containers/LinkedList.h"
#    "external/reactphysics3d/include/reactphysics3d/containers/Array.h"
#    "external/reactphysics3d/include/reactphysics3d/containers/Map.h"
#    "external/reactphysics3d/include/reactphysics3d/containers/Set.h"
#    "external/reactphysics3d/include/reactphysics3d/containers/Pair.h"
#    "external/reactphysics3d/include/reactphysics3d/containers/Deque.h"
#    "external/reactphysics3d/include/reactphysics3d/utils/Profiler.h"
#    "external/reactphysics3d/include/reactphysics3d/utils/Logger.h"
#    "external/reactphysics3d/include/reactphysics3d/utils/Message.h"
#    "external/reactphysics3d/include/reactphysics3d/utils/DefaultLogger.h"
#    "external/reactphysics3d/include/reactphysics3d/utils/DebugRenderer.h"
#    "external/reactphysics3d/include/reactphysics3d/utils/quickhull/QuickHull.h"
#    "external/reactphysics3d/include/reactphysics3d/utils/quickhull/QHHalfEdgeStructure.h"
#)

# Source files
#set (REACTPHYSICS3D_SOURCES
#    "external/reactphysics3d/src/body/Body.cpp"
#    "external/reactphysics3d/src/body/RigidBody.cpp"
#    "external/reactphysics3d/src/collision/broadphase/DynamicAABBTree.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/CollisionDispatch.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/GJK/VoronoiSimplex.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/GJK/GJKAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/SAT/SATAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/SphereVsSphereAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/CapsuleVsCapsuleAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/SphereVsCapsuleAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/NarrowPhaseInput.cpp"
#    "external/reactphysics3d/src/collision/narrowphase/NarrowPhaseInfoBatch.cpp"
#    "external/reactphysics3d/src/collision/shapes/AABB.cpp"
#    "external/reactphysics3d/src/collision/shapes/ConvexShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/ConvexPolyhedronShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/ConcaveShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/BoxShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/CapsuleShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/CollisionShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/ConvexMeshShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/SphereShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/TriangleShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/ConcaveMeshShape.cpp"
#    "external/reactphysics3d/src/collision/shapes/HeightFieldShape.cpp"
#    "external/reactphysics3d/src/collision/RaycastInfo.cpp"
#    "external/reactphysics3d/src/collision/Collider.cpp"
#    "external/reactphysics3d/src/collision/TriangleVertexArray.cpp"
#    "external/reactphysics3d/src/collision/PolygonVertexArray.cpp"
#    "external/reactphysics3d/src/collision/VertexArray.cpp"
#    "external/reactphysics3d/src/collision/TriangleMesh.cpp"
#    "external/reactphysics3d/src/collision/HeightField.cpp"
#    "external/reactphysics3d/src/collision/ConvexMesh.cpp"
#    "external/reactphysics3d/src/collision/HalfEdgeStructure.cpp"
#    "external/reactphysics3d/src/collision/ContactManifold.cpp"
#    "external/reactphysics3d/src/constraint/BallAndSocketJoint.cpp"
#    "external/reactphysics3d/src/constraint/ContactPoint.cpp"
#    "external/reactphysics3d/src/constraint/FixedJoint.cpp"
#    "external/reactphysics3d/src/constraint/HingeJoint.cpp"
#    "external/reactphysics3d/src/constraint/Joint.cpp"
#    "external/reactphysics3d/src/constraint/SliderJoint.cpp"
#    "external/reactphysics3d/src/engine/PhysicsCommon.cpp"
#    "external/reactphysics3d/src/systems/ConstraintSolverSystem.cpp"
#    "external/reactphysics3d/src/systems/ContactSolverSystem.cpp"
#    "external/reactphysics3d/src/systems/DynamicsSystem.cpp"
#    "external/reactphysics3d/src/systems/CollisionDetectionSystem.cpp"
#    "external/reactphysics3d/src/systems/SolveBallAndSocketJointSystem.cpp"
#    "external/reactphysics3d/src/systems/SolveFixedJointSystem.cpp"
#    "external/reactphysics3d/src/systems/SolveHingeJointSystem.cpp"
#    "external/reactphysics3d/src/systems/SolveSliderJointSystem.cpp"
#    "external/reactphysics3d/src/engine/PhysicsWorld.cpp"
#    "external/reactphysics3d/src/engine/Island.cpp"
#    "external/reactphysics3d/src/engine/Material.cpp"
#    "external/reactphysics3d/src/engine/OverlappingPairs.cpp"
#    "external/reactphysics3d/src/engine/Entity.cpp"
#    "external/reactphysics3d/src/engine/EntityManager.cpp"
#    "external/reactphysics3d/src/systems/BroadPhaseSystem.cpp"
#    "external/reactphysics3d/src/components/Components.cpp"
#    "external/reactphysics3d/src/components/BodyComponents.cpp"
#    "external/reactphysics3d/src/components/RigidBodyComponents.cpp"
#    "external/reactphysics3d/src/components/TransformComponents.cpp"
#    "external/reactphysics3d/src/components/ColliderComponents.cpp"
#    "external/reactphysics3d/src/components/JointComponents.cpp"
#    "external/reactphysics3d/src/components/BallAndSocketJointComponents.cpp"
#    "external/reactphysics3d/src/components/FixedJointComponents.cpp"
#    "external/reactphysics3d/src/components/HingeJointComponents.cpp"
#    "external/reactphysics3d/src/components/SliderJointComponents.cpp"
#    "external/reactphysics3d/src/collision/CollisionCallback.cpp"
#    "external/reactphysics3d/src/collision/OverlapCallback.cpp"
#    "external/reactphysics3d/src/collision/VertexArray.cpp"
#    "external/reactphysics3d/src/mathematics/Matrix2x2.cpp"
#    "external/reactphysics3d/src/mathematics/Matrix3x3.cpp"
#    "external/reactphysics3d/src/mathematics/Quaternion.cpp"
#    "external/reactphysics3d/src/mathematics/Transform.cpp"
#    "external/reactphysics3d/src/mathematics/Vector2.cpp"
#    "external/reactphysics3d/src/mathematics/Vector3.cpp"
#    "external/reactphysics3d/src/memory/PoolAllocator.cpp"
#    "external/reactphysics3d/src/memory/SingleFrameAllocator.cpp"
#    "external/reactphysics3d/src/memory/HeapAllocator.cpp"
#    "external/reactphysics3d/src/memory/MemoryManager.cpp"
#    "external/reactphysics3d/src/memory/MemoryAllocator.cpp"
#    "external/reactphysics3d/src/utils/Profiler.cpp"
#    "external/reactphysics3d/src/utils/DefaultLogger.cpp"
#    "external/reactphysics3d/src/utils/DebugRenderer.cpp"
#    "external/reactphysics3d/src/utils/quickhull/QuickHull.cpp"
#    "external/reactphysics3d/src/utils/quickhull/QHHalfEdgeStructure.cpp"
#)

# Create the library
#add_library(reactphysics3d ${REACTPHYSICS3D_HEADERS} ${REACTPHYSICS3D_SOURCES})




# Library headers
#target_include_directories(reactphysics3d PUBLIC
#              $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#              $<INSTALL_INTERFACE:include>
#)


include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	#external/reactphysics3d/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
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
target_link_libraries (Quake ReactPhysics3D::ReactPhysics3D)

