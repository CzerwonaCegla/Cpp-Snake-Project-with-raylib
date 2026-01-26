#include "GameUtilFunctions.h"
#include <raylib.h>
#include <cstdlib>
#include "GlobalGameParameters.h"

GameUtils::GameUtils()
{
    backgroundTexture = LoadTexture("Textures\\GridTile.png");
}


void GameUtils::drawBackgroundGrid()
{
    Vector2 placementVector = { 0,0 };
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


void GameUtils::gameEnd()
{
    WaitTime(2.0);
    CloseWindow();
    exit(0);
}