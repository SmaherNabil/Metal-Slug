#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#define max_main_menu 4
class MainMenu
{
public:
	MainMenu(float width, float hight);
	void draw(RenderWindow& window);
	void moveup();
	void movedown();
	int MainMenupressed() {
		return MainMenuselected;
	}
private:
	int MainMenuselected = 0;
	Font font;
	Text mainMenu[max_main_menu];
};

