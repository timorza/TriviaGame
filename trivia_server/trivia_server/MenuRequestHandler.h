#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "LoginManager.h"

class MenuRequestHandler : public IRequestHandler
{
private:
	

	LoggedUser* m_user;
	static RoomManager* m_roomManager;
	static StatisticsManager* m_statisticsManager;
	static LoginManager* m_loginManager;

	RequestResult logout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);

	bool IsIdExists(int id);
public:
	MenuRequestHandler(string username);
	
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);



};