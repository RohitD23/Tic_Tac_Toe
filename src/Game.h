#pragma once
#include <sstream>
#include "Texture.h"
#include "Button.h"
#include "Data.h"

struct GridElements {
	Texture* x_o_image;
	PlayersGrid whoPlayedOnGrid;
};


class Game {
public:
	~Game();

	void free();

	void loadMedia();

	void render();

	void handleEvent(SDL_Event* e,const Player* currentPlayer);

	bool isTextureLoaded();

	//Get what player played
	bool isButtonPressed(Player* currentPlayer);

	bool isGridFull();
	bool hasAnyoneWon();

	bool isPlayerWinning(Player* currentPlayer);
	bool isAIWinning(Player* currentPlayer);

	void aiAttackStartergy(Player* currentPlayer);
	void aiDefenceStratergy(Player* currentPlayer);
	void playerPlayedNearAI();

	int getAIMoveCount() { return aiMoveCount; }

	int getRoundsPlayed() { return roundsPlayed; }
	int getPlayerWinCount() { return playerWinCount; }
	int getaiWinCount() { return aiWinCount; }
	
private:
	//No. of Boxes on board
	const int static TOTAL_BOX = 3 ;


	//Board image
	Texture board;

	//Text on Score Board
	Texture scoreText[4];
	Texture currentRound;
	Texture playerScore;
	Texture aiScore;

	//Represents each box in board
	Button* gridBoxes[TOTAL_BOX][TOTAL_BOX];

	//To display X or O image
	GridElements* gridElements[TOTAL_BOX][TOTAL_BOX];

	//Score board
	Texture scoreBoard;

	int roundsPlayed;
	int playerWinCount;
	int aiWinCount;

	//For what Move number ai is on
	int aiMoveCount;
	//For where AI has Played
	std::pair <int, int> ai_move;
	bool hasPlayerPlayedNearAI;

	void loadGridBoxes();
	void renderGridBoxes();

	void loadScoreBoard();
	void loadCurrentRound();
	void loadPlayerScore();
	void loadAiScore();
	void renderScoreBoard();

	void loadGridElements();
	void renderGridElements();

	void changeGridElements(int x, int y, Player* currentPlayer);

	void aiFirstMove(Player* currentPlayer);
	void isCornerEmpty(Player* cuurentPlayer);
	void playNearFirstMove(Player* currentPlayer);
	void playNearMove(Player* currentPlayer);
	void randomMove(Player* currentPlayer);

	void cleanBoard();
};

