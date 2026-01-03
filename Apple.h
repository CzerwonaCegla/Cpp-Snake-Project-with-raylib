#ifndef H_APPLE
#define H_APPLE

#include "RenderableObject.h"

class Apple : RenderableObject
{
	Texture2D appleTexture;
	Vector2 coordinates;

public:
	Apple();
	Apple(Vector2 coords);
	void drawObject() override;
};

#endif // !H_APPLE
