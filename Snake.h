#ifndef H_SNAKE
#define H_SNAKE

#include <vector>
#include <raylib.h>
#include <raymath.h>
#include "GlobalGameParameters.h"
#include "RenderableObject.h"

class Snake : RenderableObject
{
	std::vector<Vector2> snakePartsCoords;
	Vector2 targetVector;
	Vector2 previouslyAddedToTargetVector;
	Vector2 tailSpawnPos;

	bool chceckIfSnakeCollidesWithSelf();
	Vector2 getTargetVectorFromInput();
	bool checkIfInBorders(const Vector2& tempTarget);

public:
	Snake();
	Snake(Vector2 startingPosVector);
	int getApplesCollected();
	void addSnakePart();
	void moveSnake();
	void drawObject() override;
};

#endif // !H_SNAKE