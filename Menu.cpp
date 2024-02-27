#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.hpp"

MainMenu::MainMenu(float width, float heigth) 
{
	if (!font.loadFromFile("FONTS/font.ttf"))
	{ cout << "No hay fuente de texto existente" << endl; }

	//JUGAR
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("JUGAR");
	mainMenu[0].setCharacterSize(30);
	mainMenu[0].setPosition(20, 280);

	//Salir
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("SALIR");
	mainMenu[1].setCharacterSize(30);
	mainMenu[1].setPosition(20, 330);

	MainMenuSelected = -1;
}

MainMenu::~MainMenu()
{}

void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; i++)
	{
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp()
{
	if (MainMenuSelected - 1 >= 0) 
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;

		if (MainMenuSelected == -1) 
		{ MainMenuSelected = 0; }

		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

void MainMenu::MoveDown()
{
	if (MainMenuSelected + 1 <= Max_main_menu)
	{ 
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;

		if (MainMenuSelected == 2)
		{
			MainMenuSelected = 1;
		}

		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}
