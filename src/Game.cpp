#include "Game.h"

Game::~Game() {
	free();
}

void Game::free() {
	board.free();
	scoreBoard.free();

	roundsPlayed = 1;
	playerWinCount = 0;
	aiWinCount = 0;

	aiMoveCount = 0;
	hasPlayerPlayedNearAI = false;

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

	roundsPlayed = 1;
	playerWinCount = 0;
	aiWinCount = 0;

	aiMoveCount = 0;
	hasPlayerPlayedNearAI = false;

	//Load Board
	board.load_media_from_file("assets/Sprites/Board.png");

	//Load Score Board
	loadScoreBoard();

	//Load Boxes
	loadGridBoxes();

	loadGridElements();

}

void Game::loadScoreBoard() {
	//Load Score board
	scoreBoard.load_media_from_file("assets/Sprites/ScoreBoard.png");

	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/Cocogoose.ttf", 30);

	//Score text
	scoreText[0].loadFromRenderedText("Round :", { 255, 255, 255, 255 }, 500);
	scoreText[1].loadFromRenderedText("Score", { 255, 255, 255, 255 }, 500);
	scoreText[2].loadFromRenderedText("Player :", { 255, 255, 255, 255 }, 500);
	scoreText[3].loadFromRenderedText("A.I. :", { 255, 255, 255, 255 }, 500);

	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/NunitoSans.ttf", 30);

	loadCurrentRound();

	loadPlayerScore();

	loadAiScore();
}

void Game::loadCurrentRound() {
	std::stringstream ss;
	ss << roundsPlayed;
	currentRound.loadFromRenderedText(ss.str(), { 255, 255, 255, 255 }, 500);
}

void Game::loadPlayerScore() {
	std::stringstream ss;
	ss << playerWinCount;
	playerScore.loadFromRenderedText(ss.str(), { 255, 255, 255, 255 }, 500);
}

void Game::loadAiScore() {
	std::stringstream ss;
	ss << aiWinCount;
	aiScore.loadFromRenderedText(ss.str(), { 255, 255, 255, 255 }, 500);
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

	renderScoreBoard();

	//Render board on screen
	board.renderTexture(nullptr, WINDOW_WIDTH - 250, WINDOW_HEIGHT - 200);

	//Render boxes on screen
	renderGridBoxes();

	//Render what player played
	renderGridElements();

	//Update window
	SDL_RenderPresent(GameWindow.Get_Renderer());
}

void Game::renderScoreBoard() {
	//Render Score Board
	scoreBoard.renderTexture(nullptr, WINDOW_WIDTH - 220, WINDOW_HEIGHT - 390);

	//Render Score Text
	scoreText[0].renderTexture(nullptr, WINDOW_WIDTH - 70, WINDOW_HEIGHT - 375);
	scoreText[1].renderTexture(nullptr, WINDOW_WIDTH - 45, WINDOW_HEIGHT - 335);
	scoreText[2].renderTexture(nullptr, WINDOW_WIDTH - 200, WINDOW_HEIGHT - 290);
	scoreText[3].renderTexture(nullptr, WINDOW_WIDTH + 20, WINDOW_HEIGHT - 290);

	currentRound.renderTexture(nullptr, WINDOW_WIDTH + 70, WINDOW_HEIGHT - 375);
	playerScore.renderTexture(nullptr, WINDOW_WIDTH - 60, WINDOW_HEIGHT - 290);
	aiScore.renderTexture(nullptr, WINDOW_WIDTH + 100, WINDOW_HEIGHT - 290);
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

bool Game::isTextureLoaded() {

	if (board.Get_Texture() == nullptr)
		return false;
	else
		return true;
}

void Game::handleEvent(SDL_Event* e,const Player* currentPlayer) {

	if (currentPlayer->playerType == PlayerType::PT_HUMAN) {

		for (int i{ 0 }; i < TOTAL_BOX; i++) {
			for (int j{ 0 }; j < TOTAL_BOX; j++)
				gridBoxes[i][j]->handleEvent(e);
		}
	}
}

bool Game::isButtonPressed(Player* currentPlayer) {

	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX; j++) {

			if (gridBoxes[i][j] != nullptr) {
				//Check if player has played
				if (gridBoxes[i][j]->get_isButtonPressed()) {
					changeGridElements(i, j, currentPlayer);

					return true;
				}
			}
		}
	}

	return false;

}

void Game::changeGridElements(int x, int y, Player* currentPlayer) {
	//If played free memory of gridBox
	delete gridBoxes[x][y];
	gridBoxes[x][y] = nullptr;

	//Initialize Image where player has played
	gridElements[x][y]->x_o_image = &(currentPlayer->elementTexture);
	//initialize who played
	gridElements[x][y]->whoPlayedOnGrid = currentPlayer->playersGrid;
}

bool Game::isGridFull() {

	int gridRecored = 0;

	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX - 2; j++) {

			if (gridElements[i][j]->whoPlayedOnGrid != PlayersGrid::PG_NONE &&
				gridElements[i][j + 1]->whoPlayedOnGrid != PlayersGrid::PG_NONE &&
				gridElements[i][j + 2]->whoPlayedOnGrid != PlayersGrid::PG_NONE) {
				gridRecored++;
			}
		}
	}
	
	if (gridRecored == 3) {
		cleanBoard();
		return true;
	}

	return false;
}

bool Game::hasAnyoneWon() {

	//For Horizontal
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX - 2; j++) {

			if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
				gridElements[i][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
				gridElements[i][j + 2]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) 
			{
				cleanBoard();

				playerWinCount++;
				loadPlayerScore();

				return true;
			}
			else if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
				gridElements[i][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
				gridElements[i][j + 2]->whoPlayedOnGrid == PlayersGrid::PG_AI)
			{
				cleanBoard();

				aiWinCount++;
				loadAiScore();

				return true;
			}
		}
	}

	//For Vertical
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX - 2; j++) {

			if (gridElements[j][i]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
				gridElements[j + 1][i]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
				gridElements[j + 2][i]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN)
			{
				cleanBoard();

				playerWinCount++;
				loadPlayerScore();

				return true;
			}
			else if (gridElements[j][i]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
				gridElements[j + 1][i]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
				gridElements[j + 2][i]->whoPlayedOnGrid == PlayersGrid::PG_AI)
			{
				cleanBoard();

				aiWinCount++;
				loadAiScore();

				return true;
			}
		}
	}

	//For Cross from left
	if (gridElements[0][0]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
		gridElements[1][1]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
		gridElements[2][2]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN)
	{
		cleanBoard();

		playerWinCount++;
		loadPlayerScore();

		return true;
	}
	else if (gridElements[0][0]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
		gridElements[1][1]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
		gridElements[2][2]->whoPlayedOnGrid == PlayersGrid::PG_AI)
	{
		cleanBoard();

		aiWinCount++;
		loadAiScore();

		return true;
	}

	//For Cross from right
	if (gridElements[0][2]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
		gridElements[1][1]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
		gridElements[2][0]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN)
	{
		cleanBoard();

		playerWinCount++;
		loadPlayerScore();

		return true;
	}
	else if (gridElements[0][2]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
		gridElements[1][1]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
		gridElements[2][0]->whoPlayedOnGrid == PlayersGrid::PG_AI)
	{
		cleanBoard();

		aiWinCount++;
		loadAiScore();

		return true;
	}
	
	return false;
}

void Game::cleanBoard() {
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX; j++) {
			delete gridElements[i][j];
			gridElements[i][j] = nullptr;
			gridElements[i][j] = new GridElements();

			loadGridBoxes();
		}
	}
	roundsPlayed++;

	loadCurrentRound();
}

bool Game::isPlayerWinning(Player* currentPlayer) {

	//For Horizontal
	for (int i = 0 ; i < TOTAL_BOX; i++) {
		for (int j = 0 ; j < (TOTAL_BOX - 1); j++) {
			for (int k = j + 1 ; k < TOTAL_BOX; k++) {

				if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
					gridElements[i][k]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) 
				{
					if (k == 1 && gridElements[i][k + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, k + 1, currentPlayer);
						return true;
					}

					else if (j == 1 && gridElements[i][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j - 1, currentPlayer);
						return true;
					}

					else if (k == 2 && gridElements[i][k - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, k - 1, currentPlayer);
						return true;
					}

				}
			}
		}
	}

	//For Vertical
	for (int i = 0 ; i < TOTAL_BOX; i++) {
		for (int j = 0 ; j < (TOTAL_BOX - 1); j++) {
			for (int k = j + 1 ; k < TOTAL_BOX; k++) {

				if (gridElements[j][i]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
					gridElements[k][i]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) 
				{
					if (k == 1 && gridElements[k + 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(k + 1, i, currentPlayer);
						return true;
					}

					else if (j == 1 && gridElements[j - 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j - 1, i, currentPlayer);
						return true;
					}

					else if (k == 2 && gridElements[k - 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(k - 1, i, currentPlayer);
						return true;
					}
				}
			}
		}
	}

	//For Cross from left
	for (int i = 0 ; i < TOTAL_BOX - 1; i++) {
		for (int j = i + 1 ; j < TOTAL_BOX; j++) {

			if (gridElements[i][i]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
				gridElements[j][j]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) 
			{
				if (j == 1 && gridElements[j + 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(j + 1, j + 1, currentPlayer);
					return true;
				}

				else if (i == 1 && gridElements[i - 1][i - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, i - 1, currentPlayer);
					return true;
				}

				else if (j == 2 && gridElements[j - 1][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(j - 1, j - 1, currentPlayer);
					return true;
				}
			}
			
		}
	}

	//For Cross from right
	for (int i = 0 , j = TOTAL_BOX - 1 ; i < TOTAL_BOX - 1; i++, j--) {
		for (int k = i + 1 , l = j - 1 ; k < TOTAL_BOX; k++, l--){

			if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN &&
				gridElements[k][l]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN)
			{
				if (k == 1 && gridElements[k + 1][l - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(k + 1, l - 1, currentPlayer);
					return true;
				}

				else if (i == 1 && gridElements[i - 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, j + 1, currentPlayer);
					return true;
				}

				else if (k == 2 && gridElements[k - 1][l + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(k - 1, l + 1, currentPlayer);
					return true;
				}
			}
		}
	}

	return false;
}

bool Game::isAIWinning(Player* currentPlayer) {
	//For Horizontal
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < (TOTAL_BOX - 1); j++) {
			for (int k{ j + 1 }; k < TOTAL_BOX; k++) {

				if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
					gridElements[i][k]->whoPlayedOnGrid == PlayersGrid::PG_AI)
				{
					if (k == 1 && gridElements[i][k + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, k + 1, currentPlayer);
						return true;
					}

					else if (j == 1 && gridElements[i][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j - 1, currentPlayer);
						return true;
					}

					else if (k == 2 && gridElements[i][k - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, k - 1, currentPlayer);
						return true;
					}
				}
			}
		}
	}

	//For Vertical
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < (TOTAL_BOX - 1); j++) {
			for (int k{ j + 1 }; k < TOTAL_BOX; k++) {

				if (gridElements[j][i]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
					gridElements[k][i]->whoPlayedOnGrid == PlayersGrid::PG_AI)
				{
					if (k == 1 && gridElements[k + 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(k + 1, i, currentPlayer);
						return true;
					}

					else if (j == 1 && gridElements[j - 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j - 1, i, currentPlayer);
						return true;
					}

					else if (k == 2 && gridElements[k - 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(k - 1, i, currentPlayer);
						return true;
					}
				}
			}
		}
	}

	//For Cross from left
	for (int i{ 0 }; i < TOTAL_BOX - 1; i++) {
		for (int j{ i + 1 }; j < TOTAL_BOX; j++) {

			if (gridElements[i][i]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
				gridElements[j][j]->whoPlayedOnGrid == PlayersGrid::PG_AI)
			{
				if (j == 1 && gridElements[j + 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(j + 1, j + 1, currentPlayer);
					return true;
				}

				else if (i == 1 && gridElements[i - 1][i - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, i - 1, currentPlayer);
					return true;
				}

				else if (j == 2 && gridElements[j - 1][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(j - 1, j - 1, currentPlayer);
					return true;
				}
			}
		}
	}

	//For Cross from right
	for (int i{ 0 }, j{ TOTAL_BOX - 1 }; i < TOTAL_BOX - 1; i++, j--) {
		for (int k{ i + 1 }, l{ j - 1 }; k < TOTAL_BOX; k++, l--) {

			if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_AI &&
				gridElements[k][l]->whoPlayedOnGrid == PlayersGrid::PG_AI)
			{
				if (k == 1 && gridElements[k + 1][l - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(k + 1, l - 1, currentPlayer);
					return true;
				}

				else if (i == 1 && gridElements[i - 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, j + 1, currentPlayer);
					return true;
				}

				else if (k == 2 && gridElements[k - 1][l + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(k - 1, l + 1, currentPlayer);
					return true;
				}
			}
		}
	}

	return false;
}

void Game::aiAttackStartergy(Player* currentPlayer) {
	
	if (aiMoveCount == 0)
		aiFirstMove(currentPlayer);
	else if (hasPlayerPlayedNearAI) {
		changeGridElements(ai_move.first, ai_move.second, currentPlayer);
		hasPlayerPlayedNearAI = false;
	}
	else if (gridElements[1][1]->whoPlayedOnGrid == PlayersGrid::PG_NONE)
		isCornerEmpty(currentPlayer);
	else if (aiMoveCount == 1)
		playNearFirstMove(currentPlayer);
	else
		randomMove(currentPlayer);
	
}

void Game::aiDefenceStratergy(Player* currentPlayer) {
	
	if (aiMoveCount == 0 && gridElements[1][1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
		if (rand() % 2 == 0)
			aiFirstMove(currentPlayer);
		else {
			changeGridElements(1, 1, currentPlayer);
		}
	}
	else
		playNearMove(currentPlayer);
	
}

void Game::aiFirstMove(Player* currentPlayer) {
	
	int x, y;

	do {
		x = rand() % TOTAL_BOX;
		y = rand() % TOTAL_BOX;
	} while (x == 1 || y == 1);

	ai_move = { x, y };

	changeGridElements(x, y, currentPlayer);

	aiMoveCount++;
}

void Game::isCornerEmpty(Player* currentPlayer) {

	//Check top left corner
	if (gridElements[0][0]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[0][1]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[1][0]->whoPlayedOnGrid == PlayersGrid::PG_NONE)
	{
			changeGridElements(0, 0, currentPlayer);
			aiMoveCount++;
			return;
	}
	//Check top right corner
	else if (gridElements[0][2]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[0][1]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[1][2]->whoPlayedOnGrid == PlayersGrid::PG_NONE)
	{
		changeGridElements(0, 2, currentPlayer);
		aiMoveCount++;
		return;
	}
	//Check bottom left corner
	else if (gridElements[2][0]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[1][0]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[2][1]->whoPlayedOnGrid == PlayersGrid::PG_NONE)
	{
		changeGridElements(2, 0, currentPlayer);
		aiMoveCount++;
		return;
	}
	//Check bottom right corner
	else if (gridElements[2][2]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[2][1]->whoPlayedOnGrid == PlayersGrid::PG_NONE &&
		gridElements[1][2]->whoPlayedOnGrid == PlayersGrid::PG_NONE)
	{
		changeGridElements(2, 2, currentPlayer);
		aiMoveCount++;
		return;
	}
	
	if(aiMoveCount >= 2){
		//Check top left corner
		if(gridElements[0][0]->whoPlayedOnGrid == PlayersGrid::PG_NONE) 
			changeGridElements(0, 0, currentPlayer);		
		//Check top right corner
		else if (gridElements[0][2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) 
			changeGridElements(0, 2, currentPlayer);		
		//Check bottom left corner
		else if (gridElements[2][0]->whoPlayedOnGrid == PlayersGrid::PG_NONE) 
			changeGridElements(2, 0, currentPlayer);
		//Check bottom right corner
		else if (gridElements[2][2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) 
			changeGridElements(2, 2, currentPlayer);		
	}
}

void Game::playerPlayedNearAI() {

	if (ai_move.first == 0 && ai_move.second == 0) {
		
		if (gridElements[1][0]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 0, 2 };
		}
		else if (gridElements[0][1]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 2, 0 };
		}
	}
	else if (ai_move.first == 0 && ai_move.second == 2) {

		if (gridElements[1][2]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 0, 0 };
		}
		else if (gridElements[0][1]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 2, 2 };
		}
	}
	else if (ai_move.first == 2 && ai_move.second == 0) {

		if (gridElements[1][0]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 2, 2 };
		}
		else if (gridElements[2][1]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 0, 0 };
		}
	}
	else if (ai_move.first == 2 && ai_move.second == 2) {

		if (gridElements[2][1]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 0, 2 };
		}
		else if (gridElements[1][2]->whoPlayedOnGrid == PlayersGrid::PG_HUMAN) {
			hasPlayerPlayedNearAI = true;
			ai_move = { 2, 0 };
		}
	}

}

void Game::playNearFirstMove(Player* currentPlayer) {

	int x, y;

	if (ai_move.first == 0 && ai_move.second == 0) {

		do {
			x = rand() % TOTAL_BOX;
			y = rand() % TOTAL_BOX;
		} while ((!(x == 0 && (y == 1 || y == 2)) && !((x == 1 || x == 2) && y == 0)));

		changeGridElements(x, y, currentPlayer);
	}

	else if (ai_move.first == 0 && ai_move.second == 2) {
		do {
			x = rand() % TOTAL_BOX;
			y = rand() % TOTAL_BOX;
		} while ((!(x == 0 && (y == 0 || y == 1)) && !((x == 1 || x == 2) && y == 2)));

		changeGridElements(x, y, currentPlayer);
	}

	else if (ai_move.first == 2 && ai_move.second == 0) {
		do {
			x = rand() % TOTAL_BOX;
			y = rand() % TOTAL_BOX;
		} while ((!(x == 2 && (y == 1 || y == 2)) && !((x == 0 || x == 1) && y == 0)));

		changeGridElements(x, y, currentPlayer);
	}

	else if (ai_move.first == 2 && ai_move.second == 2) {
		do {
			x = rand() % TOTAL_BOX;
			y = rand() % TOTAL_BOX;
		} while ((!(x == 2 && (y == 0 || y == 1)) && !((x == 0 || x == 1) && y == 2)));

		changeGridElements(x, y, currentPlayer);
	}

	aiMoveCount++;
}

void Game::playNearMove(Player* currentPlayer) {
	
	//For Horizontal
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX; j++) {

			if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_AI) {
				if (j == 0) {
					if (gridElements[i][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j + 1, currentPlayer);
						return;
					}
					else if (gridElements[i][j + 2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j + 2, currentPlayer);
						return;
					}
				}
				else if(j == 1){
					if (gridElements[i][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j - 1, currentPlayer);
						return;
					}
					else if (gridElements[i][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j + 1, currentPlayer);
						return;
					}
				}
				else if (j == 2) {
					if (gridElements[i][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j - 1, currentPlayer);
						return;
					}
					else if (gridElements[i][j - 2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(i, j - 2, currentPlayer);
						return;
					}
				}
			}
		}
	}

	//For Vertical
	for (int i{ 0 }; i < TOTAL_BOX; i++) {
		for (int j{ 0 }; j < TOTAL_BOX; j++) {

			if (gridElements[j][i]->whoPlayedOnGrid == PlayersGrid::PG_AI) {
				if (j == 0) {
					if (gridElements[j + 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j + 1, i, currentPlayer);
						return;
					}
					else if (gridElements[j + 2][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j + 2, i, currentPlayer);
						return;
					}
				}
				else if (j == 1) {
					if (gridElements[j - 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j - 1, i, currentPlayer);
						return;
					}
					else if (gridElements[j + 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j + 1, i, currentPlayer);
						return;
					}
				}
				else if (j == 2) {
					if (gridElements[j - 1][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j - 1, i, currentPlayer);
						return;
					}
					else if (gridElements[j - 2][i]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
						changeGridElements(j - 2, i, currentPlayer);
						return;
					}
				}
			}
		}
	}

	//For Left Cross
	for (int i{ 0 }, j{ 0 }; i < TOTAL_BOX; i++, j++) {
		
		if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_AI) {
			if (j == 0) {
				if (gridElements[i + 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i + 1, j + 1, currentPlayer);
					return;
				}
				else if (gridElements[i + 2][j + 2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i + 2, j + 2, currentPlayer);
					return;
				}
			}
			else if (j == 1) {
				if (gridElements[i - 1][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, j - 1, currentPlayer);
					return;
				}
				else if (gridElements[i + 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i + 1, j + 1, currentPlayer);
					return;
				}
			}
			else if (j == 2) {
				if (gridElements[i - 1][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, j - 1, currentPlayer);
					return;
				}
				else if (gridElements[i - 2][j - 2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 2, j - 2, currentPlayer);
					return;
				}
			}
		}
	}

	//For Right Croos
	for (int i{ 0 }, j{ 2 }; i < TOTAL_BOX; i++, j--) {
		if (gridElements[i][j]->whoPlayedOnGrid == PlayersGrid::PG_AI) {
			if (i == 0) {
				if (gridElements[i + 1][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i + 1, j - 1, currentPlayer);
					return;
				}
				else if (gridElements[i + 2][j - 2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i + 2, j - 2, currentPlayer);
					return;
				}
			}
			else if (i == 1) {
				if (gridElements[i - 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, j + 1, currentPlayer);
					return;
				}
				else if (gridElements[i + 1][j - 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i + 1, j - 1, currentPlayer);
					return;
				}
			}
			else if (i == 2) {
				if (gridElements[i - 1][j + 1]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 1, j + 1, currentPlayer);
					return;
				}
				else if (gridElements[i - 2][j + 2]->whoPlayedOnGrid == PlayersGrid::PG_NONE) {
					changeGridElements(i - 2, j + 2, currentPlayer);
					return;
				}
			}
		}
	}
}

void Game::randomMove(Player* currentPlayer) {
	int x, y;

	do {
		x = rand() % TOTAL_BOX;
		y = rand() % TOTAL_BOX;
	} while (gridElements[x][y]->whoPlayedOnGrid != PlayersGrid::PG_NONE);

	changeGridElements(x, y, currentPlayer);
}

