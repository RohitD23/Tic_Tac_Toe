#pragma once
#include "Window.h"

extern Window GameWindow;

#define WINDOW_WIDTH (GameWindow.Get_Width() / 2)
#define WINDOW_HEIGHT (GameWindow.Get_Height() / 2)

class Texture {

public:
	Texture();

	~Texture();

	//To free texture
	void free();

	//To load assets from device
	void load_media_from_file(std::string path);
	//path is address of assets to load assets from device

	//To load font
	void loadFromRenderedText(std::string textureText, SDL_Color textColor, int wrap);
	/*
	* textureText - text to load on window
	* textColor - Color of text
	* wrap - How much words to fit in one line
	*/

	//To create texture from surface
	void loadTextureFromSurface(SDL_Surface* surface);

	//Render assets on window
	void renderTexture(SDL_Rect* clip, int x, int y);
	/*
	* clip - how much part of asset to render
	* x - x_pos in window
	* y - y_pos in window
	*/

	//To change color of text
	void setColor(const SDL_Color& color);

	SDL_Texture* Get_Texture() { return texture; }

	int Get_Width() { return tWidth; }
	int Get_Height() { return tHeight; }

private:
	SDL_Texture* texture;

	//H & W of texture
	int tHeight;
	int tWidth;
};
