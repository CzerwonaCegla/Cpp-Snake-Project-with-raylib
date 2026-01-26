#include "GameUtilFunctions.h"
#include <raylib.h>
#include "GlobalGameParameters.h"

void drawBackgroundGrid()
{
    Vector2 placementVector = { 0,0 };
    Texture backgroundTexture = LoadTexture("Textures\\GridTile.png");
    constexpr int xMult = globalGameWindowWidth / globalGridWidth;
    constexpr int yMult = globalGameWindowHeight / globalGridWidth;
    for (int i = 0; i < yMult; ++i)
    {
        for (int j = 0; j < xMult; ++j)
        {
            DrawTexture(backgroundTexture, placementVector.x, placementVector.y, WHITE);
            placementVector.x += globalGridWidth;
        }
        placementVector.x = 0;
        placementVector.y += globalGridWidth;
    }
}


void gameEndLose()
{

}


void gameEndWin()
{

}