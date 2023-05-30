#include "Engine.h"

void ActualSubscriber::start(Engine *engine)
{
	this->engine = engine;
}

void ActualSubscriber::update(Publisher *who, void *what)
{
	const char *message = static_cast<char *>(what);
	// std::cout << message << std::endl;
	this->engine->request(message);
}

Engine::Engine() : FSM("GameFSM")
{
	// FSM /////////////////////
	ADD_STATE(Engine, StartState);
	ADD_STATE(Engine, ReviewState);
	ADD_STATE(Engine, QuizState);
	ADD_STATE(Engine, GameOverState);
	ADD_STATE(Engine, PauseState);

	ADD_TRANSITION(StartState, ReviewState);
	ADD_TRANSITION(StartState, QuizState);

	ADD_TRANSITION(ReviewState, StartState);

	ADD_TRANSITION(QuizState, PauseState);
	ADD_TRANSITION(QuizState, GameOverState);

	ADD_TRANSITION(GameOverState, QuizState);
	ADD_TRANSITION(GameOverState, StartState);

	ADD_TRANSITION(PauseState, QuizState);
	ADD_TRANSITION(PauseState, StartState);
	// FSM /////////////////////
	gameData = new GameData();
	publisher = new Publisher();
	subscriber = new ActualSubscriber();
	subscriber->start(static_cast<Engine *>(this));
	publisher->subscribe(subscriber);
	window.create(
		sf::VideoMode(SCREEN_WIDTH_IN_PIXELS, SCREEN_HEIGHT_IN_PIXELS),
		GAME_TITLE,
		sf::Style::Default);
}

void Engine::start()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
				window.close();
		}

		sf::Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();

		currentAppState->input();
		currentAppState->update(dtAsSeconds);
		currentAppState->draw();
	}
}

DEF_ENTER(Engine, StartState)
{
	currentAppState = new (GameIndex);
	currentAppState->start(&window, gameData, publisher);
}

DEF_EXIT(Engine, StartState) {}

DEF_ENTER(Engine, ReviewState)
{
	currentAppState = new (GameReview);
	currentAppState->start(&window, gameData, publisher);
}

DEF_EXIT(Engine, ReviewState) {}

DEF_ENTER(Engine, QuizState)
{
	currentAppState = new (GameQuiz);
	currentAppState->start(&window, gameData, publisher);
}

DEF_EXIT(Engine, QuizState) {}

DEF_ENTER(Engine, GameOverState)
{
	currentAppState = new (GameOver);
	currentAppState->start(&window, gameData, publisher);
}

DEF_EXIT(Engine, GameOverState) {}

DEF_ENTER(Engine, PauseState)
{
	currentAppState = new (GamePause);
	currentAppState->start(&window, gameData, publisher);
}

DEF_EXIT(Engine, PauseState) {}
