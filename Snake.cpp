#include "Snake.h"

#include <vector>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <map>
#include <iostream>
#include "GlobalGameParameters.h"

// Reads input and returns target vector
Vector2 Snake::getTargetVectorFromInput()
{
	Vector2 localTargetVector = { 0,0 };
	if (IsKeyDown(KEY_UP)) { localTargetVector.y -= globalGridWidth; }
	else if (IsKeyDown(KEY_DOWN)) { localTargetVector.y += globalGridWidth; }
	else if (IsKeyDown(KEY_RIGHT)) { localTargetVector.x += globalGridWidth; }
	else if (IsKeyDown(KEY_LEFT)) { localTargetVector.x -= globalGridWidth; }
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

void Snake::getGameStatePtr(gameWinState *state)
{
	currentState = state;
}

void Snake::loadSnakeTextures()
{
	snakeHead = LoadTexture("Textures\\SnakeHead.png");
	snakeStraight = LoadTexture("Textures\\SnakeStraight.png");
	snakeTurn = LoadTexture("Textures\\SnakeTurn.png");
	snakeTail = LoadTexture("Textures\\SnakeTail.png");
	/*snakePartTextures.emplace(std::make_pair("SnakeHead", snakeHead));
	snakePartTextures.emplace(std::make_pair("SnakeStraight", snakeStraight));
	snakePartTextures.emplace(std::make_pair("SnakeTurn", snakeTurn));
	snakePartTextures.emplace(std::make_pair("SnakeTail", snakeTail));*/
}

Snake::Snake()
{
	// Get more or less center position
	Vector2 tempVec = { (ceil(float (globalGameWindowWidth / globalGridWidth) / 2.0)) * globalGridWidth,
		(ceil(float(globalGameWindowHeight / globalGridWidth) / 2.0)) * globalGridWidth };
	Vector2 initialSnakePos = tempVec;
	snakePartsCoords.push_back(initialSnakePos);
	targetVector = initialSnakePos;
	previouslyAddedToTargetVector = { 50.0 ,0.0 };
	
	// Here to spawn a tail after head
	Vector2 tempVec2 = { initialSnakePos.x - globalGridWidth, initialSnakePos.y };
	tailSpawnPos = tempVec2;
	snakePartsCoords.push_back(tailSpawnPos);
	loadSnakeTextures();
}

Snake::Snake(Vector2 startingPosVector)
{
	Vector2 initialSnakePos = startingPosVector;
	snakePartsCoords.push_back(initialSnakePos);
	targetVector = initialSnakePos;
	previouslyAddedToTargetVector = { 50.0,0.0 };
	Vector2 tempVec2 = { initialSnakePos.x - globalGridWidth, initialSnakePos.y };
	tailSpawnPos = tempVec2;
	snakePartsCoords.push_back(tailSpawnPos);
	loadSnakeTextures();
}

int Snake::getApplesCollected()
{
	return (snakePartsCoords.size() - 1);
}

void Snake::addSnakePart()
{
	snakePartsCoords.push_back(tailSpawnPos);
}

bool Snake::chceckIfSnakeCollidesWithSelf()
{
	if (getApplesCollected() != 0)
	{
		for (int i = 0; i <= snakePartsCoords.size() - 1; ++i)
		{
			for (int j = i+1; j <= snakePartsCoords.size() - 1; ++j)
			{
				if (snakePartsCoords[i] == snakePartsCoords[j])
				{
					return true;  
				}
			}
		}
	}
	return false;
}

// Moves snake according to collected input
void Snake::moveSnake()
{
	// Collects input and checks if target of where to move is visible in window and if the input provided will make the snake reverse into itself
	Vector2 tempTarget = getTargetVectorFromInput();
	if (!(previouslyAddedToTargetVector.x == 0.0 && previouslyAddedToTargetVector.y == 0.0))
	{
		if (tempTarget.x == 0.0 && tempTarget.y == 0.0)
		{
			tempTarget = previouslyAddedToTargetVector;
		}
		if ((tempTarget.x == -previouslyAddedToTargetVector.x) || (tempTarget.y == -previouslyAddedToTargetVector.y))
		{
			tempTarget.x = previouslyAddedToTargetVector.x;
			tempTarget.y = previouslyAddedToTargetVector.y;
		}
	}
	if (checkIfInBorders(tempTarget))
	{
		targetVector += tempTarget;
		previouslyAddedToTargetVector = tempTarget;
	}
	else
	{
		*currentState = gameWinState::Lose;
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

	if (chceckIfSnakeCollidesWithSelf()) { *currentState = gameWinState::Lose; }
}

// Loops through all elements in snake and draws them
// Inherited from RenderableObject
void Snake::drawObject()
{
	for (int i = 0; i <= (snakePartsCoords.size() - 1); ++i)
	{
		//DrawRectangle(part.x, part.y, globalGridWidth, globalGridWidth, BLUE);
		drawSnakePart(i);
	}
}

std::vector<Vector2> Snake::getSnakeCoords()
{
	return snakePartsCoords;
}

bool Snake::checkIfCoordsAreInSnake(Vector2 coords)
{
	for (const auto &i : snakePartsCoords)
	{
		if (i == coords)
		{
			return true;
		}
	}
	return false;
}

// TODO in this function: delete all unused commented code
void Snake::drawSnakePart(int placeInVector)
{
	int deg = 0;
	Rectangle source = { 0.0, 0.0, (float)globalGridWidth, (float)globalGridWidth};
	Rectangle dest = { snakePartsCoords[placeInVector].x + (float)globalGridWidth/2.0,
		snakePartsCoords[placeInVector].y + (float)globalGridWidth / 2.0, (float)globalGridWidth, (float)globalGridWidth };
	Vector2 origin = { ((float)globalGridWidth / 2.0), ((float)globalGridWidth / 2.0) };
	//Vector2 offset = { 0.0, 0.0 };
	// Snake head
	if (placeInVector == 0)
	{
		// Compares position of the next part after head to position of head and sets draws rotated texture accordingly
		if ((snakePartsCoords[placeInVector + 1].x - snakePartsCoords[placeInVector].x) > 0)
		{
			deg = 0;
			//offset = { 0.0, 0.0 };
		}
		else if ((snakePartsCoords[placeInVector + 1].x - snakePartsCoords[placeInVector].x) < 0)
		{
			deg = 180;
			//offset = { (float)globalGridWidth, (float)globalGridWidth };
		}
		else if ((snakePartsCoords[placeInVector + 1].y - snakePartsCoords[placeInVector].y) > 0)
		{
			deg = 90;
			//offset = { 0.0, (float)globalGridWidth };
		}
		else if ((snakePartsCoords[placeInVector + 1].y - snakePartsCoords[placeInVector].y) < 0)
		{
			deg = 270;
			//offset = { (float)globalGridWidth, 0.0 };
		}
		//DrawTextureEx(snakeHead, snakePartsCoords[placeInVector] + offset, deg, 1, WHITE);
		DrawTexturePro(snakeHead, source, dest, origin, deg, WHITE);
		// debug stuff
		//std::cout << "Drawn head at: " << (snakePartsCoords[placeInVector]/* + offset*/).x << " "
		//	<< (snakePartsCoords[placeInVector]/* + offset*/).y << std::endl;
		
	}
	// Snake tail
	else if (placeInVector == (snakePartsCoords.size() - 1))
	{

		// Compares position of the part before the tail to determine tail's rotation
		if (snakePartsCoords[placeInVector - 1].x - snakePartsCoords[placeInVector].x > 0)
		{
			deg = 180;
			//offset = { (float)globalGridWidth, (float)globalGridWidth };
		}
		else if (snakePartsCoords[placeInVector - 1].x - snakePartsCoords[placeInVector].x < 0)
		{
			deg = 0;
			//offset = { 0.0, 0.0 };
		}
		else if (snakePartsCoords[placeInVector - 1].y - snakePartsCoords[placeInVector].y > 0)
		{
			deg = 270;
			//offset = { 0.0, (float)globalGridWidth };
		}
		else if (snakePartsCoords[placeInVector - 1].y - snakePartsCoords[placeInVector].y < 0)
		{
			deg = 90;
			//offset = { 0.0, (float)globalGridWidth };
		}
		//DrawTextureEx(snakeTail, (snakePartsCoords[placeInVector]/* + offset*/), deg, 1, WHITE);
		DrawTexturePro(snakeTail, source, dest, origin, deg, WHITE);

		// debug stuff
		//std::cout << "Drawn tail at: " << (snakePartsCoords[placeInVector]/* + offset*/).x << " "
		//	<< (snakePartsCoords[placeInVector]/* + offset*/).y << std::endl;
	}
	else
	{
		//std::string texture;

		// If the two bordering vector2 coordinates are in a straight line
		if (snakePartsCoords[placeInVector - 1].x == snakePartsCoords[placeInVector + 1].x)
		{
			//texture = "SnakeStraight";
			deg = 90;
			DrawTexturePro(snakeStraight, source, dest, origin, deg, WHITE);
		}
		else if (snakePartsCoords[placeInVector - 1].y == snakePartsCoords[placeInVector + 1].y)
		{
			//texture = "SnakeStraight";
			deg = 0;
			DrawTexturePro(snakeStraight, source, dest, origin, deg, WHITE);
		}

		// If the current vector2 coordinate is a turn
		// For up-right turn
		else if ((((snakePartsCoords[placeInVector + 1].x - snakePartsCoords[placeInVector].x) > 0) && ((snakePartsCoords[placeInVector - 1].y - snakePartsCoords[placeInVector].y) < 0)) //pos 5
			|| (((snakePartsCoords[placeInVector - 1].x - snakePartsCoords[placeInVector].x) > 0) && ((snakePartsCoords[placeInVector + 1].y - snakePartsCoords[placeInVector].y) < 0))) //pos 6
		{
			//texture = "SnakeTurn";
			deg = 270;
			DrawTexturePro(snakeTurn, source, dest, origin, deg, WHITE);
		}
		// For down-right turn
		else if (((snakePartsCoords[placeInVector + 1].x - snakePartsCoords[placeInVector].x > 0) && (snakePartsCoords[placeInVector - 1].y - snakePartsCoords[placeInVector].y) > 0) //pos 2
			|| ((snakePartsCoords[placeInVector - 1].x - snakePartsCoords[placeInVector].x > 0) && (snakePartsCoords[placeInVector + 1].y - snakePartsCoords[placeInVector].y) > 0)) //pos 1
		{
			//texture = "SnakeTurn";
			deg = 0;
			DrawTexturePro(snakeTurn, source, dest, origin, deg, WHITE);
		}
		// For up-left turn
		else if (((snakePartsCoords[placeInVector + 1].x - snakePartsCoords[placeInVector].x < 0) && (snakePartsCoords[placeInVector - 1].y - snakePartsCoords[placeInVector].y) < 0) //pos 7
			|| ((snakePartsCoords[placeInVector - 1].x - snakePartsCoords[placeInVector].x < 0) && (snakePartsCoords[placeInVector + 1].y - snakePartsCoords[placeInVector].y) < 0)) //pos 8
		{
			//texture = "SnakeTurn";
			deg = 180;
			DrawTexturePro(snakeTurn, source, dest, origin, deg, WHITE);
		}
		// For down-left turn
		else if (((snakePartsCoords[placeInVector + 1].x - snakePartsCoords[placeInVector].x < 0) && (snakePartsCoords[placeInVector - 1].y - snakePartsCoords[placeInVector].y) > 0) //pos 4
			|| ((snakePartsCoords[placeInVector - 1].x - snakePartsCoords[placeInVector].x < 0) && (snakePartsCoords[placeInVector + 1].y - snakePartsCoords[placeInVector].y) > 0)) // pos 3
		{
			//texture = "SnakeTurn";
			deg = 90;
			//DrawTextureEx(snakeTurn, snakePartsCoords[placeInVector], deg, 1, WHITE);
			DrawTexturePro(snakeTurn, source, dest, origin, deg, WHITE);
		}
		else
		{
			// for debugging missing cases
			DrawRectangle(snakePartsCoords[placeInVector].x, snakePartsCoords[placeInVector].y, 50, 50, RED);
		}
		//DrawTextureEx(snakePartTextures.at(texture), snakePartsCoords[placeInVector], deg, 1, WHITE);
	}

}

void Snake::moveSnake(const Vector2 &moveToVector)
{
	Vector2 tempTarget = moveToVector;
	if (!(previouslyAddedToTargetVector.x == 0.0 && previouslyAddedToTargetVector.y == 0.0))
	{
		if (tempTarget.x == 0.0 && tempTarget.y == 0.0)
		{
			tempTarget = previouslyAddedToTargetVector;
		}
		if ((tempTarget.x == -previouslyAddedToTargetVector.x) || (tempTarget.y == -previouslyAddedToTargetVector.y))
		{
			tempTarget.x = previouslyAddedToTargetVector.x;
			tempTarget.y = previouslyAddedToTargetVector.y;
		}
	}
	if (checkIfInBorders(tempTarget))
	{
		targetVector += tempTarget;
		previouslyAddedToTargetVector = tempTarget;
	}
	else
	{
		*currentState = gameWinState::Lose;
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

	if (chceckIfSnakeCollidesWithSelf()) { *currentState = gameWinState::Lose; }
}