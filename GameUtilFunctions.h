#ifndef H_GAME_UTIL_FUNCTIONS
#define H_GAME_UTIL_FUNCTIONS
#include <raylib.h>
class GameUtils
{
	Texture2D backgroundTexture;
public:
	GameUtils();
	void drawBackgroundGrid();
	void gameEnd();
};

#endif // !H_GAME_UTIL_FUNCTIONS
