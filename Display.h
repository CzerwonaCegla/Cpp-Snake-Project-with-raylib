#ifndef H_DISPLAY
#define H_DISPLAY
#include <string>
class Display
{
	int windowWidth;
	int windowHeight;
	std::string windowName;
public:
	Display();
	Display(int width, int height, std::string name);
	void startDisplay();
	void renderDisplay();
	void endDisplay();
};
#endif