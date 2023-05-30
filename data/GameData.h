#pragma once
#include "../stdafx.h"
#include "consts.h"
#include "kana_list.h"
#include "../utils/Quiz.h"

class GameData
{
public:
	static const unsigned int KANA_LIST_LENGTH = 109;
	static const unsigned int LIVES_INIT = 3;
	static const unsigned int STREAK_INIT = 0;
	GameData();
	~GameData();
	void resetUserData();
	static std::wstring to_wstring(std::string str);

	// review
	std::string review_type = HIRA_GAME;

	// quiz game
	std::string game_type = HIRA_GAME;
	Quiz quiz;
	int quiz_choice_index = -1;
	void create_question();

	// player data
	int lives;
	int streak;
};
