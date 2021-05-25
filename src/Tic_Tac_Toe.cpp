#include "Window.h"
#include "MainMenu.h"
#include "Game.h"
#include "Data.h"

Screen currentScreen = Screen::MENU_SCREEN;

Window GameWindow;

//To close SDL 
void close(Mix_Music* music);

//To load and play music
void loadMusic(Mix_Music* music, bool& isMusicPlaying);

//Check if button is pressed in Menu
void checkMenuButtonPressed(MainMenu& menu, Mix_Music* music, bool& isMusicPlaying);

//Check if player played
void checkPlayerPlayed(Game& game, Player** currentPlayer, Player** otherPlayer);

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

	//Create Player
	Player player1;
	Player player2;

	initializePlayers(&player1, &player2);

	Player* currentPlayer;
	Player* otherPlayer;

	//Decide who goes first
	if (rand() % 2 != 0) {
		currentPlayer = &player1;
		otherPlayer = &player2;
	}
	else {
		currentPlayer = &player2;
		otherPlayer = &player1;
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

			else if (currentScreen == Screen::GAME_SCREEN) {
				//Game events
				game.handleEvent(&e, currentPlayer);
			}
		}

		//If game window is minimized then do not render game
		if (!GameWindow.Get_Minimized()) {
			
			if (currentScreen == Screen::MENU_SCREEN) {

				//Freeing memory as we are not in game
				if(game.checkTextureLoaded())
					game.free();

				//Check if media is loaded or not
				if (!menu.checkTextureLoaded())
					menu.load_media();

				checkMenuButtonPressed(menu, music, isMusicPlaying);

				//Render menu
				menu.render();
			}

			else if (currentScreen == Screen::EXIT)
				break;

			else if (currentScreen == Screen::GAME_SCREEN) {
				//Freeing the memory as we are not on menu screen
				if(menu.checkTextureLoaded())
					menu.free();

				//Check if game is loaded or not
				if (!game.checkTextureLoaded())
					game.loadMedia();

				checkPlayerPlayed(game, &currentPlayer, &otherPlayer);

				//Render game
				game.render();

			}
		}


	}

	close(music);
}

void loadMusic(Mix_Music* music, bool& isMusicPlaying) {
	//Load music
	music = Mix_LoadMUS("assets/Audio/BackgroundMusic.wav");
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

void checkMenuButtonPressed(MainMenu& menu, Mix_Music* music, bool& isMusicPlaying) {

	//TO load game screen
	if (menu.checkPlayButtonPressed()) {
		currentScreen = Screen::GAME_SCREEN;
		menu.setPlayButton(false);
	}

	//To set sound on or off
	else if (menu.checkSoundButtonPressed()) {

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
	else if (menu.checkExitButtonPressed())
		currentScreen = Screen::EXIT;

}

void initializePlayers(Player* player1, Player* player2) {
	
	player1->playerType = PlayerType::PT_HUMAN;
	player2->playerType = PlayerType::PT_AI;

	if (rand() % 2 == 0) {
		player1->elementType = 'X';
		player2->elementType = 'O';

		player1->elementTexture.load_media_from_file("assets/Sprites/X.png");
		player2->elementTexture.load_media_from_file("assets/Sprites/O.png");

	}
	else {
		player1->elementType = 'O';
		player2->elementType = 'X';

		player1->elementTexture.load_media_from_file("assets/Sprites/O.png");
		player2->elementTexture.load_media_from_file("assets/Sprites/X.png");
	}
}

void checkPlayerPlayed(Game& game, Player** currentPlayer, Player** otherPlayer) {

	if (game.checkButtonPressed(*currentPlayer))
		switchPlayers(currentPlayer, otherPlayer);
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