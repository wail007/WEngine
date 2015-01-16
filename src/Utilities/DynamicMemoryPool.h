#ifndef W_DYNAMIC_MEMORY_POOL_H
#define W_DYNAMIC_MEMORY_POOL_H


class DynamicMemoryPool
{
public:
	DynamicMemoryPool();
	DynamicMemoryPool(unsigned int in_chunkSize);
	DynamicMemoryPool(unsigned int in_chunkSize, unsigned int in_poolSize);
	DynamicMemoryPool(const DynamicMemoryPool& in_copy);
	~DynamicMemoryPool();

	DynamicMemoryPool& operator=(const DynamicMemoryPool& in_copy);

	template <typename T>
	T* get(unsigned int in_index);

	unsigned int getChunkSize() const;
	unsigned int getNbChunks() const;

	void resize(unsigned int in_size);

private:
	char*			m_table;
	unsigned int	m_nbChunks;
	unsigned int	m_chunkSize;
};

template <typename T>
T* DynamicMemoryPool::get(unsigned int in_index)
{
	if (in_index >= m_nbChunks)
		resize(m_nbChunks + in_index);

	return (T*)(m_table + (m_chunkSize * in_index));
}

#endif