#include "OpenGLIndexBuffer.h"


GPUIndexBuffer::GPUIndexBuffer(char* in_buffer, unsigned int in_size)
{
	glGenBuffers(1, &m_handle);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, in_size, in_buffer, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


GPUIndexBuffer::GPUIndexBuffer(const IndexBuffer& in_buffer)
{
	glGenBuffers(1, &m_handle);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, in_buffer.getNbBytes(), in_buffer.getData(), GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GPUIndexBuffer::~GPUIndexBuffer()
{
	glDeleteBuffers(1, &m_handle);
}


void GPUIndexBuffer::enable() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void GPUIndexBuffer::disable() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}