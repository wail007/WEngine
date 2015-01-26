#include "Buffer.h"

Buffer::Buffer()
	:m_data(0), m_elementSize(0), m_nbBytes(0), m_nbElements(0)
{

}


Buffer::Buffer(int in_nbElements, int in_elementSize)
	:m_elementSize(in_elementSize), m_nbElements(in_nbElements), m_nbBytes(in_nbElements*in_elementSize)
{
	m_data = new char[m_nbBytes];
}

Buffer::~Buffer()
{
	delete[] m_data;
}

int	Buffer::getNbElements() const
{
	return m_nbElements;
}


int	Buffer::getElementSize() const
{
	return m_elementSize;
}


int	Buffer::getNbBytes() const
{
	return m_nbBytes;
}


const char* Buffer::getData() const
{
	return m_data;
}


void Buffer::setNbElements(int in_nbElements)
{
	m_nbElements = in_nbElements;
}