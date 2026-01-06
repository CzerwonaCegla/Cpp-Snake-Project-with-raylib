#ifndef H_SNAKE
#define H_SNAKE

#include <string>
#include <map>
#include <vector>
#include <raylib.h>
#include "RenderableObject.h"

class Snake : RenderableObject
{
	std::vector<Vector2> snakePartsCoords;
	Vector2 targetVector;
	Vector2 previouslyAddedToTargetVector;
	Vector2 tailSpawnPos;
	std::map<std::string, Texture2D> snakePartTextures;

	Texture2D snakeHead;
	Texture2D snakeTail;
	Texture2D snakeStraight;
	Texture2D snakeTurn;

	void loadSnakeTextures();
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
	std::vector<Vector2> getSnakeCoords();
	bool checkIfCoordsAreInSnake(Vector2 coords);
	void drawSnakePart(int placeInVector);
};

#endif // !H_SNAKE