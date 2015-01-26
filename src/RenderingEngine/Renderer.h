#ifndef W_RENDERER_H
#define	W_RENDERER_H

#include "LibOpenGL.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexLayout.h"
#include "OpenGLShaderProgram.h"
#include "../Math/WMath.h"

typedef void(*SwapBufferFuncPtr)(void*);


struct WindowInfo
{
	int					width;
	int					height;
	void*				handle;
	SwapBufferFuncPtr	pSwapBufferFunc;
};



class Renderer
{
public:
	Renderer(WindowInfo in_winInfo);
	~Renderer();

	/////////////////////////////////////////////Manage Viewport//////////////////////////////////////////////////
	void setViewport(int in_xPos, int in_yPos, int in_width, int in_height);
	void getViewport(int& out_xPos, int& out_yPos, int& out_width, int& out_height) const;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	////////////////////////////////////////////Manage Buffers////////////////////////////////////////////////////
	void setClearColor(const WMath::Vector4f& in_color);
	void setClearDepth(float in_depth);

	WMath::Vector4f	getClearColor() const;
	float			getClearDepth() const;

	void clearColorBuffer();
	void clearDepthBuffer();
	void clearBuffers();

	void swapColorBuffer();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// The entry point to drawing the visible set of a scene graph.
	//void Draw(const VisibleSet& visibleSet, GlobalEffect* globalEffect = 0);
	//
	//// The entry points for drawing a single object.
	//void Draw(const Visual* visual);
	//void Draw(const Visual* visual, const VisualEffectInstance* instance);
private:
	WindowInfo m_winInfo;
};

#endif