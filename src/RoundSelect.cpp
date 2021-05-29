#include "RoundSelect.h"

RoundSelect::RoundSelect() {
	loadMedia();
}

RoundSelect::~RoundSelect() {
	free();
}

void RoundSelect::free() {
	chooseText.free();
	numberText.free();

	decreaseNumber.free();
	increaseNumber.free();
	startGame.free();
}

void RoundSelect::loadMedia() {

	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/Cocogoose.ttf", 35);

	chooseText.loadFromRenderedText("Choose Number of rounds", { 255, 255, 255, 255 }, 600);

	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/NunitoSans.ttf", 90);
	numberText.loadFromRenderedText("05", { 255, 255, 255, 255 }, 600);

	loadButtons();
}

void RoundSelect::loadButtons() {

	//Load Decrease Round Number button
	decreaseNumber.load_button_media("<", 65, { 255, 255, 255, 255 });

	decreaseNumber.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	decreaseNumber.set_button_dimensions(decreaseNumber.get_Width(), decreaseNumber.get_Height());

	decreaseNumber.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	decreaseNumber.setColorOnMouseDown({ 0, 135, 175, 255 }, { 255, 50, 0, 255 });
	decreaseNumber.setColorOnMouseUp({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });

	//Load Increase Round Number button
	increaseNumber.load_button_media(">", 65, { 255, 255, 255, 255 });

	increaseNumber.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	increaseNumber.set_button_dimensions(increaseNumber.get_Width(), increaseNumber.get_Height());

	increaseNumber.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	increaseNumber.setColorOnMouseDown({ 0, 135, 175, 255 }, { 255, 50, 0, 255 });
	increaseNumber.setColorOnMouseUp({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });

	//Load Start Game button
	startGame.load_button_media("START", 70, { 255, 255, 255, 255 });

	startGame.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	startGame.set_button_dimensions(startGame.get_Width(), startGame.get_Height());

	startGame.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	startGame.setColorOnMouseDown({ 0, 135, 175, 255 }, { 255, 50, 0, 255 });
	startGame.setColorOnMouseUp({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
}

void RoundSelect::render() {
	//Set color of window
	SDL_SetRenderDrawColor(GameWindow.Get_Renderer(), 0, 135, 175, 255);
	//Render whole window with set color
	SDL_RenderClear(GameWindow.Get_Renderer());

	chooseText.renderTexture(nullptr, WINDOW_WIDTH - 260, WINDOW_HEIGHT - 200);
	numberText.renderTexture(nullptr, WINDOW_WIDTH - 60, WINDOW_HEIGHT - 100);

	decreaseNumber.render(WINDOW_WIDTH - 115, WINDOW_HEIGHT - 85);
	increaseNumber.render(WINDOW_WIDTH + 75, WINDOW_HEIGHT - 85);
	startGame.render(WINDOW_WIDTH - 120, WINDOW_HEIGHT + 50);

	//Update window
	SDL_RenderPresent(GameWindow.Get_Renderer());
}

void RoundSelect::handleEvent(SDL_Event* e) {
	decreaseNumber.handleEvent(e);
	increaseNumber.handleEvent(e);
	startGame.handleEvent(e);
}

bool RoundSelect::isTextureLoaded() {

	if (chooseText.Get_Texture() == nullptr)
		return false;
	else
		return true;
}