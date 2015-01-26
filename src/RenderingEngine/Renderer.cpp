#include "Renderer.h"


Renderer::Renderer(WindowInfo in_winInfo)
	:m_winInfo(in_winInfo)
{
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << "GLEW initialisation error: " << glewGetErrorString(err) << std::endl;
	}

	std::cout << glewGetString(GLEW_VERSION) << std::endl;

	glViewport(0, 0, in_winInfo.width, in_winInfo.height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glDisable(GL_CULL_FACE);
}


Renderer::~Renderer()
{

}


void Renderer::setViewport(int in_xPos, int in_yPos, int in_width, int in_height)
{
	glViewport(in_xPos, in_yPos, in_width, in_height);
}


void Renderer::getViewport(int& out_xPos, int& out_yPos, int& out_width, int& out_height) const
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	out_xPos	= viewport[0];
	out_yPos	= viewport[1];
	out_width	= viewport[2];
	out_height	= viewport[3];
}


void Renderer::setClearColor(const WMath::Vector4f& in_color)
{
	glClearColor(in_color.x(), in_color.y(), in_color.z(), in_color.w());
}


void Renderer::setClearDepth(float in_depth)
{
	glClearDepth(in_depth);
}

WMath::Vector4f	Renderer::getClearColor() const
{
	WMath::Vector4f v;
	glGetFloatv(GL_COLOR_CLEAR_VALUE, v);

	return v;
}


float Renderer::getClearDepth() const
{
	float f;
	glGetFloatv(GL_DEPTH_CLEAR_VALUE, &f);

	return f;
}

void Renderer::clearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::clearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}


void Renderer::clearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::swapColorBuffer()
{
	(*m_winInfo.pSwapBufferFunc)(m_winInfo.handle);
}