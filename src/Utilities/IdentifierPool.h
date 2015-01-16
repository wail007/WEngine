#ifndef W_IDENTIFIER_POOL
#define W_IDENTIFIER_POOL

#include <vector>

class IdentifierPool
{
public:
	IdentifierPool();

	void recycleId(unsigned int in_id);
	unsigned int getId();

private:
	std::vector<unsigned int> m_recycledIds;
	unsigned int m_nextId;
};

#endif