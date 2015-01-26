#ifndef W_OPENGL_INDEX_BUFFER_H
#define W_OPENGL_INDEX_BUFFER_H

#include "LibOpenGL.h"
#include "IndexBuffer.h"


class Renderer;

class GPUIndexBuffer
{
public:
	GPUIndexBuffer(char* in_buffer, unsigned int in_size);
	GPUIndexBuffer(const IndexBuffer& in_buffer);
	~GPUIndexBuffer();

	
	void enable()	const;
	void disable()	const;

private:
	GLuint m_handle;
};



#endif
