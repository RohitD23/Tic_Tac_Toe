#include "Game.h"

Game::Game() {
	loadMedia();
}

Game::~Game() {
	free();
}

void Game::free() {
	board.free();
	scoreBoard.free();

	for (int i{ 0 }; i < TOTAL_BOX; i++) {

		for (int j{ 0 }; j < TOTAL_BOX; j++) {
			delete gridBoxes[i][j];
			delete gridElements[i][j];

			gridBoxes[i][j] = nullptr;
			gridElements[i][j]= nullptr;
		}
	}
}

void Game::loadMedia() {
	//Load Board
	board.load_media_from_file("assets/Sprites/Board.png");

	//Load Score board
	scoreBoard.load_media_from_file("assets/Sprites/ScoreBoard.png");

	//Load Boxes
	loadGridBoxes();

	loadGridElements();
}

void Game::loadGridBoxes() {
	//H & W of box
	int dimension = 150;

	//Initialize Boxes
	for (int i{ 0 }; i < TOTAL_BOX; i++) {

		for (int j{ 0 }; j < TOTAL_BOX; j++) {
			gridBoxes[i][j] = new Button();
			//Set box h & w
			gridBoxes[i][j]->set_button_dimensions(dimension, dimension);

			//Set box color
			gridBoxes[i][j]->setDefaultColor({ 0, 135, 175, 255 });
			gridBoxes[i][j]->setColorOnHover({ 0, 194, 252, 255 });
			gridBoxes[i][j]->setColorOnMouseDown({ 0, 96, 125, 255 });
			gridBoxes[i][j]->setColorOnMouseUp({ 0, 135, 175, 255 });
		}
	}

}

void Game::loadGridElements() {

	for (int i{ 0 }; i < TOTAL_BOX; i++) {

		for (int j{ 0 }; j < TOTAL_BOX; j++)
			gridElements[i][j] = new GridElements();

	}
}

void Game::render() {
	//Set color of window
	SDL_SetRenderDrawColor(GameWindow.Get_Renderer(), 0, 135, 175, 255);
	//Render whole window with set color
	SDL_RenderClear(GameWindow.Get_Renderer());

	//Render Score Board
	scoreBoard.renderTexture(nullptr, WINDOW_WIDTH - 220, WINDOW_HEIGHT - 390);

	//Render board on screen
	board.renderTexture(nullptr, WINDOW_WIDTH - 250, WINDOW_HEIGHT - 200);

	//Render boxes on screen
	renderGridBoxes();

	//Render what player played
	renderGridElements();

	//Update window
	SDL_RenderPresent(GameWindow.Get_Renderer());
}

void Game::renderGridBoxes() {
	gridBoxes[0][0]->render(WINDOW_WIDTH - 232, WINDOW_HEIGHT - 183);
	gridBoxes[0][1]->render(WINDOW_WIDTH - 73, WINDOW_HEIGHT - 183);
	gridBoxes[0][2]->render(WINDOW_WIDTH + 85, WINDOW_HEIGHT - 183);

	gridBoxes[1][0]->render(WINDOW_WIDTH - 232, WINDOW_HEIGHT - 25);
	gridBoxes[1][1]->render(WINDOW_WIDTH - 73, WINDOW_HEIGHT - 25);
	gridBoxes[1][2]->render(WINDOW_WIDTH + 85, WINDOW_HEIGHT - 25);

	gridBoxes[2][0]->render(WINDOW_WIDTH - 232, WINDOW_HEIGHT + 133);
	gridBoxes[2][1]->render(WINDOW_WIDTH - 73, WINDOW_HEIGHT + 133);
	gridBoxes[2][2]->render(WINDOW_WIDTH + 85, WINDOW_HEIGHT + 133);
}

void Game::renderGridElements(){
	gridElements[0][0]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH - 232, WINDOW_HEIGHT - 183);
	gridElements[0][1]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH - 73, WINDOW_HEIGHT - 183);
	gridElements[0][2]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH + 85, WINDOW_HEIGHT - 183);

	gridElements[1][0]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH - 232, WINDOW_HEIGHT - 25);
	gridElements[1][1]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH - 73, WINDOW_HEIGHT - 25);
	gridElements[1][2]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH + 85, WINDOW_HEIGHT - 25);

	gridElements[2][0]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH - 232, WINDOW_HEIGHT + 133);
	gridElements[2][1]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH - 73, WINDOW_HEIGHT + 133);
	gridElements[2][2]->x_o_image->renderTexture(nullptr, WINDOW_WIDTH + 85, WINDOW_HEIGHT + 133);
}

bool Game::checkTextureLoaded() {

	if (board.Get_Texture() == nullptr)
		return false;
	else
		return true;
}

void Game::handleEvent(SDL_Event* e, Player* currentPlayer) {

	if (currentPlayer->playerType == PlayerType::PT_HUMAN) {

		for (int i{ 0 }; i < TOTAL_BOX; i++) {
			for (int j{ 0 }; j < TOTAL_BOX; j++)
				gridBoxes[i][j]->handleEvent(e);
		}
	}
}

bool Game::checkButtonPressed(Player* currentPlayer) {

	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX; j++) {

			if (gridBoxes[i][j] != nullptr) {
				if (gridBoxes[i][j]->get_isButtonPressed()) {
					delete gridBoxes[i][j];
					gridBoxes[i][j] = nullptr;

					gridElements[i][j]->x_o_image = &(currentPlayer->elementTexture);
					gridElements[i][j]->x_o = currentPlayer->elementType;

					return true;
				}
			}
		}
	}

	return false;

}

