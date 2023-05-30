#include "GameReview.h"

void GameReview::start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher)
{
	this->window = window;
	this->gameData = gameData;
	this->publisher = publisher;

	auto winSize = this->window->getSize();
	font.loadFromFile(FONT_NAME);

	hira.setFont(font);
	hira.setPosition(HALF_SPRITE, HALF_SPRITE);
	hira.setString(HIRA_GAME);
	hira.setFillColor(sf::Color::White);
	hira.setCharacterSize(HALF_SPRITE / 2);

	kata.setFont(font);
	kata.setPosition(TWICE_SPRITE, HALF_SPRITE);
	kata.setString(KATA_GAME);
	kata.setFillColor(sf::Color::White);
	kata.setCharacterSize(HALF_SPRITE / 2);

	return_main_menu.setFont(font);
	return_main_menu.setPosition(HALF_SPRITE, winSize.y - SPRITE_SIDE);
	return_main_menu.setString("Return to Main Menu");
	return_main_menu.setFillColor(sf::Color::White);
	return_main_menu.setCharacterSize(HALF_SPRITE);

	for (unsigned int i = 0; i < gameData->KANA_LIST_LENGTH; i++)
	{
		auto k = katakana_list.at(i);
		sf::Text title;
		title.setFont(font);
		title.setString(k.kana + L" - " + k.reading);
		title.setFillColor(sf::Color::White);
		title.setCharacterSize(SPRITE_SIDE / 4);
		title.setPosition(
			HALF_SPRITE + (HALF_SPRITE * 3) * k.col,
			SPRITE_SIDE + k.row * (HALF_SPRITE / 2));
		k_list.push_back(title);
	}

	for (unsigned int i = 0; i < gameData->KANA_LIST_LENGTH; i++)
	{
		auto k = hiragana_list.at(i);
		sf::Text title;
		title.setFont(font);
		title.setString(k.kana + L" - " + k.reading);
		title.setFillColor(sf::Color::White);
		title.setCharacterSize(SPRITE_SIDE / 4);
		title.setPosition(
			HALF_SPRITE + (HALF_SPRITE * 3) * k.col,
			SPRITE_SIDE + k.row * (HALF_SPRITE / 2));
		h_list.push_back(title);
	}
}

void GameReview::input()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_clicking)
	{
		is_clicking = true;
		sf::Vector2f mouse = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		if (hira.getGlobalBounds().contains(mouse))
		{
			gameData->review_type = HIRA_GAME;
			return;
		}

		if (kata.getGlobalBounds().contains(mouse))
		{
			gameData->review_type = KATA_GAME;
			return;
		}

		if (return_main_menu.getGlobalBounds().contains(mouse))
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

void GameReview::update(float dtAsSeconds)
{
}

void GameReview::draw()
{
	window->clear(sf::Color::Black);

	if (gameData->review_type == HIRA_GAME)
	{
		for (auto c : h_list)
		{
			window->draw(c);
		}
	}

	if (gameData->review_type == KATA_GAME)
	{
		for (auto c : k_list)
		{
			window->draw(c);
		}
	}

	window->draw(hira);
	window->draw(kata);
	window->draw(return_main_menu);

	window->display();
}
