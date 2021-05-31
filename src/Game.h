#pragma once
#include <sstream>
#include "Texture.h"
#include "Button.h"
#include "Data.h"

struct GridElements {
	Texture* x_o_image;
	PlayersGrid whoPlayedOnGrid;
};

enum class GridAlignment
{
	GA_NONE = 0,
	GA_HORIZONTAL,
	GA_VERTICAL,
	GA_LEFTCROSS,
	GA_RIGHTCROSS
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

	int getCurrentRound() const { return currentRound; }
	int getPlayerWinCount() const  { return playerWinCount; }
	int getaiWinCount() const { return aiWinCount; }
	
private:
	//No. of Boxes on board
	const int static TOTAL_BOX = 3 ;


	//Board image
	Texture board;

	//Text on Score Board
	Texture scoreText[4];
	Texture roundsPlayed;
	Texture playerScore;
	Texture aiScore;

	//Represents each box in board
	Button* gridBoxes[TOTAL_BOX][TOTAL_BOX];

	//To display X or O image
	GridElements* gridElements[TOTAL_BOX][TOTAL_BOX];

	//Score board
	Texture scoreBoard;

	int currentRound;
	int playerWinCount;
	int aiWinCount;

	//For what Move number ai is on
	int aiMoveCount;
	//For where AI has Played
	std::pair <int, int> ai_move;
	bool hasPlayerPlayedNearAI;

	//To check if someone has won
	bool isRoundOver;
	//To color grid where someone has won
	SDL_Rect colorGrid[3];
	//To color in which direction 
	GridAlignment gridAlignment;

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
	void randomMove(Player* currentPlayer);

	void cleanBoard();

	//Set Position of colorGrid where to color grid
	void setColorGridLoaction(int x);
};

