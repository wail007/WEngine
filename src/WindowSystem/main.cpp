#include "../RenderingEngine/Renderer.h"
#include "Window.h"

#define FPS					60
#define WINDOW_WIDTH		600
#define WINDOW_HEIGHT		300


///////////////////////////////cube definition////////////////////////////////////////////////////////////
GLuint		cubeVBOid;
GLuint		cubeVAOid;


float		cubeVertex[] = { 4, 4, -4, 4, -4, -4, -4, -4, -4,	     // Face 1
-4, -4, -4, -4, 4, -4, 4, 4, -4,     // Face 1

4, -4, 4, 4, -4, -4, 4, 4, -4,       // Face 2
4, 4, -4, 4, 4, 4, 4, -4, 4,         // Face 2

4, -4, -4, 4, -4, 4, -4, -4, 4,      // Face 3
-4, -4, 4, -4, -4, -4, 4, -4, -4,    // Face 3

-4, -4, 4, 4, -4, 4, 4, 4, 4,        // Face 4
4, 4, 4, -4, 4, 4, -4, -4, 4,      // Face 4

-4, -4, -4, -4, -4, 4, -4, 4, 4,     // Face 5
-4, 4, 4, -4, 4, -4, -4, -4, -4,   // Face 5

-4, 4, 4, 4, 4, 4, 4, 4, -4,         // Face 6
-4, 4, -4, -4, 4, 4, 4, 4, -4 };      // Face 6

float		cubeNormals[] = { 0, 0, -1, 0, 0, -1, 0, 0, -1,
0, 0, -1, 0, 0, -1, 0, 0, -1,

1, 0, 0, 1, 0, 0, 1, 0, 0,
1, 0, 0, 1, 0, 0, 1, 0, 0,

0, -1, 0, 0, -1, 0, 0, -1, 0,
0, -1, 0, 0, -1, 0, 0, -1, 0,

0, 0, 1, 0, 0, 1, 0, 0, 1,
0, 0, 1, 0, 0, 1, 0, 0, 1,

-1, 0, 0, -1, 0, 0, -1, 0, 0,
-1, 0, 0, -1, 0, 0, -1, 0, 0,

0, 1, 0, 0, 1, 0, 0, 1, 0,
0, 1, 0, 0, 1, 0, 0, 1, 0 };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////




//globlal variables
SDL_Window*		window;
SDL_GLContext	openglContext;


WMath::Matrix4f view(WMath::lookAt(WMath::Vector3f(30, 60, 30), WMath::Vector3f(-30, -60, -30), WMath::Vector3f(0, 1, 0)));

ShaderObject vert("E:/Documents/WEngine/src/RenderingEngine/vert.glsl", ShaderType::VERTEX_SHADER);
ShaderObject frag("E:/Documents/WEngine/src/RenderingEngine/frag.glsl", ShaderType::FRAGMENT_SHADER);

ShaderProgram program;

WMath::Matrix4f proj;


int main(int argc, char** argv)
{
	//initialise sdl
	SDL_Init(SDL_INIT_VIDEO);

	//create sdl window
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

	// set openGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	//create opengl context
	openglContext = SDL_GL_CreateContext(window);

	//initialise glew
	glewExperimental = GL_TRUE;
	GLenum initGLEW(glewInit());

	std::cout << glewGetString(GLEW_VERSION) << std::endl;

	vert.compile();
	frag.compile();
	program.linkProgram(vert, frag);

	//define matrices
	proj = WMath::perspective(70.0f, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 1.0f, 1000.0f);


	//////////////////////////////////load cube///////////////////////////////////////

	// generate an id for our VBO
	glGenBuffers(1, &cubeVBOid);

	// lock VBO so we can work on it
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOid);

	// reserve video memory in GPU for our VBO
	glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float) * 2, 0, GL_STATIC_DRAW);

	// transfer data to GPU
	glBufferSubData(GL_ARRAY_BUFFER, 0, 108 * sizeof(float), cubeVertex);
	glBufferSubData(GL_ARRAY_BUFFER, 108 * sizeof(float), 108 * sizeof(float), cubeNormals);

	// unlock VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// generate an id for our VAO
	glGenVertexArrays(1, &cubeVAOid);

	// lock VAO
	glBindVertexArray(cubeVAOid);

	// lock du VBO
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOid);

	// get vertex from VRAM
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)0 + 108 * sizeof(float));
	glEnableVertexAttribArray(1);

	// unlock VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unlock du VAO
	glBindVertexArray(0);
	//////////////////////////////////////////////////////////////////////////////////////////////////


	//main loop
	for (;;)
	{
	

		///////////////////////////////////////////rendering//////////////////////////////////////////////////////////////////////////////////
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		////////////////////////render cube/////////////////////////////
		//send matrices to shader
		lightShader.sendMatrix4("ModelViewMatrix", view*localModel);
		lightShader.sendMatrix4("MVP", proj*view*localModel);
		lightShader.sendMatrix3("NormalMatrix", mat3(transpose(inverse(view*localModel))));

		lightShader.sendVector3("Material.Ka", cubeColor * 0.5f);
		lightShader.sendVector3("Material.Kd", cubeColor);
		lightShader.sendVector3("color", cubeColor);

		// lock VAO
		glBindVertexArray(cubeVAOid);

		// render cube
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// unlock VAO
		glBindVertexArray(0);
		////////////////////////////////////////////////////////////////


		glUseProgram(0);

		SDL_GL_SwapWindow(window);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}


	//free memory
	glDeleteBuffers(1, &cubeVBOid);
	glDeleteVertexArrays(1, &cubeVAOid);

	SDL_GL_DeleteContext(openglContext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}





