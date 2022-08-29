#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

class RequestHandlerFactory
{
private:
	static RequestHandlerFactory* m_ptr;

	RequestHandlerFactory() = default;
	~RequestHandlerFactory() = default;
public:
	static LoginRequestHandler* createLoginRequestHandler();
	static MenuRequestHandler* createMenuRequestHandler(string user);

	static RoomAdminRequestHandler* createRoomAdminRequestHandler(string username, Room userRoom);
	static RoomMemberRequestHandler* createRoomMemberRequestHandler(string username, Room userRoom);

	static GameRequestHandler* createGameRequestHandler(string username, unsigned int gameId, unsigned int questionCounter);

	static RequestHandlerFactory* get_instance();
	static void reset_instance();
};