#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "JsonResponsePacket.h"
#include "RoomManager.h"
#include "GameManager.h"


class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(string username, Room userRoom);
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

private:
	static RoomManager* m_roomManager;
	static GameManager* m_GameManager;
	Room* m_room;
	LoggedUser* m_user;
	static IDatabase* m_dataBase;

	RequestResult startGame();
	RequestResult getRoomState();
	RequestResult leaveGame();
};

