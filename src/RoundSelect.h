#pragma once
#include "Texture.h"
#include "Button.h"

class RoundSelect {
public:
	~RoundSelect();

	void free();

	void loadMedia();

	void render();

	void handleEvent(SDL_Event* e);

	bool isTextureLoaded();

	bool isDecreaseNumberPressed() { return decreaseNumber.get_isButtonPressed(); }
	bool isIncreaseNumberPressed() { return increaseNumber.get_isButtonPressed(); }
	bool isStartGamePressed() { return startGame.get_isButtonPressed(); }

	void setDecreaseNumberPressed(bool setButtonPressed) { decreaseNumber.set_isButtonPressed(setButtonPressed); }
	void setIncreaseNumberPressed(bool setButtonPressed) { increaseNumber.set_isButtonPressed(setButtonPressed); }

	Texture* getNumberText() { return &numberText; }
private:

	Texture chooseText;
	Texture numberText;

	Button decreaseNumber;
	Button increaseNumber;
	Button startGame;

	//Load Button Media
	void loadButtons();
};