#pragma once
#include "Texture.h"

//Which screen to render
enum class Screen {
	MENU_SCREEN = 0,
	GAME_SCREEN,
	EXIT
};

enum class PlayerType {
	PT_HUMAN = 0,
	PT_AI
};

struct Player {
	PlayerType playerType;  //Player is Human or AI
	char elementType;       //X or O
	Texture	elementTexture; //X or O image
};