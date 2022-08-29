#include "Game.h"

IDatabase* Game::m_dataBase = SqliteDataBase::get_instance();

Game::Game(unsigned int gameId, string questionDifficulty, unsigned int numOfQuestions, std::vector<Question> questions, std::vector<GameData> players)
{
	this->m_gameId = gameId;
	this->m_questionDifficulty = questionDifficulty;
	this->m_numOfQuestions = numOfQuestions;
	this->m_questions = questions;
	this->m_players = players;
}

Game::Game(Game* game)
{
	this->m_gameId = game->getGameId();
	this->m_numOfQuestions = game->getNumOfQuestions();
	this->m_questionDifficulty = game->getQuestionsDifficulty();
	this->m_questions = game->getQuestions();
	this->m_players = game->getPlayersData();
}

GameData* Game::getPlayerMeta(string username)
{
	for (int i = 0; i < this->m_players.size(); i++)
	{
		if (this->m_players[i].username == username)
			return &m_players[i];
	}
}

Question Game::getNextQuestion(string username, unsigned int* questionCounter)
{
	GameData* iter = getPlayerMeta(username);
	iter->currentQuestion = this->m_questions.at(++ * questionCounter);

	return iter->currentQuestion;
}

bool Game::submitAnswer(string username, string answer, float time)
{
	try
	{
		GameData* iter = getPlayerMeta(username);
		string question = iter->currentQuestion.question;
		bool  isAnswerCorrect = this->m_dataBase->isAnswerCorrect(answer, question);
		iter->totalAnswerTime += time;
		if (isAnswerCorrect)
		{
			this->m_dataBase->addToCorrectAnswers(username);
			iter->correctAnswerCount++;
		}
		else
		{
			this->m_dataBase->addToWrongAnswers(username);
			iter->wrongAnswerCount++;
		}

		return isAnswerCorrect;
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;

		return false;
	}
}

void Game::removePlayer(string username)
{
	for (auto player = this->m_players.begin(); player != this->m_players.end(); player++)
	{
		if (player->username == username)
		{
			this->m_players.erase(player);

			return;
		}
	}
}

unsigned int Game::getGameId()
{
	return this->m_gameId;
}

std::vector<Question> Game::getQuestions()
{
	return this->m_questions;
}

std::vector<GameData> Game::getPlayersData()
{
	return this->m_players;
}

string Game::getQuestionsDifficulty()
{
	return this->m_questionDifficulty;
}

unsigned int Game::getNumOfQuestions()
{
	return this->m_numOfQuestions;
}

std::vector<string> Game::getPlayersInGame()
{
	std::vector<string> players;
	for (auto player = this->m_players.begin(); player != this->m_players.end(); player++)
	{
		players.push_back(player->username);
	}

	return players;
}

std::list<PlayerResults> Game::getGameResults()
{
	PlayerResults result;
	std::list<PlayerResults> results;
	for (auto player : this->m_players)
	{
		player.averageAnswerTime = player.totalAnswerTime / this->m_numOfQuestions;
		this->m_dataBase->addToPlayerGames(player.username);
		float avgAnsTime = (this->m_dataBase->getPlayerAverageAnswerTime(player.username) + player.averageAnswerTime) / this->m_dataBase->getNumOfPlayerGames(player.username);
		m_dataBase->setPlayerAverageAnswerTime(player.username, avgAnsTime);
		result.averageAnswerTime = player.averageAnswerTime;
		result.correctAnswerCount = player.correctAnswerCount;
		result.wrongAnswerCount = player.wrongAnswerCount;
		result.username = player.username;
		results.push_back(result);
	}

	return results;
}