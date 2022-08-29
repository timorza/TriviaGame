#include "RequestHandlerFactory.h"

RequestHandlerFactory* RequestHandlerFactory::m_ptr = nullptr;

RequestHandlerFactory* RequestHandlerFactory::get_instance()
{
	if (!m_ptr)
		m_ptr = new RequestHandlerFactory;

	return m_ptr;
}

void RequestHandlerFactory::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* loginRequestHandler = new LoginRequestHandler;
	
	return loginRequestHandler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(string user)
{
	MenuRequestHandler* menuRequestHandler = new MenuRequestHandler(user);

	return menuRequestHandler;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(string username, Room userRoom)
{
	RoomAdminRequestHandler* roomAdminRequestHandler = new RoomAdminRequestHandler(username, userRoom);

	return roomAdminRequestHandler;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(string username, Room userRoom)
{
	RoomMemberRequestHandler* roomMemberRequestHandler = new RoomMemberRequestHandler(username, userRoom);

	return roomMemberRequestHandler;
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(string username, unsigned int gameId, unsigned int questionCounter)
{
	GameRequestHandler* gameRequestHandler = new GameRequestHandler(username, gameId, questionCounter);

	return gameRequestHandler;
}

