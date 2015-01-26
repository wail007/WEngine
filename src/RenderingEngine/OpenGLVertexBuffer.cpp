#include "OpenGLVertexBuffer.h"

GPUVertexBuffer::GPUVertexBuffer(char* in_buffer, unsigned int in_size)
{
	glGenBuffers(1, &m_handle);

	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	{
		glBufferData(GL_ARRAY_BUFFER, in_size, in_buffer, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GPUVertexBuffer::GPUVertexBuffer(const VertexBuffer& in_buffer)
{
	glGenBuffers(1, &m_handle);

	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	{
		glBufferData(GL_ARRAY_BUFFER, in_buffer.getNbBytes(), in_buffer.getData(), GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


GPUVertexBuffer::~GPUVertexBuffer()
{
	glDeleteBuffers(1, &m_handle);
}


void GPUVertexBuffer::enable() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}


void GPUVertexBuffer::disable() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}