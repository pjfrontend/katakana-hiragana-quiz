#include "GameIndex.h"

void GameIndex::start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher)
{
	this->window = window;
	this->gameData = gameData;
	this->publisher = publisher;

	auto winSize = this->window->getSize();
	font.loadFromFile(FONT_NAME);

	title.setFont(font);
	title.setPosition(HALF_SPRITE, HALF_SPRITE);
	title.setString(GAME_TITLE);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(SPRITE_SIDE);

	hira_quiz.setFont(font);
	hira_quiz.setString(HIRA_GAME + " " + QUIZ);
	hira_quiz.setFillColor(sf::Color::White);
	hira_quiz.setCharacterSize(HALF_SPRITE);
	hira_quiz.setPosition(HALF_SPRITE, winSize.y - HALF_SPRITE * 5);

	kata_quiz.setFont(font);
	kata_quiz.setString(KATA_GAME + " " + QUIZ);
	kata_quiz.setFillColor(sf::Color::White);
	kata_quiz.setCharacterSize(HALF_SPRITE);
	kata_quiz.setPosition(HALF_SPRITE, winSize.y - HALF_SPRITE * 4);

	review_game.setFont(font);
	review_game.setString(REVIEW);
	review_game.setFillColor(sf::Color::White);
	review_game.setCharacterSize(HALF_SPRITE);
	review_game.setPosition(HALF_SPRITE, winSize.y - HALF_SPRITE * 3);

	quit_game.setFont(font);
	quit_game.setString(QUIT_GAME);
	quit_game.setFillColor(sf::Color::White);
	quit_game.setCharacterSize(HALF_SPRITE);
	quit_game.setPosition(HALF_SPRITE, winSize.y - HALF_SPRITE * 2);

	gameData->resetUserData();
}

void GameIndex::input()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_clicking)
	{
		is_clicking = true;
		sf::Vector2f mouse = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		if (kata_quiz.getGlobalBounds().contains(mouse))
		{
			gameData->game_type = KATA_GAME;
			gameData->quiz = Quiz(katakana_list, NUMBER_OF_QUESTIONS);
			gameData->create_question();
			publisher->notify((void *)STATE_QUIZ.c_str());
			return;
		}

		if (hira_quiz.getGlobalBounds().contains(mouse))
		{
			gameData->game_type = HIRA_GAME;
			gameData->quiz = Quiz(hiragana_list, NUMBER_OF_QUESTIONS);
			gameData->create_question();
			publisher->notify((void *)STATE_QUIZ.c_str());
			return;
		}

		if (review_game.getGlobalBounds().contains(mouse))
		{
			publisher->notify((void *)STATE_REVIEW.c_str());
			return;
		}

		if (quit_game.getGlobalBounds().contains(mouse))
		{
			exit(0);
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		is_clicking = false;
	}
}

void GameIndex::update(float dtAsSeconds)
{
}

void GameIndex::draw()
{
	window->clear(sf::Color::Black);

	window->draw(title);
	window->draw(hira_quiz);
	window->draw(kata_quiz);
	window->draw(review_game);
	window->draw(quit_game);

	window->display();
}
