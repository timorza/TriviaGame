#pragma once
#include "sqlite3.h"
#include "Structs.h"
#include <string>
#include <queue>
#include <list>

using std::string;

class IDatabase
{
public:
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string password, string username) = 0;
	virtual void addNewUser(string username, string password, string email) = 0;

	virtual std::vector<Question> getQuestions(string difficulty, unsigned int numOfQuestuions) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswer(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;

	virtual bool isAnswerCorrect(string answer, string question) = 0;
	virtual void addToCorrectAnswers(string username) = 0;
	virtual void addToPlayerGames(string username) = 0;
	virtual void addToWrongAnswers(string username) = 0;
	virtual void setPlayerAverageAnswerTime(string username, float averageAnswerTime) = 0;
};

