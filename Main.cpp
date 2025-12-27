#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "GlobalGameParameters.h"
#include "RenderableObject.h"
#include "Snake.h"

using namespace std;

int main()
{
	string name = "Snake";
	SetTargetFPS(2);
	InitWindow(globalGameWindowWidth, globalGameWindowHeight, name.c_str());
	// DO NOT TOUCH CODE ABOVE FOR NOW


	Snake snake;
	// MAIN GAME LOOP
	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_SPACE))
		{
			snake.addSnakePart();
		}
		snake.moveSnake();

		// Draw start -------------------
		BeginDrawing();

		ClearBackground(DARKGREEN);
		snake.drawObject();

		EndDrawing();
		// Draw end ---------------------
	}


	CloseWindow();
	return 0;
}