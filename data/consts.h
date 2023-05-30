#pragma once
#include "../stdafx.h"

// text
static const std::string GAME_TITLE = "Kana Quiz";

static const std::string PAUSE_CONT = "Resume Game";
static const std::string PAUSE_QUIT = "Back to Main Menu";

static const std::string QUIZ = "Quiz";
static const std::string REVIEW = "Review";
static const std::string KATA_GAME = "Katakana";
static const std::string HIRA_GAME = "Hiragana";
static const std::string QUIT_GAME = "Quit";

// states
static const std::string STATE_START = "StartState";
static const std::string STATE_GAME_OVER = "GameOverState";
static const std::string STATE_PAUSE = "PauseState";
static const std::string STATE_REVIEW = "ReviewState";
static const std::string STATE_QUIZ = "QuizState";

// dimensions
const int SPRITE_SIDE = 64;
const int SCREEN_HEIGHT_IN_SPRITES = 9;
const int SCREEN_WIDTH_IN_SPRITES = 15;
const int SPRITES_PER_SCREEN = SCREEN_HEIGHT_IN_SPRITES * SCREEN_WIDTH_IN_SPRITES;
const int SCREEN_HEIGHT_IN_PIXELS = SPRITE_SIDE * SCREEN_HEIGHT_IN_SPRITES;
const int SCREEN_WIDTH_IN_PIXELS = SPRITE_SIDE * SCREEN_WIDTH_IN_SPRITES;
const int HALF_SPRITE = SPRITE_SIDE / 2;
const int TWICE_SPRITE = SPRITE_SIDE * 2;

const int NUMBER_OF_QUESTIONS = 4;

// assets
const static std::string FONT_NAME = "assets/NotoSansJP-Regular.otf";

// structs
struct Kana {
	std::string id;
	unsigned int row;
	std::wstring kana;
	std::wstring reading;
	std::string type;
	unsigned int col;
};
