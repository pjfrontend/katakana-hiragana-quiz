#pragma once
#include "../stdafx.h"
#include "../data/consts.h"

typedef std::vector<Kana> AnswersKana;

struct QuestionKana
{
	Kana answer;
	AnswersKana options;
};

class Quiz
{
	bool is_kana;
	AnswersKana data;
	QuestionKana question;
	unsigned int numberOfOptions;
	bool isIndexInVector(std::vector<unsigned int> v, unsigned int i);
	unsigned int questionIndex = 0;
	unsigned int getQuestionIndex();
public:
	Quiz(AnswersKana answers, unsigned int optionsNumber);
	Quiz();
	~Quiz();
	void setQuestion();
	QuestionKana getQuestion();
	bool isCorrectAnswer(int index);
};

