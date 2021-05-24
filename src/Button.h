#pragma once
#include "Texture.h"

class Button {

public:
	Button();

	~Button();

	void free();

	void render(int x, int y);

	void load_button_media(std::string text, int fontSize);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	bool get_isButtonPressed() { return isButtonPressed; }
	void set_isButtonPressed(bool isButtonPressed) { this->isButtonPressed = isButtonPressed; }

	int get_Width() { return ButtonText.Get_Width(); }
	int get_Height() { return ButtonText.Get_Height(); }

	//Set box h & w
	void set_button_dimensions(int width, int height);

	//Set text color on event
	void setColorOnEvent(const SDL_Color& textColor) { ButtonText.setColor(textColor); }

	//Set default color of button and text
	void setDefaultColor(SDL_Color buttonColor = { 0,0,0,0 }, SDL_Color textColor = { 0,0,0,0 });
	//Set text and button color on hover
	void setColorOnHover(SDL_Color buttonColor = { 0,0,0,0 }, SDL_Color textColor = { 0,0,0,0 });
	//Set text and button color on mouse down
	void setColorOnMouseDown(SDL_Color buttonColor = { 0,0,0,0 }, SDL_Color textColor = { 0,0,0,0 });
	//Set text and button color on mouse up
	void setColorOnMouseUp(SDL_Color buttonColor = { 0,0,0,0 }, SDL_Color textColor = { 0,0,0,0 });


private:

	//Color of button
	SDL_Color buttonColor;
	SDL_Color buttonDefaultColor;
	SDL_Color buttonColorOnHover;
	SDL_Color buttonColorOnMouseDown;
	SDL_Color buttonColorOnMouseUp;

	//Color of text
	SDL_Color textColor;
	SDL_Color textColorOnHover;
	SDL_Color textColorOnMouseDown;
	SDL_Color textColorOnMouseUp;

	//Button text
	Texture ButtonText;

	//Rectangle around button
	SDL_Rect box;

	bool isButtonPressed;
};