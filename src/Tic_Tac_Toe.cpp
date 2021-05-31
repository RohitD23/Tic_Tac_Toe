#include <sstream>
#include "Window.h"
#include "MainMenu.h"
#include "Game.h"
#include "Data.h"
#include "RoundSelect.h"
#include "GameOver.h"

Screen currentScreen = Screen::MENU_SCREEN;

Window GameWindow;

//To close SDL 
void close(Mix_Music* music);

//Initialize data of players
void initializePlayers(Player* player1, Player* player2);
//Switch player after their turn
void switchPlayers(Player** currentPlayer, Player** otherPlayer);
//Decide who goes first
void selectPlayersChance(Player** currentPlayer, Player** otherPlayer, Player* player1, Player* player2, AIStratergy& stratergy);

//To load and play music
void loadMusic(Mix_Music* music, bool& isMusicPlaying);

//Check if button is pressed in Menu
void isMenuButtonPressed(MainMenu& menu, Mix_Music* music, bool& isMusicPlaying);

//Check if button is pressed in RoundSelect
void isRoundSelectButtonPreesed(RoundSelect& roundSelect, int& totalRounds);

//Check if button is pressed in GameOver
bool isGameOverButtonPressed(const GameOver& gameOver, Game& game);

//Check if player played
void hasPlayerPlayed(Game& game, Player** currentPlayer, Player** otherPlayer, AIStratergy& stratergy, int totalRounds);
//Get what A.I played
void GetAIMove(Game& game, Player* currentPlayer, AIStratergy stratergy);

//Check if Game is Over 
bool isGameOver(Game& game, int& totalRounds);

void PlayGame() {

	srand(time(NULL));

	//Initialize Game Window and Renderer
	GameWindow.init();

	MainMenu menu;
	Game game;
	RoundSelect roundSelect;
	GameOver gameOver;

	//Create Player
	Player player1;
	Player player2;

	//To decide how AI plays
	AIStratergy stratergy = AIStratergy::AS_NONE;

	initializePlayers(&player1, &player2);

	Player* currentPlayer;
	Player* otherPlayer;

	//Number of rounds to play
	int totalRounds = 5;

	selectPlayersChance(&currentPlayer, &otherPlayer, &player1, &player2, stratergy);

	//For music
	Mix_Music* music = nullptr;
	//To check if music is playing
	bool isMusicPlaying;

	loadMusic(music, isMusicPlaying);

	//To save the events from player
	SDL_Event e;
	bool quit = false;

	//Main Loop 
	while (!quit) {

		//Take events from player and process while the event stack not gets empty
		while (SDL_PollEvent(&e) != 0) {

			//To close game
			if (e.type == SDL_QUIT || currentScreen == Screen::EXIT)
				quit = true;

			//Window events
			GameWindow.handle_event(&e);

			if (currentScreen == Screen::MENU_SCREEN) {
				//Menu events
				menu.handleEvent(&e);
			}

			else if (currentScreen == Screen::ROUND_SELECT) {
				//Select Number of rounds
				roundSelect.handleEvent(&e);
			}

			else if (currentScreen == Screen::GAME_SCREEN) {
				//Game events
				game.handleEvent(&e, currentPlayer);
			}

			else if (currentScreen == Screen::GAMEOVER_SCREEN) {
				//GameOver events
				gameOver.handleEvent(&e);
			}
		}

		//If game window is minimized then do not render game
		if (!GameWindow.Get_Minimized()) {
			
			if (currentScreen == Screen::MENU_SCREEN) {

				//Freeing memory as we are not in game
				if(game.isTextureLoaded())
					game.free();

				//Freeing memory as we are not in round select screen
				if (roundSelect.isTextureLoaded())
					roundSelect.free();

				//Freeing memory as we are not in game over
				if (gameOver.isTextureLoaded())
					gameOver.free();

				//Check if media is loaded or not
				if (!menu.isTextureLoaded())
					menu.load_media();

				isMenuButtonPressed(menu, music, isMusicPlaying);

				//Render menu
				menu.render();
			}

			else if (currentScreen == Screen::EXIT)
				break;

			else if (currentScreen == Screen::ROUND_SELECT) {

				//Freeing memory as we are not in game
				if (game.isTextureLoaded())
					game.free();

				//Freeing the memory as we are not on menu screen
				if (menu.isTextureLoaded())
					menu.free();

				//Freeing memory as we are not in game over
				if (gameOver.isTextureLoaded())
					gameOver.free();

				//Check if round select is loaded or not
				if (!roundSelect.isTextureLoaded())
					roundSelect.loadMedia();

				isRoundSelectButtonPreesed(roundSelect, totalRounds);

				//Render round select
				roundSelect.render();
			}

			else if (currentScreen == Screen::GAME_SCREEN) {
				//Freeing the memory as we are not on menu screen
				if(menu.isTextureLoaded())
					menu.free();

				//Freeing memory as we are not in round select screen
				if (roundSelect.isTextureLoaded())
					roundSelect.free();

				//Freeing memory as we are not in game over
				if (gameOver.isTextureLoaded())
					gameOver.free();

				//Check if game is loaded or not
				if (!game.isTextureLoaded())
					game.loadMedia();

				//Render game
				game.render();

				hasPlayerPlayed(game, &currentPlayer, &otherPlayer, stratergy, totalRounds);
			}

			else if (currentScreen == Screen::GAMEOVER_SCREEN) {
				//Freeing the memory as we are not on menu screen
				if (menu.isTextureLoaded())
					menu.free();

				//Freeing memory as we are not in round select screen
				if (roundSelect.isTextureLoaded())
					roundSelect.free();

				//Check if game over is loaded or not
				if (!gameOver.isTextureLoaded())
					gameOver.loadMedia(game);

				if (isGameOverButtonPressed(gameOver, game)) {
					selectPlayersChance(&currentPlayer, &otherPlayer, &player1, &player2, stratergy);
					totalRounds = 5;
				}

				gameOver.render();
			}
		}


	}

	currentPlayer = nullptr;
	otherPlayer = nullptr;

	close(music);
}

void loadMusic(Mix_Music* music, bool& isMusicPlaying) {
	//Load music
	music = Mix_LoadMUS("assets/Audio/BackgroundMusic.mp3");
	try {
		if (music == nullptr)
			throw (std::string("Failed to load beat music! SDL_mixer Error: ") + std::string(Mix_GetError()));
	}
	catch (std::string& ex) {
		std::cout << ex << std::endl;
	}

	//Play the music
	Mix_PlayMusic(music, -1);
	isMusicPlaying = true;
}

void isMenuButtonPressed(MainMenu& menu, Mix_Music* music, bool& isMusicPlaying) {

	//TO load game screen
	if (menu.isPlayButtonPressed()) {
		currentScreen = Screen::ROUND_SELECT;
		menu.setPlayButton(false);
	}

	//To set sound on or off
	else if (menu.isSoundButtonPressed()) {

		if (isMusicPlaying == true) {
	        
			//Stop the music
			Mix_HaltMusic();
			isMusicPlaying = false;
			menu.changeSoundText("Sound : On");
		}
		else {
			//Play the music
			Mix_PlayMusic(music, -1);
			isMusicPlaying = true;
			menu.changeSoundText("Sound : Off");
		}

		menu.setSoundButton(false);
	}

	//To close game
	else if (menu.isExitButtonPressed())
		currentScreen = Screen::EXIT;

}

void isRoundSelectButtonPreesed(RoundSelect& roundSelect, int& totalRounds) {

	std::stringstream ss;

	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/NunitoSans.ttf", 90);

	if (roundSelect.isDecreaseNumberPressed()) {
		roundSelect.setDecreaseNumberPressed(false);
		if (totalRounds != 5) {
			totalRounds -= 5;

			if (totalRounds == 5) {
				ss << "0" << totalRounds;
			}
			else
				ss << totalRounds;

			roundSelect.getNumberText()->loadFromRenderedText(ss.str(), { 255, 255, 255, 255 }, 600);
		}
	}
	else if (roundSelect.isIncreaseNumberPressed()) {
		roundSelect.setIncreaseNumberPressed(false);
		if (totalRounds != 15) {
			totalRounds += 5;
			ss << totalRounds;
			roundSelect.getNumberText()->loadFromRenderedText(ss.str(), { 255, 255, 255, 255 }, 600);
		}
	}
	else if (roundSelect.isStartGamePressed())
		currentScreen = Screen::GAME_SCREEN;
}

bool isGameOverButtonPressed(const GameOver& gameOver, Game& game) {

	if (gameOver.isPlayAgainButtonPressed()) {
		currentScreen = Screen::ROUND_SELECT;
		game.free();
		return true;
	}
	else if (gameOver.isExitButtonPressed()) {
		currentScreen = Screen::EXIT;
		return false;
	}

	return false;
}

void initializePlayers(Player* player1, Player* player2) {
	
	player1->playerType = PlayerType::PT_HUMAN;
	player2->playerType = PlayerType::PT_AI;

	player1->playersGrid = PlayersGrid::PG_HUMAN;
	player2->playersGrid = PlayersGrid::PG_AI;

	if (rand() % 2 == 0) {
		player1->elementTexture.load_media_from_file("assets/Sprites/X.png");
		player2->elementTexture.load_media_from_file("assets/Sprites/O.png");
	}
	else {
		player1->elementTexture.load_media_from_file("assets/Sprites/O.png");
		player2->elementTexture.load_media_from_file("assets/Sprites/X.png");
	}
}

void selectPlayersChance(Player** currentPlayer, Player** otherPlayer, Player* player1, Player* player2, AIStratergy& stratergy) {
	//Decide who goes first
	if (rand() % 2 != 0) {
		*currentPlayer = player1;
		*otherPlayer = player2;

		stratergy = AIStratergy::AS_DEFENCE;
	}
	else {
		*currentPlayer = player2;
		*otherPlayer = player1;

		stratergy = AIStratergy::AS_ATTACK;
	}
}

void hasPlayerPlayed(Game& game, Player** currentPlayer, Player** otherPlayer, AIStratergy& stratergy, int totalRounds) {

	if (isGameOver(game, totalRounds)) {
		if ((*currentPlayer)->playerType == PlayerType::PT_AI)
			stratergy = AIStratergy::AS_ATTACK;
		else
			stratergy = AIStratergy::AS_DEFENCE;
	}
	//If it's players chance
	else if ((*currentPlayer)->playerType == PlayerType::PT_HUMAN) {
		//Check if player played
		if (game.isButtonPressed(*currentPlayer))
			switchPlayers(currentPlayer, otherPlayer);
		
		//Check if player played near AI
		if (game.getAIMoveCount() == 1)
			game.playerPlayedNearAI();
	}
	//If it's AI chance
	else {
		SDL_Delay(750);
		GetAIMove(game, *currentPlayer, stratergy);
		switchPlayers(currentPlayer, otherPlayer);
	}
}

void GetAIMove(Game& game,Player* currentPlayer, AIStratergy stratergy) {

	if (game.isAIWinning(currentPlayer))
		return;
	else if (game.isPlayerWinning(currentPlayer))
		return;
	else if (stratergy == AIStratergy::AS_ATTACK)
		game.aiAttackStartergy(currentPlayer);
	else if (stratergy == AIStratergy::AS_DEFENCE)
		game.aiDefenceStratergy(currentPlayer);
}

void switchPlayers(Player** currentPlayer, Player** otherPlayer)
{
	Player* temp = *currentPlayer;
	*currentPlayer = *otherPlayer;
	*otherPlayer = temp;
}

bool isGameOver(Game& game, int& totalRounds) {

	if (game.getCurrentRound() > totalRounds) {
		currentScreen = Screen::GAMEOVER_SCREEN;
		totalRounds = 5;
		return true;
	}
	else if (game.hasAnyoneWon())
		return true;
	else if (game.isGridFull())
		return true;

	return false;
}

void close(Mix_Music* music) {

	//Free the music
	Mix_FreeMusic(music);
	music = nullptr;

	GameWindow.free();

	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}