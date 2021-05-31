#pragma once
#include "Texture.h"
#include "Button.h"
#include "Game.h"

class GameOver {
public:
	~GameOver();

	void free();

	void loadMedia(const Game& game);

	void render();

	void handleEvent(SDL_Event* e);

	bool isTextureLoaded();

	//To check button is pressed
	bool isPlayAgainButtonPressed() const { return playAgain.get_isButtonPressed(); }
	bool isExitButtonPressed() const { return exit.get_isButtonPressed(); }

private:
	//What is the result of the game
	Texture gameStatus;

	Button playAgain;
	Button exit;

	void loadButtons();
};