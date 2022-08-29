#include "StatisticsManager.h"

IDatabase* StatisticsManager::m_database = SqliteDataBase::get_instance();
StatisticsManager* StatisticsManager::m_ptr = nullptr;

bool sortByValue(const std::pair<int, string>& a, const std::pair<int, string>& b)
{
	return (a.first < b.first);
}

StatisticsManager* StatisticsManager::get_instance()
{
	if (!m_ptr)
		m_ptr = new StatisticsManager;

	return m_ptr;
}

void StatisticsManager::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

std::map<int, string>  StatisticsManager::getHighScore(Game game)
{
	std::map<int, string>  HighScores;
	std::vector<std::pair<int, string>> vecOfHighScores;
	std::list<PlayerResults> results = game.getGameResults();

	for (const auto result : results)
	{
		float score = result.correctAnswerCount / result.averageAnswerTime;
		vecOfHighScores.push_back(std::pair<int, string>(score, result.username));
	}

	std::sort(vecOfHighScores.begin(), vecOfHighScores.end(), sortByValue);

	std::copy(vecOfHighScores.begin(), vecOfHighScores.end(), std::inserter(HighScores, HighScores.begin()));

	return HighScores;
}

UserStatistics StatisticsManager::getUserStatistics(string username)
{
	UserStatistics user_statistic;
	user_statistic.username = username;
	user_statistic.totalCorrectAnswerCount = this->m_database->getNumOfCorrectAnswer(username);
	user_statistic.averageAnswerTime = this->m_database->getPlayerAverageAnswerTime(username);
	user_statistic.numOfPlayerGames = this->m_database->getNumOfPlayerGames(username);
	user_statistic.totalWrongAnswerCount = (this->m_database->getNumOfTotalAnswers(username) - this->m_database->getNumOfCorrectAnswer(username));

	return user_statistic;
}
