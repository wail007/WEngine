#ifndef W_OPENGL_VERTEX_LAYOUT_H
#define W_OPENGL_VERTEX_LAYOUT_H

#include "LibOpenGL.h"
#include "VertexLayout.h"
#include "OpenGLVertexBuffer.h"

class GPUVertexLayout
{
public:
	GPUVertexLayout(const VertexLayout& in_layout, const GPUVertexBuffer& in_vbo);
	~GPUVertexLayout();

	void enable()	const;
	void disable()	const;

private:
	GLuint m_handle;
};

#endif