#pragma once
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include "Game.h"
#include <map>

class StatisticsManager
{
private:
	static StatisticsManager* m_ptr;
	static IDatabase* m_database;
	StatisticsManager() = default;

public:	
	static StatisticsManager* get_instance();
	static void reset_instance();
	std::map<int, string> getHighScore(Game game);
	UserStatistics getUserStatistics(string username);
};