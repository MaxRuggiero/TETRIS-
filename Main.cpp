#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "UI.hpp"
#include "Board.hpp"
#include "Menu.hpp"

using namespace std;
using namespace sf;

int rgt = 0, lft = 0, up = 0;

int score = 0;
int maxScore = 0;

bool live = 1, play = 0, start = 0;

void main()
{
	RenderWindow MENU(VideoMode(400, 400), "Menu");
	MainMenu mainMenu(400, 400);

	RectangleShape fondo;
	fondo.setSize(Vector2f(400, 400));
	Texture Maintexture;
	Maintexture.loadFromFile("fondo.menu.png");
	fondo.setTexture(&Maintexture);

	while (MENU.isOpen())
	{
		Event event;

		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}

			if (live)
			{
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					mainMenu.MoveUp();
					play = 1;
					break;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					mainMenu.MoveDown();
					play = 0;
					break;
				}

				if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					if (play == 1)
					{
						start = true;
						MENU.close();
					}

					if (play == 0)
					{
						start = false;
						MENU.close();
					}
				}

			}
			MENU.clear(Color(30, 30, 30));
			MENU.draw(fondo);
			mainMenu.draw(MENU);
			MENU.display();
		}
	}

	if (start == true)
	{
		Board board;
		UI ui;

		RenderWindow window(VideoMode(400, 400), "Tetris");
		window.setFramerateLimit(60);

		board.InstallPart();

		int right = 0, left = 0, up = 0;

		int score = 0;
		int maxScore = 0;

		ifstream in("maxScore.txt");
		in >> maxScore;
		ui.SetMaxScore(maxScore);
		ui.SetScore(score);

		bool live = 1;

		while (window.isOpen()) {
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) window.close();
			}

			if (live) {
				if (Keyboard::isKeyPressed(Keyboard::Up) && !up) board.RotatePart(), up = 1;
				else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
					up = 0;
				}

				if (Keyboard::isKeyPressed(Keyboard::Down)) board.UpdateLimitTimer(5);
				else board.UpdateLimitTimer(30);

				if (Keyboard::isKeyPressed(Keyboard::Right) && !right) {
					board.Right();
					right = 1;
				}
				else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
					right = 0;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && right) {
					right++;
					if (right == 6) right = 0;
				}

				if (Keyboard::isKeyPressed(Keyboard::Left) && !left) {
					board.Left();
					left = 1;
				}
				else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
					left = 0;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Left) && left) {
					left++;
					if (left == 6) left = 0;
				}

				if (board.UpdateBoard()) {
					if (!board.InstallPart()) {
						live = 0;
						board.ClearBoard();
						if (score > maxScore) {
							ui.NewScore();
							ofstream out("maxScore.txt");
							out << score;
						}
						else {
							ui.GameOver();
						}
					}
				}
				board.UpdateBoardColors();

				int newScore = board.CheckLine() * 5;
				score += newScore;
				ui.SetScore(score);
			}


			window.clear(Color(20, 20, 20));
			window.draw(board);
			window.draw(ui);
			window.display();
		}
	}
}