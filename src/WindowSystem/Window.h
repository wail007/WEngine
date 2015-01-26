#ifndef W_WINDOW_H
#define W_WINDOW_H

#include <SDL.h>
#include <string>

#undef main

class Window
{
public:
	static bool Init(std::string in_name, unsigned int in_width, unsigned int in_height);

	static void Release();

	static void swapBuffer();

private:
	static unsigned int s_width;
	static unsigned int s_height;
	 
	static SDL_Window*		s_winHandle;
	static SDL_GLContext	s_oglContextHandle;
};

#endif