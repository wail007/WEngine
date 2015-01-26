#define _CRT_SECURE_NO_WARNINGS
#include "../RenderingEngine/Renderer.h"
#include "../RenderingEngine/Teapot.h"
#include "Window.h"
#include <cstdio>


float v[] = { 0, 0, 0.5 };

int main()
{
	Window::Init("", 300, 300);

	WindowInfo w;
	w.height = w.width = 300;
	w.pSwapBufferFunc = (SwapBufferFuncPtr)SDL_GL_SwapWindow;

	Renderer r(w);

	GPUVertexBuffer vbo((char*)teapotVertex, sizeof(teapotVertex));
	GPUIndexBuffer ibo((char*)teapotIndex, sizeof(teapotIndex));

	VertexLayout vlayout;
	vlayout.setAttribute(VertexLayout::POSITION, 0, 3);

	GPUVertexLayout vao(vlayout, vbo);


	glPointSize(5);

	FILE* f = fopen("E:/Documents/WEngine/src/RenderingEngine/vert.glsl", "r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *string = (char*)malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);
	string[fsize] = '\0';
	ShaderObject vert(string, ShaderType::VERTEX_SHADER);
	vert.compile();
	free(string);

	f = fopen("E:/Documents/WEngine/src/RenderingEngine/frag.glsl", "r");
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	string = (char*)malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);
	string[fsize] = '\0';
	ShaderObject frag(string, ShaderType::FRAGMENT_SHADER);
	frag.compile();
	free(string);

	ShaderProgram p;
	p.linkProgram(vert, frag);
	p.enable();
	


	
	vao.enable();
	ibo.enable();


	while (1)
	{
		r.clearBuffers();

		p.setMatrix4("mvp", WMath::translate(WMath::Vector3f(0,0, 3)));

		glDrawElements(GL_TRIANGLES, sizeof(teapotIndex)/sizeof(int), GL_UNSIGNED_INT, 0);
		


		Window::swapBuffer();
	}
	

	return 0;
}