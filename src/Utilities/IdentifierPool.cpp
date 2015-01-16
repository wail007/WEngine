#include "IdentifierPool.h"

IdentifierPool::IdentifierPool()
	:m_recycledIds(5), m_nextId(0)
{

}

void IdentifierPool::recycleId(unsigned int in_id)
{
	m_recycledIds.push_back(in_id);
}

unsigned int IdentifierPool::getId()
{
	if (!m_recycledIds.empty())
	{
		unsigned int id = m_recycledIds[m_recycledIds.size() - 1];
		m_recycledIds.pop_back();
		return id;
	}

	return m_nextId++;
}