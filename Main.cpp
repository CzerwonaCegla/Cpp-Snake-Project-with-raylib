#include <string>
#include <vector>
#include <raylib.h>

class Snake
{
	int length;
	std::vector<Vector2> snakeCoords;
	Vector2 currentDirection;
public:
	Snake()
	{
		length = 1;
		Vector2 initialSnakePos;
		initialSnakePos.x = 0;
		initialSnakePos.y = 0;
		snakeCoords.push_back(initialSnakePos);
		currentDirection.x = 0;
		currentDirection.y = 0;
	}

	void Move()
	{
		if (IsKeyDown(KEY_UP))
		{

		}
	}
};

int main()
{
	int height = 720;
	int width = 1280;
	std::string name = "Snake";

	InitWindow(width, height, name.c_str());

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}