#include "display.h"
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);//INITIALIZE EVERYTHING 
	

	//ASSIGN GL_ATTRIBUTES
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);



	//CREATE WINDOW
	m_window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);//CREATE WINDOW
	m_glContext = SDL_GL_CreateContext(m_window);//ASSIGN CONTEXT

	//CHECK GLEW ERROR
	GLenum status = glewInit();//SEARCH THROUG
	if (status != GLEW_OK)
	{
		printf("GLEW failed to initialize!\n");
		
	}
	m_isClosed = false;


}


Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
	   
}
bool Display::IsClosed()
{
	return m_isClosed;
}
void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update(Camera& camera)//SWAP BUFFERS
{
	
	SDL_GL_SwapWindow(m_window);
	SDL_Event e;
	/*if(cameraSpeed==cameraShift)
	std::cout << "Shift" << std::endl;*/
	while (SDL_PollEvent(&e))
	{
		isShiftPressed = false;
		
		
		switch (e.type)
		{
		case SDL_QUIT:
			m_isClosed = true;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:

				m_isClosed = true;
				break;
			case SDLK_w:
				printf("w\n");
				camera.SetCameraPos(camera.GetCameraPos()+(cameraSpeed*camera.GetCameraFront()));
				//cameraPos += cameraSpeed * cameraFront;
				break;
			case SDLK_s:
				printf("s\n");
				camera.SetCameraPos(camera.GetCameraPos() - (cameraSpeed*camera.GetCameraFront()));
				//cameraPos -= cameraSpeed * cameraFront;
				break;
			case SDLK_a:
				printf("a\n");
				
				camera.SetCameraPos(camera.GetCameraPos() + (glm::normalize(glm::cross(camera.GetCameraFront(), camera.GetCameraUp()))*cameraSpeed));
				//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				
				break;
			case SDLK_d:
				printf("d\n");
				camera.SetCameraPos(camera.GetCameraPos() - (glm::normalize(glm::cross(camera.GetCameraFront(), camera.GetCameraUp()))*cameraSpeed));
				//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				break;
			case SDLK_LSHIFT:
				
				if (cameraSpeed == cameraShift)
					cameraSpeed = cameraDefault;
				else if (cameraSpeed == cameraDefault)
					cameraSpeed = cameraShift;				
				
				break;
			case SDLK_SPACE:
				printf("space\n");
				
				break;
			case SDLK_LCTRL:
				printf("LCTR\n");

				break;			
			default:				
				break;	

			}			
		//case SDL_KEYUP:
		//	switch (e.key.keysym.sym) 
		//	{
		//	case SDLK_LSHIFT:
		//		/* We check to make sure the alien is moving */
		//		/* to the left. If it is then we zero the    */
		//		/* velocity. If the alien is moving to the   */
		//		/* right then the right key is still press   */
		//		/* so we don't tocuh the velocity            */
		//		if (isShiftPressed == false)
		//			cameraSpeed = cameraDefault;
		//		break;
		//	
		//	default:
		//		break;
		//	}
		default:
			break;
			
		}
		
	}

}

