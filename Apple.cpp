#include <raylib.h>
#include "Apple.h";

Apple::Apple()
{
	appleTexture = LoadTexture("Textures\\Apple.png");
	coordinates = { 500, 500 };
}

Apple::Apple(Vector2 coordinates)
{

}

void Apple::drawObject()
{
	DrawTextureV(appleTexture, coordinates, WHITE);
}