#ifndef W_OPENGL_VERTEX_BUFFER_H
#define W_OPENGL_VERTEX_BUFFER_H

#include "LibOpenGL.h"
#include "VertexBuffer.h"

class Renderer;

class GPUVertexBuffer
{
public:
	GPUVertexBuffer(char* in_buffer, unsigned int in_size);
	GPUVertexBuffer(const VertexBuffer& in_buffer);
	~GPUVertexBuffer();

	void enable()	const;
	void disable()	const;

private:
	GLuint m_handle;
};



#endif
