#ifndef H_APPLE
#define H_APPLE

#include <raylib.h>
#include "RenderableObject.h"

class Apple : RenderableObject
{
	Texture2D appleTexture;
	Vector2 coordinates;
	Vector2 rollCoordinates();

public:
	Apple();
	Apple(Vector2 coords);
	void drawObject() override;
	Vector2 getCoordinates();
	void setNewCoordinates();
};

#endif // !H_APPLE
