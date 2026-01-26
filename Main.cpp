#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "GlobalGameParameters.h"
#include "RenderableObject.h"
#include "Snake.h"
#include "Apple.h"

#include "GameUtilFunctions.h"

using namespace std;

int main()
{
	string name = "Snake";
	constexpr int targetFps = 120;
	SetTargetFPS(targetFps);
	InitWindow(globalGameWindowWidth, globalGameWindowHeight, name.c_str());
	// DO NOT TOUCH CODE ABOVE FOR NOW

	Apple apple;
	Snake snake;
	// Only here for the rare occasion if starting apple spawns directly inside the snake
	while (snake.checkIfCoordsAreInSnake(apple.getCoordinates()))
	{
		apple.setNewCoordinates();
	}

	constexpr int framesPerMove = (targetFps / 3);
	int currentFrame = 1;

	//Texture2D temp = LoadTexture("Textures\\SnakeHead.png");
	// 
	// MAIN GAME LOOP
	Vector2 currentMove = { 0.0, 0.0 };
	while (!WindowShouldClose())
	{
		currentMove = snake.getTargetVectorFromInput();
		// Check for apple and snake collision
		Vector2 gameAppleCoords = apple.getCoordinates();
		if(snake.checkIfCoordsAreInSnake(apple.getCoordinates()))
		{
			snake.addSnakePart();
			while (snake.checkIfCoordsAreInSnake(apple.getCoordinates()))
			{
				apple.setNewCoordinates();
			}
		}

		// To be removed later when testing is done
		/*if (IsKeyDown(KEY_SPACE))
		{
			snake.addSnakePart();
		}*/


		// Draw start -------------------
		BeginDrawing();

		ClearBackground(DARKGREEN);
		drawBackgroundGrid();
		apple.drawObject();
		snake.drawObject();
		//DrawTextureEx(temp, { 400,400 }, 180, 1, WHITE);
		switch (state)
		{
			case gameWinState::Lose:
    		DrawText("You Lose!", (int)(globalGameWindowWidth * (2.0 / 5.0)), (int)(globalGameWindowHeight * (2.0 / 5.0)), 50, WHITE);
    		break;
			case gameWinState::Win:
    		DrawText("You Win!", (int)(globalGameWindowWidth * (2.0 / 5.0)), (int)(globalGameWindowHeight * (2.0 / 5.0)), 50, WHITE);
    		break;
		}
		EndDrawing();
		// Draw end ---------------------
		if ((currentFrame % framesPerMove) == 0)
		{
			snake.moveSnake(currentMove);
			currentFrame = 1;
		}
		else
		{
			++currentFrame;
		}
	}


	CloseWindow();
	return 0;
}