#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "GlobalGameParameters.h"
#include "RenderableObject.h"
#include "Snake.h"
#include "Apple.h"
#include "GameState.h"

#include "GameUtilFunctions.h"

using namespace std;

int main()
{
	constexpr int maxApplesCollected = ((globalGameWindowWidth / globalGridWidth) * (globalGameWindowHeight / globalGridWidth)) - 1;
	//enum class gameWinState { None, Win, Lose };
	gameWinState state = gameWinState::None;
	string name = "Snake";
	constexpr int targetFps = 120;
	SetTargetFPS(targetFps);
	InitWindow(globalGameWindowWidth, globalGameWindowHeight, name.c_str());
	GameUtils utils;
	// DO NOT TOUCH CODE ABOVE FOR NOW

	Apple apple;
	Snake snake;
	// Only here for the rare occasion if starting apple spawns directly inside the snake
	while (snake.checkIfCoordsAreInSnake(apple.getCoordinates()))
	{
		apple.setNewCoordinates();
	}
	snake.getGameStatePtr(&state);
	constexpr int framesPerMove = (targetFps / 2);
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
		if (snake.getApplesCollected() == maxApplesCollected)
		{
			state = gameWinState::Win;
		}
		if(snake.checkIfCoordsAreInSnake(apple.getCoordinates()))
		{
			snake.addSnakePart();
			if (snake.getApplesCollected() == maxApplesCollected)
			{
				state = gameWinState::Win;
			}
			if (state == gameWinState::None)
			{
				while (snake.checkIfCoordsAreInSnake(apple.getCoordinates()))
				{
					apple.setNewCoordinates();
				}
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
		utils.drawBackgroundGrid();

		apple.drawObject();
		snake.drawObject();
		//DrawTextureEx(temp, { 400,400 }, 180, 1, WHITE);
		switch (state)
		{
		case gameWinState::Lose:
    		DrawText("You Lose!", (int)(globalGameWindowWidth * (2.0 / 5.0)), (int)(globalGameWindowHeight * (2.0 / 5.0)), 50, WHITE);
			std::cerr << "YOU LOSE";
    		break;
		case gameWinState::Win:
    		DrawText("You Win!", (int)(globalGameWindowWidth * (2.0 / 5.0)), (int)(globalGameWindowHeight * (2.0 / 5.0)), 50, WHITE);
			std::cerr << "YOU WIN";
    		break;
		}
		EndDrawing();
		// Draw end ---------------------
		if (state != gameWinState::None)
		{
			utils.gameEnd();
		}
		else
		{
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
	}


	CloseWindow();
	return 0;
}