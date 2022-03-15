#include "vlpch.h"
#include "Mesh.h"

namespace Velocity
{
	Mesh::Mesh(float* vertices, uint32_t numVerts, uint32_t* indices, uint32_t numIndices)
	{
		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		Ref<VertexBuffer> vertexBuffer;
		Ref<IndexBuffer> indexBuffer;

		vertexBuffer.reset(VertexBuffer::Create(vertices, numVerts * sizeof(float)));
		
		// add default layout
		BufferLayout layout = {
			{ShaderDataType::Float3, "aPos", false}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(IndexBuffer::Create(indices, numIndices * sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_VertexArray->Unbind();
	}


	Mesh::Mesh(Ref<VertexBuffer>& vertexBuffer, Ref<IndexBuffer>& indexBuffer)
	{
		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		// vertex buffer has no layout, so assign default
		if (!vertexBuffer->HasLayout())
		{
			// add default layout
			BufferLayout layout = {
				{ShaderDataType::Float3, "aPos", false}
			};

			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_VertexArray->Unbind();
	}

	Ref<VertexArray>& Mesh::BindMesh()
	{
		m_VertexArray->Bind();
		return m_VertexArray;
	}
	
	void Mesh::UnbindMesh()
	{
		m_VertexArray->Unbind();
	}
}