#include "GameOver.h"

GameOver::~GameOver() {
	free();
}

void GameOver::free() {
	gameStatus.free();

	playAgain.free();
	exit.free();
}

void GameOver::loadMedia(const Game& game) {

	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/Cocogoose.ttf", 40);

	if (game.getPlayerWinCount() > game.getaiWinCount())
		gameStatus.loadFromRenderedText("Congatulations!!! \nYou have won. :)", { 255, 255, 255, 255 }, 1000);
	else if (game.getPlayerWinCount() < game.getaiWinCount())
		gameStatus.loadFromRenderedText("The A.I won. Maybe \nwe are doomed. :(", { 255, 255, 255, 255 }, 1000);
	else
		gameStatus.loadFromRenderedText("Nobody won or lose. \nIt's a draw.", { 255, 255, 255, 255 }, 1000);

	loadButtons();
}

void GameOver::loadButtons() {
	//Load playAgain Again Button media
	playAgain.load_button_media("Play Again", 40, { 255,255,255 });

	playAgain.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	playAgain.set_button_dimensions(playAgain.get_Width(), playAgain.get_Height());

	playAgain.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	playAgain.setColorOnMouseDown({ 0, 135, 175, 255 }, { 255, 50, 0, 255 });
	playAgain.setColorOnMouseUp({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });

	//Load exit Button media
	exit.load_button_media("Exit", 40, { 255, 255, 255, 255 });

	exit.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	exit.set_button_dimensions(exit.get_Width(), exit.get_Height());

	exit.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	exit.setColorOnMouseDown({ 0, 135, 175, 255 }, { 255, 50, 0, 255 });
	exit.setColorOnMouseUp({ 0, 135, 175, 255 }, { 255, 80, 0, 255 });
}

void GameOver::render() {
	//Set color of window
	SDL_SetRenderDrawColor(GameWindow.Get_Renderer(), 0, 135, 175, 255);
	//Render whole window with set color
	SDL_RenderClear(GameWindow.Get_Renderer());

	//Render Game Status text
	gameStatus.renderTexture(nullptr, WINDOW_WIDTH - 210, WINDOW_HEIGHT - 200);

	//Render play Again button
	playAgain.render(WINDOW_WIDTH - 120, WINDOW_HEIGHT - 50);
	//Render exit button
	exit.render(WINDOW_WIDTH - 40, WINDOW_HEIGHT + 20);

	//Update window
	SDL_RenderPresent(GameWindow.Get_Renderer());
}

void GameOver::handleEvent(SDL_Event* e) {
	playAgain.handleEvent(e);
	exit.handleEvent(e);
}

bool GameOver::isTextureLoaded() {

	if (gameStatus.Get_Texture() == nullptr)
		return false;
	else
		return true;
}