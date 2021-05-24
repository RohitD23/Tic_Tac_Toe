#include "Window.h"
#include "MainMenu.h"
#include "Game.h"

//Which screen to render
enum class Screen {
	MENU_SCREEN = 0,
	GAME_SCREEN,
	EXIT
};

Screen currentScreen = Screen::MENU_SCREEN;

Window GameWindow;

//For music
Mix_Music* music = nullptr;

//To check if music is playing
bool isMusicPlaying;

//To close SDL 
void close();

//To load and play music
void loadMusic();

//Check if button is pressed in Menu
void checkMenuButtonPressed(MainMenu& menu);

void PlayGame() {

	//Initialize Game Window and Renderer
	GameWindow.init();

	loadMusic();

	MainMenu menu;
	Game game;

	bool quit = false;

	//To save the events from player
	SDL_Event e;

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

		}

		//If game window is minimized then do not render game
		if (!GameWindow.Get_Minimized()) {
			
			if (currentScreen == Screen::MENU_SCREEN) {

				//Freeing memory as we are not in game
				game.free();

				//Check if media is loaded or not
				if (!menu.checkTextureLoaded())
					menu.load_media();

				checkMenuButtonPressed(menu);

				//Render menu
				menu.render();
			}

			else if (currentScreen == Screen::EXIT)
				break;

			else if (currentScreen == Screen::GAME_SCREEN) {
				//Freeing the memory as we are not on menu screen
				menu.free();

				//Check if game is loaded or not
				if (!game.checkTextureLoaded())
					game.loadMedia();

				//Render game
				game.render();
			}
		}


	}

	close();
}

void loadMusic() {
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

void checkMenuButtonPressed(MainMenu& menu) {

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

void close() {

	//Free the music
	Mix_FreeMusic(music);
	music = nullptr;

	GameWindow.free();

	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

