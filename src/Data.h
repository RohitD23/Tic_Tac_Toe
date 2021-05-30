#pragma once
#include "Texture.h"

//Which screen to render
enum class Screen {
	MENU_SCREEN = 0,
	ROUND_SELECT,
	GAME_SCREEN,
	GAMEOVER_SCREEN,
	EXIT
};


//Who is playing
enum class PlayerType {
	PT_NONE = 0,
	PT_HUMAN,
	PT_AI
};

//Who has played on Grid
enum class PlayersGrid {
	PG_NONE = 0,
	PG_HUMAN,
	PG_AI
};

enum class AIStratergy {
	AS_NONE = 0,
	AS_ATTACK,
	AS_DEFENCE
};

struct Player {
	PlayerType playerType;   //Player is Human or AI
	PlayersGrid playersGrid; //Who played on the gridBox
	Texture	elementTexture;  //X or O image
};