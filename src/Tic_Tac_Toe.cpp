#include "Window.h"
#include "MainMenu.h"
#include "Game.h"
#include "Data.h"
#include "RoundSelect.h"

Screen currentScreen = Screen::MENU_SCREEN;

Window GameWindow;

//To close SDL 
void close(Mix_Music* music);

//To load and play music
void loadMusic(Mix_Music* music, bool& isMusicPlaying);

//Check if button is pressed in Menu
void isMenuButtonPressed(MainMenu& menu, Mix_Music* music, bool& isMusicPlaying);

//Check if player played
void hasPlayerPlayed(Game& game, Player** currentPlayer, Player** otherPlayer, AIStratergy& stratergy);
//Get what A.I played
void GetAIMove(Game& game, Player* currentPlayer, AIStratergy& stratergy);

//Initialize data of players
void initializePlayers(Player* player1, Player* player2);
//Switch player after their turn
void switchPlayers(Player** currentPlayer, Player** otherPlayer);

void PlayGame() {

	srand(time(NULL));

	//Initialize Game Window and Renderer
	GameWindow.init();

	MainMenu menu;
	Game game;
	RoundSelect roundSelect;

	//Create Player
	Player player1;
	Player player2;

	//To decide how AI plays
	AIStratergy stratergy = AIStratergy::AS_NONE;

	initializePlayers(&player1, &player2);

	Player* currentPlayer;
	Player* otherPlayer;

	//Decide who goes first
	if (rand() % 2 != 0) {
		currentPlayer = &player1;
		otherPlayer = &player2;

		stratergy = AIStratergy::AS_DEFENCE;
	}
	else {
		currentPlayer = &player2;
		otherPlayer = &player1;

		stratergy = AIStratergy::AS_ATTACK;
	}

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

				//Check if round select is loaded or not
				if (!roundSelect.isTextureLoaded())
					roundSelect.loadMedia();

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

				//Check if game is loaded or not
				if (!game.isTextureLoaded())
					game.loadMedia();

				hasPlayerPlayed(game, &currentPlayer, &otherPlayer, stratergy);

				//Render game
				game.render();

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

void hasPlayerPlayed(Game& game, Player** currentPlayer, Player** otherPlayer, AIStratergy& stratergy) {

	//If it's players chance
	if ((*currentPlayer)->playerType == PlayerType::PT_HUMAN) {
		//Check if player played
		if (game.isButtonPressed(*currentPlayer))
			switchPlayers(currentPlayer, otherPlayer);
		
		//Check if player played near AI
		if (game.getAIMoveCount() == 1)
			game.playerPlayedNearAI();
	}
	//If it's AI chance
	else {
		GetAIMove(game, *currentPlayer, stratergy);
		switchPlayers(currentPlayer, otherPlayer);
	}
}

void GetAIMove(Game& game,Player* currentPlayer, AIStratergy& stratergy) {

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