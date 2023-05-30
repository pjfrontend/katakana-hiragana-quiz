#include "GameOver.h"

void GameOver::start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher)
{
	this->window = window;
	this->gameData = gameData;
	this->publisher = publisher;

	font.loadFromFile(FONT_NAME);

	message.setFont(font);
	message.setPosition(HALF_SPRITE, HALF_SPRITE);
	message.setFillColor(sf::Color::White);
	message.setCharacterSize(HALF_SPRITE);

	if (gameData->quiz.isCorrectAnswer(gameData->quiz_choice_index))
	{
		display_success();
	}
	else
	{
		display_failure();
	}
}

void GameOver::input()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_clicking)
	{
		is_clicking = true;
		sf::Vector2f mouse = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		if (gameData->quiz.isCorrectAnswer(gameData->quiz_choice_index))
		{
			gameData->streak += 1;
			if (gameData->streak > 10 && gameData->streak % 10 == 0)
			{
				gameData->lives += 1;
			}

			gameData->create_question();
			publisher->notify((void *)STATE_QUIZ.c_str());
		}
		else
		{
			gameData->lives -= 1;
			if (gameData->lives <= 0)
			{
				publisher->notify((void *)STATE_START.c_str());
			}
			else
			{
				gameData->streak = 0;
				gameData->create_question();
				publisher->notify((void *)STATE_QUIZ.c_str());
			}
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		is_clicking = false;
	}
}

void GameOver::update(float dtAsSeconds)
{
}

void GameOver::draw()
{
	window->clear(sf::Color::Black);

	window->draw(message);

	window->display();
}

void GameOver::display_success()
{
	auto k = gameData->quiz.getQuestion().answer;
	message.setString(L"Correct! " + k.kana + L" reads " + k.reading);
}
void GameOver::display_failure()
{
	auto i = gameData->quiz_choice_index;
	auto answer = gameData->quiz.getQuestion().answer;
	auto u = gameData->quiz.getQuestion().options.at(i);
	message.setString(L"Wrong... You chose " + u.kana + L" but the answer is " + answer.kana);
}
