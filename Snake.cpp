#include "Snake.h"


// Reads input and returns target vector
Vector2 Snake::getTargetVectorFromInput()
{
	Vector2 localTargetVector = { 0,0 };
	if (IsKeyDown(KEY_UP)) { localTargetVector.y -= globalGridWidth; }
	else if (IsKeyDown(KEY_DOWN)) { localTargetVector.y += globalGridWidth; }
	else if (IsKeyDown(KEY_RIGHT)) { localTargetVector.x += globalGridWidth; }
	else if (IsKeyDown(KEY_LEFT)) { localTargetVector.x -= globalGridWidth; }
	if (localTargetVector.x != 0.0 || localTargetVector.y != 0.0)
	{
		previouslyAddedToTargetVector = localTargetVector;
	}
	return localTargetVector;
}

// Checks if target vector is fully in window
bool Snake::checkIfInBorders(const Vector2& tempTarget)
{
	if ((tempTarget.x + targetVector.x) < 0.0 ||
		(tempTarget.x + targetVector.x) > (float)(globalGameWindowWidth - globalGridWidth)) // Check if out of bounds on right or left
	{
		return false;
	}
	else if ((tempTarget.y + targetVector.y) < 0.0 ||
		(tempTarget.y + targetVector.y) > (float)(globalGameWindowHeight - globalGridWidth)) // Check if above/below top border and bottom border
	{
		return false;
	}
	else
	{
		return true;
	}
}

Snake::Snake()
{
	Vector2 initialSnakePos = { 0,0 };
	snakePartsCoords.push_back(initialSnakePos);
	targetVector = initialSnakePos;
	previouslyAddedToTargetVector = { 0,0 };
	tailSpawnPos = initialSnakePos;
}

Snake::Snake(Vector2 startingPosVector)
{
	Vector2 initialSnakePos = startingPosVector;
	snakePartsCoords.push_back(initialSnakePos);
	targetVector = initialSnakePos;
	previouslyAddedToTargetVector = { 0,0 };
	tailSpawnPos = initialSnakePos;
}

int Snake::getApplesCollected()
{
	return (snakePartsCoords.size() - 1);
}

void Snake::addSnakePart()
{
	snakePartsCoords.push_back(tailSpawnPos);
}

// Moves snake according to collected input
void Snake::moveSnake()
{
	// Collects input and checks if target of where to move is visible in window
	Vector2 tempTarget = getTargetVectorFromInput();
	if (tempTarget.x == 0.0 && tempTarget.y == 0.0)
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

	for (int i = (snakePartsCoords.size() - 1); i >= 0; --i)
	{
		// If iter is snake's head then set it to target vector
		// Else set part to vector of the part closer to the snake's head
		if (i == snakePartsCoords.size() - 1) { tailSpawnPos = snakePartsCoords[i]; }
		if (i == 0)
		{
			snakePartsCoords[0] = targetVector;
		}
		else
		{
			snakePartsCoords[i] = snakePartsCoords[i - 1];
		}
	}
}

// Loops through all elements in snake and draws them
// Inherited from RenderableObject
void Snake::drawObject()
{
	for (const auto part : snakePartsCoords)
	{
		DrawRectangle(part.x, part.y, globalGridWidth, globalGridWidth, BLUE);
	}
}