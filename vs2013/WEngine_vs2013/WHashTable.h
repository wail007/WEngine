/*#ifndef W_HASH_TABLE_H
#define W_HASH_TABLE_H

template <typename T>
class WHashTable
{
public:
	WHashTable();
	WHashTable(unsigned int in_capacity);
	WHashTable(const WHashTable& in_copy);

	void insert(int in_key, T in_obj);
	void remove(int in_key);

	T* operator[](int in_key);

	void resize(unsigned int in_size);

private:

	struct Pair
	{
		int	key;
		T	value;
	};

	Pair* m_table;

	unsigned int m_size;
	unsigned int m_capacity;

	unsigned int m_startIndex;
};


template <typename T>
WHashTable<T>::WHashTable()
	:m_size(0), m_capacity(5), m_startIndex(0)
{
	m_table = new Pair[m_capacity];
}

template <typename T>
WHashTable<T>::WHashTable(unsigned int in_capacity)
	:m_size, m_capacity(in_capacity), m_startIndex(0)
{
	m_table = new Pair[m_capacity];
}

template <typename T>
WHashTable<T>::WHashTable(const WHashTable& in_copy)
{

}

template <typename T>
void WHashTable<T>::insert(int in_key, T in_obj)
{

}

template <typename T>
void WHashTable<T>::remove(int in_key)
{

}

template <typename T>
T* WHashTable<T>::operator[]((int in_key))
{

}

template <typename T>
void WHashTable<T>::resize(unsigned int in_size)
{

}

#endif
*/