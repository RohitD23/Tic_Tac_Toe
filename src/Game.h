#pragma once
#include "Texture.h"
#include "Button.h"
#include "Data.h"

struct GridElements {
	Texture* x_o_image;
	char x_o;
};

class Game {
public:
	Game();

	~Game();

	void free();

	void loadMedia();

	void render();

	void handleEvent(SDL_Event* e, Player* currentPlayer);

	bool checkTextureLoaded();

	bool checkButtonPressed(Player* currentPlayer);

private:
	//No. of Boxes on board
	const int static TOTAL_BOX = 3 ;

	//Board image
	Texture board;

	//Represents each box in board
	Button* gridBoxes[TOTAL_BOX][TOTAL_BOX];

	//To display X or O image
	GridElements* gridElements[TOTAL_BOX][TOTAL_BOX];

	//Score board
	Texture scoreBoard;

	void loadGridBoxes();
	void renderGridBoxes();

	void loadGridElements();
	void renderGridElements();

};