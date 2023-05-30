#include "Quiz.h"


Quiz::Quiz(AnswersKana answers, unsigned int optionsNumber)
{
	data = answers;
	numberOfOptions = optionsNumber;
	srand((unsigned)time(0));
	std::random_shuffle(data.begin(), data.end());
}

Quiz::Quiz()
{
}


Quiz::~Quiz()
{
}

void Quiz::setQuestion()
{
	question.options.clear();

	unsigned int randomIndex = getQuestionIndex();
	question.answer = data.at(randomIndex);
	question.options.push_back(data.at(randomIndex));
	std::vector<unsigned int> indices;
	indices.push_back(randomIndex);

	while (question.options.size() < numberOfOptions)
	{
		unsigned int randomIndex2 = rand() % data.size();
		if (isIndexInVector(indices, randomIndex2)) {
			continue;
		}

		auto next_question = data.at(randomIndex2);
		// katakana + hiragana need this to work
		if (question.answer.reading == next_question.reading) {
			continue;
		}

		question.options.push_back(next_question);
		indices.push_back(randomIndex2);
	}

	std::random_shuffle(question.options.begin(), question.options.end());
}

QuestionKana Quiz::getQuestion()
{
	return question;
}

bool Quiz::isCorrectAnswer(int index)
{
	return question.options.at(index).id == question.answer.id;
}

bool Quiz::isIndexInVector(std::vector<unsigned int> v, unsigned int i)
{
	for (auto el : v)
	{
		if (el == i) return true;
	}
	return false;
}

unsigned int Quiz::getQuestionIndex()
{
	unsigned int currentIndex = questionIndex;
	//std::cout << "index is: " << currentIndex << std::endl;
	questionIndex++;

	if (questionIndex >= data.size()) {
		std::random_shuffle(data.begin(), data.end());
		questionIndex = 0;
		//std::cout << "ran out of original questions" << std::endl;
	}
	return currentIndex;
}
