#pragma once
#include "Game.h"

class GameManager
{
private:
	static GameManager* m_ptr;
	GameManager() = default;
	~GameManager() = default;
	std::vector<Game> m_games;

public:
	static GameManager* getInstance();
	static void resetInstance();
	void createGame(Game game);
	void deleteGame(unsigned int gameId);
	Game getGameById(unsigned int id);
	bool SumbitAnswerOfGame(string username, string answer, float time, unsigned int id);
	Question getNextQuestionOfPlayer(string username, unsigned int id, unsigned int* questionCounter);
	std::list<PlayerResults> getGameResults(unsigned int id);
	void removeUserFromGame(string username, unsigned int id);

};