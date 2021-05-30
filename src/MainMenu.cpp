#include "MainMenu.h"

MainMenu::~MainMenu() { 
	free(); 
}

void MainMenu::free() {
	title.free();

	play.free();
	sound.free();
	exit.free();
}

void MainMenu::load_media() {
	 
	//Load Font file
	*GameWindow.Get_Font() = TTF_OpenFont("assets/Font/Cocogoose.ttf", 90);

	//Load title text
	title.loadFromRenderedText("Tic Tac Toe", { 255, 150, 0, 255 }, 1000);

	load_buttons();

}

void MainMenu::load_buttons() {
	
	//Load Play Button media
	play.load_button_media("Play", 60, { 255,255,255 });
	
	play.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	play.set_button_dimensions(play.get_Width(), play.get_Height());
	
	play.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	play.setColorOnMouseDown({ 0, 135, 175, 255 }, { 255, 50, 0, 255 });
	play.setColorOnMouseUp({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });

	//Load Sound Button media
	sound.load_button_media("Sound : Off", 60, { 255, 255, 255, 255 });

	sound.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	sound.set_button_dimensions(sound.get_Width(), sound.get_Height());

	sound.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	sound.setColorOnMouseDown({ 0, 135, 175, 255 }, { 255, 50, 0, 255 });
	sound.setColorOnMouseUp({ 0, 135, 175, 255 }, { 255, 80, 0, 255 });

	// Load Exit Button media
    exit.load_button_media("Exit", 60, { 255,255,255 });

	exit.setDefaultColor({ 0, 135, 175, 255 }, { 255, 255, 255, 255 });
	exit.set_button_dimensions(exit.get_Width(), exit.get_Height());

	exit.setColorOnHover({ 0, 135, 175, 255 }, { 255, 110, 0, 255 });
	exit.setColorOnMouseDown({ 0, 135, 175, 255 }, {255, 50, 0, 255});
	exit.setColorOnMouseUp({ 0, 135, 175, 255 }, {255, 110, 0, 255});
}

void MainMenu::render() {

	//Set color of window
	SDL_SetRenderDrawColor(GameWindow.Get_Renderer(), 0, 135, 175, 255);
	//Render whole window with set color
	SDL_RenderClear(GameWindow.Get_Renderer());

	//Render title text
	title.renderTexture(nullptr, WINDOW_WIDTH - 280, WINDOW_HEIGHT - 300);

	//Render play button
	play.render(WINDOW_WIDTH - 75, WINDOW_HEIGHT - 90);
	//Render sound button
	sound.render(WINDOW_WIDTH - 180, WINDOW_HEIGHT );
	//Render exit button
	exit.render(WINDOW_WIDTH - 70, WINDOW_HEIGHT + 90);

	//Update window
	SDL_RenderPresent(GameWindow.Get_Renderer());
}

void MainMenu::handleEvent(SDL_Event* e) {
	play.handleEvent(e);
	sound.handleEvent(e);
	exit.handleEvent(e);
}

void MainMenu::changeSoundText(std::string text) {
	sound.load_button_media(text, 60, { 255, 255, 255, 255 });
}

bool MainMenu::isTextureLoaded() {

	if (title.Get_Texture() == nullptr)
		return false;
	else
		return true;
}