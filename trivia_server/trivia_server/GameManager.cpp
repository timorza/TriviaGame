#include "GameManager.h"

GameManager* GameManager::m_ptr = new GameManager;

GameManager* GameManager::getInstance()
{
    if (!m_ptr)
        m_ptr = nullptr;
    return m_ptr;
}

void GameManager::resetInstance()
{
    delete m_ptr;
    m_ptr = nullptr;
}

void GameManager::createGame(Game game)
{
    this->m_games.push_back(game);
}

void GameManager::deleteGame(unsigned int gameId)
{
    for (std::vector<Game>::iterator game = this->m_games.begin(); game != this->m_games.end(); game++)
    {
        if (game->getGameId() == gameId)
        {
            this->m_games.erase(game);

            return;
        }
    }
}

Game GameManager::getGameById(unsigned int id)
{
    for (std::vector<Game>::iterator game = this->m_games.begin(); game != this->m_games.end(); game++)
    {
        if (game->getGameId() == id)
            return *game;
    }
}

bool GameManager::SumbitAnswerOfGame(string username, string answer, float time, unsigned int id)
{
    for (std::vector<Game>::iterator game = m_games.begin(); game != m_games.end(); game++)
    {
        if (game->getGameId() == id)
        {
            return game->submitAnswer(username, answer, time);
        }
    }

    throw std::exception("Game doesnt exsit");
}

Question GameManager::getNextQuestionOfPlayer(string username, unsigned int id, unsigned int* questionCounter)
{
    for (std::vector<Game>::iterator game = m_games.begin(); game != m_games.end(); game++)
    {
        if (game->getGameId() == id)
        {
            return game->getNextQuestion(username, questionCounter);
        }
    }

    throw std::exception("Game doesnt exsit");
}

std::list<PlayerResults> GameManager::getGameResults(unsigned int id)
{
    for (std::vector<Game>::iterator game = m_games.begin(); game != m_games.end(); game++)
    {
        if (game->getGameId() == id)
        {
            return game->getGameResults();
        }
    }

    throw std::exception("Game doesnt exsit");
}

void GameManager::removeUserFromGame(string username, unsigned int id)
{
    for (std::vector<Game>::iterator game = m_games.begin(); game != m_games.end(); game++)
    {
        if (game->getGameId() == id)
        {
            game->removePlayer(username);
            return;
        }
    }

    throw std::exception("Game doesnt exsit");
}