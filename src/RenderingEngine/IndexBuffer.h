#ifndef W_INDEX_BUFFER_H
#define W_INDEX_BUFFER_H

#include "Buffer.h"

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(int in_nbIndices, int in_indexSize);
	virtual ~IndexBuffer();

	int	getOffset() const;

	void setOffset(int in_offset);	

private:
	int m_offset;
};

#endif
