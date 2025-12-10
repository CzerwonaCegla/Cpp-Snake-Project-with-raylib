#include "Display.h"
#include <raylib.h>
Display::Display()
{
	windowWidth = 1280;
	windowHeight = 720;
	windowName = "Snake";
}

Display::Display(int width, int height, std::string name)
{
	windowWidth = width;
	windowHeight = height;
	windowName = name;
}

void Display::startDisplay()
{
	InitWindow(windowWidth, windowHeight, windowName.c_str());
}

void Display::renderDisplay()
{
	BeginDrawing();

	EndDrawing();
}

void Display::endDisplay()
{
	CloseWindow();
}