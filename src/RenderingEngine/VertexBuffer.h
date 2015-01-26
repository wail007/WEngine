#ifndef W_VERTEX_BUFFER_H
#define W_VERTEX_BUFFER_H

#include "Buffer.h"

class VertexBuffer : public Buffer
{
public:
	// Construction and destruction.

	VertexBuffer(){}

	VertexBuffer(int in_nbVertices, int in_vertexSize)
		:Buffer(in_nbVertices*in_vertexSize, in_vertexSize)
	{

	}

	virtual ~VertexBuffer()
	{

	}
};


#endif
