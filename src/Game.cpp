#include "Game.h"

Game::Game() {
	loadMedia();
}

Game::~Game() {
	free();
}

void Game::free() {
	board.free();
}

void Game::loadMedia() {
	//Load Board
	board.load_media_from_file("assets/Sprites/Board.png");

	//Load Boxes
	loadBoxes();
}

void Game::loadBoxes() {
	//H & W of box
	int dimension = 174;

	//Initialize Boxes
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		boardSquare[i] = new Button();
		//Set box h & w
		boardSquare[i]->set_button_dimensions(dimension, dimension);
		
		//Set box color
		boardSquare[i]->setDefaultColor({ 0, 135, 175, 255 });
		boardSquare[i]->setColorOnHover({ 0, 135, 200, 255 });
		boardSquare[i]->setColorOnMouseDown({ 0, 135, 255, 255 });
		boardSquare[i]->setColorOnMouseUp({ 0, 135, 175, 255 });
	}

}

void Game::render() {
	//Set color of window
	SDL_SetRenderDrawColor(GameWindow.Get_Renderer(), 0, 135, 175, 255);
	//Render whole window with set color
	SDL_RenderClear(GameWindow.Get_Renderer());

	//Render board on screen
	board.renderTexture(nullptr, WINDOW_WIDTH - 300, WINDOW_HEIGHT - 300);

	//Render boxes on screen
	renderBoxes();

	//Update window
	SDL_RenderPresent(GameWindow.Get_Renderer());
}

void Game::renderBoxes() {

}

bool Game::checkTextureLoaded() {

	if (board.Get_Texture() == nullptr)
		return false;
	else
		return true;
}