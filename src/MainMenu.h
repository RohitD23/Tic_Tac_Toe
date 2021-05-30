#pragma once
#include "Texture.h"
#include "Button.h"

class MainMenu {
public:
	~MainMenu();

	void free();

	void load_media();

	void render();

	void handleEvent(SDL_Event* e);

	//To check button is pressed
	bool isPlayButtonPressed() { return play.get_isButtonPressed(); }
	bool isSoundButtonPressed() { return sound.get_isButtonPressed(); }
	bool isExitButtonPressed() { return exit.get_isButtonPressed(); }

	void setPlayButton(bool buttonPresssed) { play.set_isButtonPressed(buttonPresssed); }
	void setSoundButton(bool buttonPresssed) { sound.set_isButtonPressed(buttonPresssed); }

	//To change sound text
	void changeSoundText(std::string text);

	//Check if media is empty or not
	bool isTextureLoaded();

private:
	//Title text
	Texture title;

	//Menu Buttons
	Button play;
	Button sound;
	Button exit;

	//Load Button Media
	void load_buttons();

};