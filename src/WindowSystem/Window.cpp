#include "Window.h"


unsigned int	Window::s_width				= 0;
unsigned int	Window::s_height			= 0;
SDL_Window*		Window::s_winHandle			= 0;
SDL_GLContext	Window::s_oglContextHandle	= 0;


bool Window::Init(std::string in_name, unsigned int in_width, unsigned int in_height)
{
	SDL_Init(SDL_INIT_VIDEO);

	s_winHandle = SDL_CreateWindow(in_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, in_width, in_height, SDL_WINDOW_OPENGL);

	// set openGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	//create opengl context
	s_oglContextHandle = SDL_GL_CreateContext(s_winHandle);


	return true;
}

void Window::Release()
{
	SDL_GL_DeleteContext(s_oglContextHandle);
	SDL_DestroyWindow(s_winHandle);
	SDL_Quit();
}


void Window::swapBuffer()
{
	SDL_GL_SwapWindow(s_winHandle);
}


	