#include "GameData.h"

GameData::GameData()
{
	lives = LIVES_INIT;
	streak = STREAK_INIT;
}

GameData::~GameData()
{
}

void GameData::resetUserData()
{
	lives = LIVES_INIT;
	streak = STREAK_INIT;
}

std::wstring GameData::to_wstring(std::string str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//std::string narrow = converter.to_bytes(wide_utf16_source_string);
	std::wstring wstr = converter.from_bytes(str);
	return wstr;
}

// int maze_tiles[SPRITES_PER_SCREEN];
void GameData::create_question()
{
	quiz.setQuestion();
}
