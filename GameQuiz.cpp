#include "GameQuiz.h"

void GameQuiz::start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher)
{
	this->window = window;
	this->gameData = gameData;
	this->publisher = publisher;

	font.loadFromFile(FONT_NAME);

	lives_streak.setFont(font);
	lives_streak.setPosition(HALF_SPRITE / 4, SCREEN_HEIGHT_IN_PIXELS - HALF_SPRITE - HALF_SPRITE / 4);
	lives_streak.setString("Lives x" +
						   std::to_string(gameData->lives) + " Correct Answers Streak: " +
						   std::to_string(gameData->streak));
	lives_streak.setFillColor(sf::Color::White);
	lives_streak.setCharacterSize(HALF_SPRITE);

	question_txt.setFont(font);
	question_txt.setPosition(HALF_SPRITE / 4, HALF_SPRITE / 4);
	question_txt.setString(build_question_txt());
	question_txt.setFillColor(sf::Color::White);
	question_txt.setCharacterSize(3 * HALF_SPRITE / 4);

	// setting questions and enemies :( not great code
	for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
	{
		// quiz questions
		sf::Text t;
		t.setFont(font);
		t.setPosition(0, (4 * SPRITE_SIDE / 3) + SPRITE_SIDE * i);
		t.setString(labels[i] + gameData->quiz.getQuestion().options.at(i).kana);
		t.setFillColor(sf::Color::White);
		t.setCharacterSize(HALF_SPRITE);
		answers_txt.push_back(t);
	}
}

void GameQuiz::input()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_clicking)
	{
		is_clicking = true;
		sf::Vector2f mouse = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
		{
			if (answers_txt.at(i).getGlobalBounds().contains(mouse))
			{
				gameData->quiz_choice_index = i;
				publisher->notify((void *)STATE_GAME_OVER.c_str());
				return;
			}
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		is_clicking = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		publisher->notify((void *)STATE_PAUSE.c_str());
		return;
	}
}

void GameQuiz::update(float dtAsSeconds)
{
}

void GameQuiz::draw()
{
	window->clear(sf::Color::Black);

	window->draw(lives_streak);
	window->draw(question_txt);

	for (auto b : answers_txt)
	{
		window->draw(b);
	}

	window->display();
}

std::wstring GameQuiz::build_question_txt()
{
	return L"Choose the option that reads " + gameData->quiz.getQuestion().answer.reading;
}
