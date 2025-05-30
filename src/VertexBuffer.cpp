#include "VertexBuffer.h"
#include "Renderer.h"
#include <windows.h>

VertexBuffer::VertexBuffer() 
	: m_RendererID(0) {}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::SetDataSize(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Reset()
{
	if (m_RendererID)
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
		m_RendererID = 0;
	}
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
