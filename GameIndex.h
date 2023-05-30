#pragma once
#include "stdafx.h"
#include "IAppState.h"
#include "data/consts.h"
#include "utils/Quiz.h"
#include "data/kana_list.h"

class GameIndex : public IAppState
{
	bool is_clicking = true;
	sf::Font font;
	sf::Text title;
	sf::Text hira_quiz;
	sf::Text kata_quiz;
	sf::Text review_game;
	sf::Text quit_game;

public:
	void start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher);
	void input();
	void update(float dtAsSeconds);
	void draw();
};
