#include "DynamicMemoryPool.h"

DynamicMemoryPool::DynamicMemoryPool()
	: m_chunkSize(1), m_nbChunks(5)
{
	m_table = new char[m_chunkSize * m_nbChunks];
}


DynamicMemoryPool::DynamicMemoryPool(unsigned int in_chunkSize)
	: m_chunkSize(in_chunkSize), m_nbChunks(5)
{
	m_table = new char[m_chunkSize * m_nbChunks];
}

DynamicMemoryPool::DynamicMemoryPool(unsigned int in_chunkSize, unsigned int in_poolSize)
	: m_chunkSize(in_chunkSize), m_nbChunks(in_poolSize)
{
	m_table = new char[m_chunkSize * m_nbChunks];
}

DynamicMemoryPool::DynamicMemoryPool(const DynamicMemoryPool& in_copy)
{
	m_chunkSize	= in_copy.m_chunkSize;
	m_nbChunks	= in_copy.m_nbChunks;

	unsigned int nbBytes = m_nbChunks * m_chunkSize;

	m_table = new char[nbBytes];

	for (unsigned int i = 0; i < nbBytes; i++)
	{
		m_table[i] = in_copy.m_table[i];
	}
}

DynamicMemoryPool::~DynamicMemoryPool()
{
	delete[] m_table;
}

DynamicMemoryPool& DynamicMemoryPool::operator = (const DynamicMemoryPool& in_copy)
{
	if (this != &in_copy)
	{
		m_chunkSize	= in_copy.m_chunkSize;
		m_nbChunks	= in_copy.m_nbChunks;

		delete[] m_table;

		int nbBytes = m_nbChunks * m_chunkSize;

		m_table = new char[nbBytes];

		for (int i = 0; i < nbBytes; i++)
		{
			m_table[i] = in_copy.m_table[i];
		}
	}

	return *this;
}

unsigned int DynamicMemoryPool::getChunkSize() const
{
	return m_chunkSize;
}

unsigned int DynamicMemoryPool::getNbChunks() const
{
	return m_nbChunks;
}


void DynamicMemoryPool::resize(unsigned int in_size)
{
	char* tmp = new char[m_chunkSize*in_size];

	unsigned int nbBytes = m_chunkSize * m_nbChunks;

	for (unsigned int i = 0; i < nbBytes; i++)
	{
		tmp[i] = m_table[i];
	}

	delete[] m_table;

	m_table = tmp;

	m_nbChunks = in_size;
}
