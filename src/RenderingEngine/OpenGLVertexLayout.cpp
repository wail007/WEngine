#include "OpenGLVertexLayout.h"


GPUVertexLayout::GPUVertexLayout(const VertexLayout& in_layout, const GPUVertexBuffer& in_vbo)
{
	glGenVertexArrays(1, &m_handle);

	in_vbo.enable();
	{
		glBindVertexArray(m_handle);
		{
			for (int i = 0; i < VertexLayout::COUNT; i++)
			{
				if (in_layout.isSet((VertexLayout::AttribIndex)i))
				{
					glVertexAttribPointer	(	i, 
												in_layout.getnbComponents((VertexLayout::AttribIndex)i), 
												GL_FLOAT, 
												GL_FALSE, 
												0, 
												BUFFER_OFFSET(in_layout.getOffset((VertexLayout::AttribIndex)i))
											);

					glEnableVertexAttribArray(i);
				}
			}
		}
		glBindVertexArray(0);
	}
	in_vbo.disable();
	
}


GPUVertexLayout::~GPUVertexLayout()
{
	glDeleteVertexArrays(1, &m_handle);
}

void GPUVertexLayout::enable()	const
{
	glBindVertexArray(m_handle);
}


void GPUVertexLayout::disable()	const
{
	glBindVertexArray(0);
}