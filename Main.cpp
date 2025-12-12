#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>

class Snake
{
	int keyPressed;
	int length;
	std::vector<Vector2> snakeCoords;
	Vector2 currentDirection;
public:
	Snake()
	{
		keyPressed = 0;
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

	void Draw()
	{

	}
};

int main()
{
	int height = 700;
	int width = 1200;
	std::string name = "Snake";
	const int gridWidth = 50;
	SetTargetFPS(60);
	InitWindow(width, height, name.c_str());
	Vector2 objPos = { 0.0, 0.0 };
	Vector2 currentPos = objPos;
	Vector2 targetPos = { 0.0,0.0 };
	Vector2 addToPos = { 0.0, 0.0 };
	float t = 0.0;
	float moveToPosTime = 0.5;
	int loggedKey = 0;
	while (!WindowShouldClose())
	{
		// log keys earlier than meets conditions for better input
		if(IsKeyDown(KEY_UP)){loggedKey = 1;}
		else if(IsKeyDown(KEY_DOWN)) { loggedKey = 2; }
		else if (IsKeyDown(KEY_RIGHT)) { loggedKey = 3; }
		else if (IsKeyDown(KEY_LEFT)) { loggedKey = 4; }

		if (Vector2Distance(currentPos, targetPos) < 0.05)
		{
			// snap objPos to targetPos when close
			objPos = targetPos;
			t = 0.0;

			// check for inputs
			if (/*IsKeyDown(KEY_UP) || */loggedKey == 1) { addToPos = { 0.0, 0.0 }; addToPos.y = -gridWidth; }
			else if (/*IsKeyDown(KEY_DOWN) || */loggedKey == 2) { addToPos = { 0.0, 0.0 }; addToPos.y = gridWidth;}
			else if (/*IsKeyDown(KEY_RIGHT) || */loggedKey == 3) { addToPos = { 0.0, 0.0 }; addToPos.x = gridWidth;}
			else if (/*IsKeyDown(KEY_LEFT) || */loggedKey == 4) { addToPos = { 0.0, 0.0 }; addToPos.x = -gridWidth;}
			loggedKey = 0;
			targetPos += addToPos;
			if (targetPos.x < 0.0 || targetPos.x > (float)(width-gridWidth)) { targetPos.x -= addToPos.x; }
			if (targetPos.y < 0.0 || targetPos.y > (float)(height-gridWidth)) { targetPos.y -= addToPos.y; }
		}
		else
		{
			if (t < 1.0) { t += GetFrameTime()/moveToPosTime; }
			if (t > 1.0) { t = 1.0; }
			currentPos = Vector2Lerp(objPos, targetPos, t);
		}
		// Draw start -------------------
		BeginDrawing();
		ClearBackground(DARKGREEN);
		DrawRectangle(currentPos.x, currentPos.y, gridWidth, gridWidth, BLUE);
		EndDrawing();
		// Draw end ---------------------
	}

	CloseWindow();
	return 0;
}