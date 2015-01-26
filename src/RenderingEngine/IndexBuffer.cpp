#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(int in_nbIndices, int in_indexSize)
	:Buffer(in_nbIndices, in_indexSize), m_offset(0)
{

}


IndexBuffer::~IndexBuffer()
{

}


int	IndexBuffer::getOffset() const
{
	return m_offset;
}

void IndexBuffer::setOffset(int in_offset)
{
	m_offset = in_offset;
}