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
		if (IsKeyDown(KEY_UP)) {}
	}
};

int main()
{
	int height = 720;
	int width = 1280;
	std::string name = "Snake";
	SetTargetFPS(5);
	InitWindow(width, height, name.c_str());
	Vector2 currentDirection = { 0.0,0.0 };
	Vector2 objPos = { 200.0, 200.0 };
	while (!WindowShouldClose())
	{
		//currentDirection = { 0.0,0.0 };
		if (IsKeyDown(KEY_UP)) { currentDirection.y = -50.0; currentDirection.x = 0.0; }
		else if (IsKeyDown(KEY_DOWN)) { currentDirection.y = 50.0; currentDirection.x = 0.0; }
		else if (IsKeyDown(KEY_RIGHT)) { currentDirection.x = 50.0; currentDirection.y = 0.0; }
		else if (IsKeyDown(KEY_LEFT)) { currentDirection.x = -50.0; currentDirection.y = 0.0; }
		BeginDrawing();
		ClearBackground(DARKGREEN);
		objPos.x += currentDirection.x;
		objPos.y += currentDirection.y;
		DrawRectangle(objPos.x, objPos.y, 50, 50, BLUE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}