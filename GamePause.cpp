#include "GamePause.h"

void GamePause::start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher)
{
	this->window = window;
	this->gameData = gameData;
	this->publisher = publisher;

	font.loadFromFile(FONT_NAME);

	message.setFont(font);
	message.setPosition(HALF_SPRITE, HALF_SPRITE);
	message.setFillColor(sf::Color::White);
	message.setCharacterSize(HALF_SPRITE);
	message.setString("Pause");

	resume_btn.setFont(font);
	resume_btn.setPosition(HALF_SPRITE, HALF_SPRITE * 3);
	resume_btn.setFillColor(sf::Color::White);
	resume_btn.setCharacterSize(HALF_SPRITE / 2);
	resume_btn.setString(PAUSE_CONT);

	main_menu_btn.setFont(font);
	main_menu_btn.setPosition(HALF_SPRITE, HALF_SPRITE * 4);
	main_menu_btn.setFillColor(sf::Color::White);
	main_menu_btn.setCharacterSize(HALF_SPRITE / 2);
	main_menu_btn.setString(PAUSE_QUIT);
}

void GamePause::input()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_clicking)
	{
		is_clicking = true;
		sf::Vector2f mouse = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		if (resume_btn.getGlobalBounds().contains(mouse))
		{
			publisher->notify((void *)STATE_QUIZ.c_str());
			return;
		}

		if (main_menu_btn.getGlobalBounds().contains(mouse))
		{
			publisher->notify((void *)STATE_START.c_str());
			return;
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		is_clicking = false;
	}
}

void GamePause::update(float dtAsSeconds)
{
}

void GamePause::draw()
{
	window->clear(sf::Color::Black);

	window->draw(message);
	window->draw(resume_btn);
	window->draw(main_menu_btn);

	window->display();
}
