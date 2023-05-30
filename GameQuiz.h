#pragma once
#include "stdafx.h"
#include "IAppState.h"
#include "data/consts.h"

class GameQuiz : public IAppState
{
	// sf::Event event;
	bool is_clicking = true;
	sf::Font font;
	sf::Text question_txt;
	sf::Text lives_streak;
	std::wstring labels[NUMBER_OF_QUESTIONS] = {L"A", L"B", L"C", L"D"};
	std::vector<sf::Text> answers_txt;

	std::wstring build_question_txt();

public:
	void start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher);
	void input();
	void update(float dtAsSeconds);
	void draw();
};
