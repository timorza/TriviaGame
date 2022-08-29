#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "JsonResponsePacket.h"
#include "RoomMemberRequestHandler.h"

class RoomAdminRequestHandler : public IRequestHandler
{
private:
	Room* m_room;
	LoggedUser* m_user;

	static RoomManager* m_roomManager;
	static GameManager* m_gameManager;
	static IDatabase* m_dataBase;

	RequestResult closeRoom();
	RequestResult startGame();
	static RequestResult getPlayersInRoom(RequestInfo info, bool isMember, string username, Room room);

	friend class RoomMemberRequestHandler;


public:
	RoomAdminRequestHandler(string username, Room userRoom);
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
};