#pragma once
#include "Structs.h"
#include "LoggedUser.h"
#include "SqliteDataBase.h"

class Game
{
private:
	std::vector<Question> m_questions;
	std::vector<GameData> m_players;
	unsigned int m_gameId;
	string m_questionDifficulty;
	unsigned  int m_numOfQuestions;
	static IDatabase* m_dataBase;

public:
	Game(unsigned int gameId, string questionDifficulty, unsigned  int numOfQuestions, std::vector<Question> questions, std::vector<GameData> players);
	Game(Game* game);
	GameData* getPlayerMeta(string username);
	Question getNextQuestion(string username, unsigned int* questionCounter);
	bool submitAnswer(string username, string answer, float time);
	void removePlayer(string username);
	unsigned int getGameId();
	std::vector<Question> getQuestions();
	std::vector<GameData> getPlayersData();
	string getQuestionsDifficulty();
	unsigned int getNumOfQuestions();
	std::vector<string> getPlayersInGame();
	std::list<PlayerResults> getGameResults();

};