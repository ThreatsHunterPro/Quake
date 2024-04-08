#include "UPrimitiveMesh.h"

const float* UPrimitiveMesh::GetFloatArrayByType(const PrimitiveType& _type)
{
	//const float** _box = {
	//	// position		 // normals		    // color	      // texture
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f ,
	//	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0
	//};


	const float* _arrays = {};

	return _arrays;
}

//const float UPrimitiveMesh::GenerateBoxVertexesFloat()
//{
//	const float _result[] = {
//		 position		 // normals		    // color	      // texture
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f ,
//		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//
//		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
//		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//
//		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//
//		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//
//		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0
//	};
//
//	return _result;
//}
//
//const float* UPrimitiveMesh::GenerateSphereVertexesFloat()
//{
//	int _numStacks = 20;
//	int _numSlices = 20;
//	float _radius = 1;
//	float _stackStep = pi<float>() / _numStacks;
//	float _sliceStep = (2.0f * pi<float>()) / _numSlices;
//	float* _result;
//	int vertexIndex = 0;
//
//	// Generate vertices for the sphere
//	for (int i = 0; i <= _numStacks; ++i) {
//		float stackAngle = i * _stackStep;
//		float y = _radius * cos(stackAngle);
//		float sinStack = sin(stackAngle);
//
//		for (int j = 0; j <= _numSlices; ++j) {
//			float sliceAngle = j * _sliceStep;
//			float x = _radius * cos(sliceAngle) * sinStack;
//			float z = _radius * sin(sliceAngle) * sinStack;
//
//			// Position
//			_result[vertexIndex++] = x;
//			_result[vertexIndex++] = y;
//			_result[vertexIndex++] = z;
//
//			// Normal (same as position for a unit sphere)
//			_result[vertexIndex++] = x / _radius;
//			_result[vertexIndex++] = y / _radius;
//			_result[vertexIndex++] = z / _radius;
//
//			// Color (for demonstration)
//			_result[vertexIndex++] = 0.0f;   // Red
//			_result[vertexIndex++] = 0.0f;   // Green
//			_result[vertexIndex++] = 1.0f;   // Blue
//
//			// Texture coordinates (s, t)
//			_result[vertexIndex++] = (float)j / _numSlices;
//			_result[vertexIndex++] = (float)i / _numStacks;
//		}
//	}
//	const float _result[10] = {};
//	return _result;
//}
//
//const float* UPrimitiveMesh::GeneratePlaneVertexesFloat()
//{
//	const float _result[] = {
//		    position        // normals			   // color    // textures
//			0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//		};
//	return _result;
//}
//
//const float* UPrimitiveMesh::GenerateCylinderVertexesFloat()
//{
//	int _numSegments = 20;
//	float _radius = 1;
//	float _height = 1;
//	float _segmentAngle = pi<float>() * 2 / _numSegments;
//	float _numVertices = _numSegments * 6; // Chaque Segment a 2 triangle, donc 3 * 2 vertexs
//	const float* _result = new float* [_numVertices];
//	int _index = 0;
//
//	for (int i = 0; i < _numSegments; ++i) {
//		float _angle = i * _segmentAngle;
//		float _nextAngle = (i + 1) * _segmentAngle;
//
//		// Bottom vertex of the current Segment
//
//		_result[_index] = new float [11] {_radius* cos(_angle), 0.0f, _radius* sin(_angle), //position 
//			cos(_angle), 0.0f, sin(_angle),					 //normals
//			1.0, 0,										     // color
//			(float)i / _numSegments, 0};						 // textures
//
//		_result[_index + 1] = new float [11] {_radius* cos(_angle), 0.0f, _radius* sin(_angle),
//			cos(_nextAngle), 0.0f, sin(_nextAngle),
//			1.0, 0, 0,
//			((float)i + 1) / _numSegments, 0};
//
//		// Top vertices of the current segment
//		_result[_index + 2] = new float [11] {_radius* cos(_angle), _height, _radius* sin(_angle),
//			cos(_angle), 0.0f, sin(_angle),
//			0, 1.0, 0,
//			(float)i / _numSegments, 0};
//
//		_result[_index + 3] = new float [11] {_radius* cos(_angle), _height, _radius* sin(_angle),
//			cos(_nextAngle), 0.0f, sin(_nextAngle),
//			0, 1.0, 0,
//			((float)i + 1) / _numSegments, 0};
//
//		// side triangles for the current segment
//		_result[_index + 4] = _result[_index];      // x
//		_result[_index + 5] = _result[_index + 2];   // y (top of the cylinder)
//	 
//	}
//
//	return new float();
//}
//
//const float* UPrimitiveMesh::GenerateConeVertexesFloat()
//{
//	int _numSegments = 20;
//	float _radius = 1;
//	float _height = 1;
//	int _numVertices = _numSegments * 3;
//	const float* _result = new float* [_numVertices];
//	float _segmentAngle = 2 * pi<float>() / _numSegments;
//
//	int _index = 0;
//
//	// Generate vertices for the base of the cone
//	float _coneBase = 0;
//	for (int i = 0; i < _numSegments; ++i)
//	{
//		float angle = i * _segmentAngle;
//		float _x = _radius * cos(angle);
//		float _z = _radius * sin(angle);
//
//		_result[_index] = new float[11] {
//			_x, _coneBase, _z,                            // Position
//				0.0f, -1.0f, 0.0f,							// Normal (straight downward)
//				1.0f, 0.0f, 0.0f,							 // Color (red)
//				(_x + _radius) / (2.0f * _radius), 0.0f    // Texture coordinates (s, t)
//			};
//	_index++;
//	}
//
//	// Generate vertices for the tip of the cone
//	float tipY = _height;
//	_result[_index] = new float[11] {0.0f, tipY, 0.0f,   // Position (tip)
//		0.0f, 1.0f, 0.0f,    // Normal (straight upward)
//		0.0f, 1.0f, 0.0f,    // Color (green)
//		0.5f, 1.0f};         // Texture coordinates (s, t)
//	_index++;
//
//	// Generate vertices for the side of the cone
//	for (int i = 0; i < _numSegments; ++i) {
//		float _angle = i * _segmentAngle;
//		float _angle1 = (i + 1) * _segmentAngle;
//		float _x = _radius * cos(_angle);
//		float _z = _radius * sin(_angle);
//		float _x1 = _radius * cos(_angle1);
//		float _z1 = _radius * sin(_angle1);
//
//		// Base vertex of the current segment
//		_result[_index] = new float[11] {
//			_x, _coneBase, _z,                          // Position
//				cos(_angle), 0.0f, sin(_angle),         // Normal
//				1.0f, 0.0f, 0.0f,                       // Color (red)
//				(float)i / _numSegments, 0.0f  };         // Texture coordinates (s, t)
//		_index++;
//
//		// Tip vertex
//		_result[_index] = new float[11] {
//			0.0f, tipY, 0.0f,                       // Position
//				cos(_angle), 0.0f, sin(_angle),         // Normal
//				0.0f, 1.0f, 0.0f,                       // Color (green)
//				(float)i / _numSegments, 1.0f};        // Texture coordinates (s, t)
//		_index++;
//
//		// Base vertex of the next segment
//		_result[_index] = new float[11] {
//			_x1, _coneBase, _z1,                          // Position
//				cos(_angle1), 0.0f, sin(_angle1),         // Normal
//				1.0f, 0.0f, 0.0f,                       // Color (red)
//				(float)(i + 1) / _numSegments, 0.0f};     // Texture coordinates (s, t)
//		_index++;
//	}
//	return new float();
//}
