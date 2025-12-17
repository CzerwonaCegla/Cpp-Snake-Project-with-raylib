#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>

#define GRID_WIDTH 50

using namespace std;

class Snake
{
	int length;
	vector<Vector2> snakeCoords;
	Vector2 targetVector;
public:
	Snake()
	{
		length = 1;
		Vector2 initialSnakePos;
		initialSnakePos.x = 0;
		initialSnakePos.y = 0;
		snakeCoords.push_back(initialSnakePos);
		targetVector.x = 0;
		targetVector.y = 0;
	}
	
	Snake(Vector2 startingPosVector)
	{
		length = 1;
		Vector2 initialSnakePos = startingPosVector;
		snakeCoords.push_back(initialSnakePos);
		targetVector = initialSnakePos;
	}

	Vector2 getTargetVectorFromInput()
	{
		Vector2 targetVector = { 0,0 };
		if (IsKeyDown(KEY_UP)) { targetVector.y += GRID_WIDTH; }
		else if (IsKeyDown(KEY_DOWN)) { targetVector.y += GRID_WIDTH; }
		else if (IsKeyDown(KEY_RIGHT)) { targetVector.x += GRID_WIDTH; }
		else if (IsKeyDown(KEY_LEFT)) { targetVector.x += GRID_WIDTH; }
		return targetVector;
	}

	void moveSnake()
	{

	}

	void drawSnake()
	{
		
	}
};

int main()
{
	int height = 750;
	int width = 1250;
	std::string name = "Snake";
	const int gridWidth = GRID_WIDTH;
	SetTargetFPS(60);
	InitWindow(width, height, name.c_str());
	// DO NOT TOUCH CODE ABOVE FOR NOW

	Vector2 objPos = { 0.0, 0.0 };
	Vector2 currentPos = objPos;
	Vector2 targetPos = { 0.0,0.0 };
	Vector2 addToPos = { 0.0, 0.0 };
	float t = 0.0;
	float moveToPosTime = 0.5;
	int loggedKey = 0;

	// MAIN GAME LOOP DO NOT TOUCH
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

		// DO NOT TOUCH CODE BELOW FOR NOW
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