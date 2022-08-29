#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"

class GameRequestHandler : public IRequestHandler
{
private:
	unsigned int m_gameId;
	unsigned int m_questionCounter = 0;
	LoggedUser* m_user;
	static GameManager* m_gameManager;
	static RoomManager* m_roomManager;
	static StatisticsManager* m_statisticManager;

	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);
	RequestResult GetHighScores(RequestInfo info);
public:
	GameRequestHandler(string username, unsigned int gameId, unsigned int questionCounter);
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

};