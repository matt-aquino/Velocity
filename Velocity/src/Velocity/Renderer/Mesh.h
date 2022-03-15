#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include <memory>
#include <vector>

namespace Velocity
{
	class Mesh
	{
	public:
		Mesh() = default;

		Mesh(float* vertices, uint32_t numVerts, uint32_t* indices, uint32_t numIndices); // take in raw vertex data and generate the buffers
		Mesh(std::shared_ptr<VertexBuffer>& vertexBuffer, std::shared_ptr<IndexBuffer>& indexBuffer); // take in two buffers and generate the vertex array

		std::shared_ptr<VertexArray>& BindMesh();
		void UnbindMesh();
		~Mesh() = default;


	private:
		std::shared_ptr<VertexArray> m_VertexArray;

	};
}