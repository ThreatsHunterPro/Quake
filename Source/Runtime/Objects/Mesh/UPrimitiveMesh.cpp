#include "UPrimitiveMesh.h"



void UPrimitiveMesh::GetFloatArrayByType(const PrimitiveType& _type, TArray<float>& _vertices, TArray<float>& _indices)
{
	switch (_type)
	{
	case PT_BOX:
		GenerateBoxVertices(_vertices);
		break;
	case PT_SPHERE:
		GenerateSphereVerticesAndIndices(_vertices, _indices);
		break;
	case PT_PLANE:
		GenerateSphereVerticesAndIndices(_vertices, _indices);
		break;
	case PT_CYLINDER:
		GenerateSphereVerticesAndIndices(_vertices, _indices);
		break;
	case PT_CONE:
		GenerateSphereVerticesAndIndices(_vertices, _indices);
		break;
	default:
		break;
	}

}

void UPrimitiveMesh::GenerateBoxVertices(TArray<float>& _vertices)
{
	_vertices = {
		//position		 // normals		    // color	      // texture
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f ,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0
	};
}

void UPrimitiveMesh::GenerateSphereVerticesAndIndices(TArray<float>& _vertices, TArray<float>& _indices)
{
	TArray<float> _sphereVertices;
	TArray<unsigned int> _sphereIndices;

	float _sectorCount = 20;
	float stackCount = 20;
	float _radius = 1;
	float _sectorStep = 2 * pi<float>() / _sectorCount;
	float stackStep = pi<float>() / stackCount;

	for (int i = 0; i <= stackCount; ++i) {
		float stackAngle = pi<float>() / 2 - i * stackStep;
		float xy = _radius * cos(stackAngle);
		float z = _radius * sin(stackAngle);

		for (int j = 0; j <= _sectorCount; ++j) {
			float sectorAngle = j * _sectorStep;

			float x = xy * cos(sectorAngle);
			float y = xy * sin(sectorAngle);

			_vertices.Add(x);
			_vertices.Add(y);
			_vertices.Add(z);

			// Normales (pour la lumière)

			_vertices.Add(x / _radius);
			_vertices.Add(y / _radius);
			_vertices.Add(z / _radius);

			// Couleur (par exemple, blanc)
			_vertices.Add(1.0f);
			_vertices.Add(1.0f);
			_vertices.Add(1.0f);

			// Coordonnées de texture (non utilisées dans cet exemple)
			_vertices.Add(0.0f);
			_vertices.Add(0.0f);
		}
	}

	for (int i = 0; i < stackCount; ++i) {
		int k1 = i * (_sectorCount + 1);
		int k2 = k1 + _sectorCount + 1;

		for (int j = 0; j < _sectorCount; ++j, ++k1, ++k2) {
			// Triangle 1
			_sphereIndices.Add(k1);
			_sphereIndices.Add(k2);
			_sphereIndices.Add(k1 + 1);

			// Triangle 2
			_sphereIndices.Add(k2);
			_sphereIndices.Add(k2 + 1);
			_sphereIndices.Add(k1 + 1);
		}
	}

	// Convertir les indices en un tableau de float pour OpenGL
	for (unsigned int index : _sphereIndices) {
		for (int i = 0; i < 8; ++i) { // 8 car nous avons 8 valeurs par sommet
			_indices.Add(_sphereVertices[index * 8 + i]);
		}
	}
}


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
