#pragma once

#include "VertexArray.h"
#include "Buffer.h"
namespace Velocity
{
	class Mesh
	{
	public:
		Mesh() = default;

		Mesh(float* vertices, uint32_t numVerts, uint32_t* indices, uint32_t numIndices); // take in raw vertex data and generate the buffers
		Mesh(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer); // take in two buffers and generate the vertex array

		Ref<VertexArray>& BindMesh();
		void UnbindMesh();
		~Mesh() = default;


	private:
		Ref<VertexArray> m_VertexArray;

	};
}