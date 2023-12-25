#include "mainmenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

MainMenu::MainMenu(float width, float hight) {
	font.loadFromFile("PiloEscribanoPublico-Regular.ttf");
	for (int i = 0; i < 4; i++)
	{
		mainMenu[i].setFont(font);
		mainMenu[i].setFillColor(Color::White);
		mainMenu[i].setCharacterSize(50);
	}
	//play
	mainMenu[0].setFillColor(Color::Blue);
	mainMenu[0].setString("Play");
	mainMenu[0].setPosition(110, 215);
	//options
	mainMenu[1].setString("Options");
	mainMenu[1].setPosition(80, 340);
	//about
	mainMenu[2].setString("LeaderBoard");
	mainMenu[2].setPosition(90, 465);
	//exit
	mainMenu[3].setString("Exit");
	mainMenu[3].setPosition(110, 590);
	MainMenuselected = 0;

}
//drawing main_menu
void MainMenu::draw(RenderWindow& window) {
	window.draw(mainMenu[0]);
	window.draw(mainMenu[1]);
	window.draw(mainMenu[2]);
	window.draw(mainMenu[3]);
}
//move up
void MainMenu::moveup()
{
	if (MainMenuselected - 1 >= -1)
	{
		mainMenu[MainMenuselected].setFillColor(Color::White);
		MainMenuselected--;
		if (MainMenuselected == -1)
		{
			MainMenuselected = 3;
		}
		mainMenu[MainMenuselected].setFillColor(Color::Blue);

	}
}
//move down
void MainMenu::movedown()
{
	if (MainMenuselected + 1 <= max_main_menu)
	{
		mainMenu[MainMenuselected].setFillColor(Color::White);
		MainMenuselected++;
		if (MainMenuselected == 4)
		{
			MainMenuselected = 0;
		}
		mainMenu[MainMenuselected].setFillColor(Color::Blue);
	}
}