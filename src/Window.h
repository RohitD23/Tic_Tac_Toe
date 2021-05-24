#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

class Window {
public:

	Window();

	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 800;
	static const int SCREEN_Y_POS = 50;

	//Create window and Renderer
	void init();

	void free();

	//Handle events for window(minimize,maximize,etc.)
	void handle_event(SDL_Event* e);

	int Get_Height() { return wHeight; }
	int Get_Width() { return wWidth; }

	bool Get_Minimized() { return wMinimized; }

	SDL_Renderer* Get_Renderer() { return renderer; }
	SDL_Window* Get_Window() { return window; }
	TTF_Font** Get_Font() { return &font; }

private:
	//Variable to create main window
	SDL_Window* window;

	//Variable to create renderer
	SDL_Renderer* renderer;

	//Variable to create text
	TTF_Font* font;

	//Variables to get window height and width
	int wHeight;
	int wWidth;

	//To check if screen is minimized
	bool wMinimized;
};
