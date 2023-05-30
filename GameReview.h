#pragma once
#include "stdafx.h"
#include "IAppState.h"
#include "data/kana_list.h"

class GameReview : public IAppState
{
	bool is_clicking = true;
	sf::Font font;
	sf::Text hira;
	sf::Text kata;
	sf::Text return_main_menu;

	std::vector<sf::Text> h_list;
	std::vector<sf::Text> k_list;

public:
	void start(sf::RenderWindow *window, GameData *gameData, Publisher *publisher);
	void input();
	void update(float dtAsSeconds);
	void draw();
};
