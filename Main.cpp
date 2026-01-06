#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "GlobalGameParameters.h"
#include "RenderableObject.h"
#include "Snake.h"
#include "Apple.h"

using namespace std;

int main()
{
	string name = "Snake";
	SetTargetFPS(2);
	InitWindow(globalGameWindowWidth, globalGameWindowHeight, name.c_str());
	// DO NOT TOUCH CODE ABOVE FOR NOW

	Apple apple;
	Snake snake;
	// Only here for the rare occasion if starting apple spawns directly inside the snake
	while (snake.checkIfCoordsAreInSnake(apple.getCoordinates()))
	{
		apple.setNewCoordinates();
	}
	Texture2D temp = LoadTexture("Textures\\SnakeHead.png");
	// MAIN GAME LOOP
	while (!WindowShouldClose())
	{
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

		snake.moveSnake();
		// Draw start -------------------
		BeginDrawing();

		ClearBackground(DARKGREEN);
		/*snake.drawObject();
		apple.drawObject();*/
		DrawTextureEx(temp, { 400,400 }, 180, 1, WHITE);
		EndDrawing();
		// Draw end ---------------------
	}


	CloseWindow();
	return 0;
}