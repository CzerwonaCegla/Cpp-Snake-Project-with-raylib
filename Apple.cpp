#include "Apple.h";

#include <raylib.h>
#include "GlobalGameParameters.h"

Apple::Apple()
{
	appleTexture = LoadTexture("Textures\\Apple.png");
	coordinates = rollCoordinates();
}

Apple::Apple(Vector2 coordinates)
{
	appleTexture = LoadTexture("Textures\\Apple.png");
	this->coordinates = coordinates;
}

void Apple::drawObject()
{
	DrawTextureV(appleTexture, coordinates, WHITE);
}

Vector2 Apple::getCoordinates()
{
	return coordinates;
}

Vector2 Apple::rollCoordinates()
{
	int xMult = (globalGameWindowWidth-globalGridWidth) / globalGridWidth;
	int x = GetRandomValue(0, xMult);

	int yMult = (globalGameWindowHeight-globalGridWidth) / globalGridWidth;
	int y = GetRandomValue(0, yMult);

	Vector2 tempVec2 = { (float)x * globalGridWidth, (float)y * globalGridWidth };
	return tempVec2;
}

void Apple::setNewCoordinates()
{
	coordinates = rollCoordinates();
}