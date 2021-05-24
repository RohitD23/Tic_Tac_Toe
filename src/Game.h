#pragma once
#include "Texture.h"
#include "Button.h"

class Game {
public:
	Game();

	~Game();

	void free();

	void loadMedia();

	void render();

	void handleEvent(SDL_Event* e);

	bool checkTextureLoaded();

private:
	//No. of Boxes on board
	const int static TOTAL_BOX = 9;

	//Board image
	Texture board;

	//Represents each box in board
	Button* boardSquare[TOTAL_BOX];

	void loadBoxes();
	void renderBoxes();
};