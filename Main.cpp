#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <iostream>

#define GRID_WIDTH 50
#define SNAKE_WINDOW_WIDTH 1300
#define SNAKE_WINDOW_HEIGHT 800

using namespace std;

class Snake
{
	vector<Vector2> snakePartsCoords;
	Vector2 targetVector;
	Vector2 previouslyAddedToTargetVector;
	Vector2 tailSpawnPos;

	// Reads input and 
	Vector2 getTargetVectorFromInput()
	{
		Vector2 localTargetVector = { 0,0 };
		if (IsKeyDown(KEY_UP)) { localTargetVector.y -= GRID_WIDTH;}
		else if (IsKeyDown(KEY_DOWN)) { localTargetVector.y += GRID_WIDTH; }
		else if (IsKeyDown(KEY_RIGHT)) { localTargetVector.x += GRID_WIDTH; }
		else if (IsKeyDown(KEY_LEFT)) { localTargetVector.x -= GRID_WIDTH; }
		if (localTargetVector.x != 0.0 || localTargetVector.y != 0.0)
		{
			previouslyAddedToTargetVector = localTargetVector;
		}
		return localTargetVector;
	}

	bool checkIfInBorders(const Vector2& tempTarget)
	{
		if ((tempTarget.x + targetVector.x) < 0.0 ||
			(tempTarget.x + targetVector.x) > (float)(SNAKE_WINDOW_WIDTH - GRID_WIDTH)) // Check if out of bounds on right or left
		{
			return false;
		}
		else if ((tempTarget.y + targetVector.y) < 0.0 ||
			(tempTarget.y + targetVector.y) > (float)(SNAKE_WINDOW_HEIGHT - GRID_WIDTH)) // Check if above/below top border and bottom border
		{
			return false;
		}
		else
		{
			return true;
		}
	}

public:
	Snake()
	{
		Vector2 initialSnakePos = { 0,0 };
		snakePartsCoords.push_back(initialSnakePos);
		targetVector = initialSnakePos;
		previouslyAddedToTargetVector = { 0,0 };
		tailSpawnPos = initialSnakePos;
	}
	
	Snake(Vector2 startingPosVector)
	{
		Vector2 initialSnakePos = startingPosVector;
		snakePartsCoords.push_back(initialSnakePos);
		targetVector = initialSnakePos;
		previouslyAddedToTargetVector = { 0,0 };
		tailSpawnPos = initialSnakePos;
	}

	int getApplesCollected()
	{
		return (snakePartsCoords.size() - 1);
	}

	void addSnakePart()
	{

	}

	void moveSnake()
	{
		Vector2 tempTarget = getTargetVectorFromInput();
		if (tempTarget.x == 0.0 && tempTarget.y == 0)
		{
			tempTarget = previouslyAddedToTargetVector;
		}
		if (checkIfInBorders(tempTarget))
		{
			targetVector += tempTarget;
		}
		else
		{
			exit(0);
		}
		
		for(int i = (snakePartsCoords.size() - 1); i >= 0; --i)
		{
			// If iter is snake's head then set it to target vector
			// Else set part to vector of the part closer to the snake's head
			if (i == snakePartsCoords.size() - 1) { tailSpawnPos = snakePartsCoords[i]; }
			if (i==0)
			{
				snakePartsCoords[0] = targetVector;
			}
			else
			{
				snakePartsCoords[i] = snakePartsCoords[i - 1];
			}
		}
	}

	// Loops through all elements in vector and draws them
	void drawSnake()
	{
		for (const auto part : snakePartsCoords)
		{
			DrawRectangle(part.x, part.y, GRID_WIDTH, GRID_WIDTH, BLUE);
		}
	}
};

int main()
{
	std::string name = "Snake";
	const int gridWidth = GRID_WIDTH;
	SetTargetFPS(1);
	InitWindow(SNAKE_WINDOW_WIDTH, SNAKE_WINDOW_HEIGHT, name.c_str());
	// DO NOT TOUCH CODE ABOVE FOR NOW


	Snake snake;
	// MAIN GAME LOOP
	while (!WindowShouldClose())
	{
		snake.moveSnake();

		// Draw start -------------------
		BeginDrawing();

		ClearBackground(DARKGREEN);
		snake.drawSnake();

		EndDrawing();
		// Draw end ---------------------
	}


	CloseWindow();
	return 0;
}