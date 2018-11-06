#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>
#include "camera.h"
class Display
{
public:

	Display(int width, int height, const std::string& title);

	~Display();
	void Clear(float r, float g, float b, float a);
	bool IsClosed();
	
	void Update(Camera& camera);//SWAP BUFFERS

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
	float cameraShift = 2;
	float cameraDefault = 0.1f;
	float cameraSpeed = cameraDefault; // adjust accordingly
	bool isShiftPressed;
};

#endif