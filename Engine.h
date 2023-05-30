#pragma once
#include "stdafx.h"
#include "utils/fsm.h"
#include "utils/pubsub.h"
#include "data/consts.h"
#include "data/GameData.h"
#include "IAppState.h"
#include "GameIndex.h"
#include "GameReview.h"
#include "GameQuiz.h"
#include "GamePause.h"
#include "GameOver.h"

class Engine;

class ActualSubscriber : public Subscriber
{
	Engine *engine;

public:
	void start(Engine *engine);
	virtual void update(Publisher *who, void *what);
};

class Engine : public FSM
{
	DECL_STATE(Engine, StartState);
	DECL_STATE(Engine, ReviewState);
	DECL_STATE(Engine, QuizState);
	DECL_STATE(Engine, GameOverState);
	DECL_STATE(Engine, PauseState);

	IAppState *currentAppState;
	sf::RenderWindow window;
	GameData *gameData;
	sf::Event event;
	Publisher *publisher;
	ActualSubscriber *subscriber;

public:
	Engine();
	void start();
};
