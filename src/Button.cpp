#include "Button.h"

Button::Button() {

	box = { 0,0,0,0 };

	buttonColor = { 0, 0, 0, 0 };
	buttonDefaultColor = { 0, 0, 0, 0 };
	buttonColorOnHover = { 0, 0, 0, 0 };
	buttonColorOnMouseDown = { 0, 0, 0, 0 };
	buttonColorOnMouseUp = { 0, 0, 0, 0 };

	textColor = { 0, 0, 0, 0 };
	textColorOnHover = { 0, 0, 0, 0 };
	textColorOnMouseDown = { 0, 0, 0, 0 };
	textColorOnMouseUp = { 0, 0, 0, 0 };

	box = { 0,0,0,0 };

	isButtonPressed = false;
}

Button::~Button() { free(); }

void Button::free() {

	box = { 0,0,0,0 };

	buttonColor = { 0, 0, 0, 0 };
	buttonDefaultColor = { 0, 0, 0, 0 };
	buttonColorOnHover = { 0, 0, 0, 0 };
	buttonColorOnMouseDown = { 0, 0, 0, 0 };
	buttonColorOnMouseUp = { 0, 0, 0, 0 };

	textColor = { 0, 0, 0, 0 };
	textColorOnHover = { 0, 0, 0, 0 };
	textColorOnMouseDown = { 0, 0, 0, 0 };
	textColorOnMouseUp = { 0, 0, 0, 0 };

	ButtonText.free();

	isButtonPressed = false;
}

void Button::set_button_dimensions(int width, int height) {
	box.w = width;
	box.h = height;
}

void Button::load_button_media(std::string text, int fontSize,SDL_Color textColor) {

	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/Cocogoose.ttf", fontSize);

	ButtonText.loadFromRenderedText(text, textColor, 500);

}

void Button::render(int x, int y) {

	if (this != nullptr) {
		box.x = x;
		box.y = y;

		//Render Rectangle
		SDL_SetRenderDrawColor(GameWindow.Get_Renderer(), buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
		SDL_RenderFillRect(GameWindow.Get_Renderer(), &box);

		//Render text inside button
		ButtonText.renderTexture(nullptr, x, y);
	}
}

void Button::handleEvent(SDL_Event* e) {

	//If mouse event happened
	if (this != nullptr && (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)) {

		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < box.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > box.x + box.w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < box.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > box.y + box.h)
		{
			inside = false;
		}

		//If mouse is inside button
		if (inside) {

			//Set Color and check button pressed
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				setColorOnEvent(textColorOnHover);
				buttonColor = buttonColorOnHover;
				break;

			case SDL_MOUSEBUTTONDOWN:
				setColorOnEvent(textColorOnMouseDown);
				buttonColor = buttonColorOnMouseDown;
				break;

			case SDL_MOUSEBUTTONUP:
				setColorOnEvent(textColorOnMouseUp);
				buttonColor = buttonColorOnMouseUp;
				isButtonPressed = true;
				break;
			}
		}
		else {
			setColorOnEvent(textColor);
			buttonColor = buttonDefaultColor;
		}
	}
	

}

void Button::setDefaultColor(SDL_Color buttonColor, SDL_Color textColor) {
	buttonDefaultColor = buttonColor;
	this->buttonColor = buttonColor;
	this->textColor = textColor;
}

void Button::setColorOnHover(SDL_Color buttonColor, SDL_Color textColor) {
	buttonColorOnHover = buttonColor;
	textColorOnHover = textColor;
}

void Button::setColorOnMouseDown(SDL_Color buttonColor, SDL_Color textColor) {
	buttonColorOnMouseDown = buttonColor;
	textColorOnMouseDown = textColor;
}

void Button::setColorOnMouseUp(SDL_Color buttonColor, SDL_Color textColor) {
	buttonColorOnMouseUp = buttonColor;
	textColorOnMouseUp = textColor;
}