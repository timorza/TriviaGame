#include "RoomMemberRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomManager* RoomMemberRequestHandler::m_roomManager = RoomManager::get_instance();
IDatabase* RoomMemberRequestHandler::m_dataBase = SqliteDataBase::get_instance();
GameManager* RoomMemberRequestHandler::m_GameManager = GameManager::getInstance();

RoomMemberRequestHandler::RoomMemberRequestHandler(string username, Room userRoom)
{
    this->m_user = new LoggedUser(username);
    this->m_room = new Room(userRoom.getData());
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
    return (info.requestId == START_GAME_REQUEST || info.requestId == STATE_ROOM_REQUEST || info.requestId == LEAVE_ROOM_REQUEST);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;
	switch (code)
	{
	case LEAVE_ROOM_REQUEST:
		myResult = leaveGame();
		break;
	case  START_GAME_REQUEST:
		myResult = startGame();
		break;
	case STATE_ROOM_REQUEST:
		myResult = getRoomState();
		myResult.newHandler = RequestHandlerFactory::createRoomMemberRequestHandler(m_user->getUsername(), *m_room);
		break;
	default:
		myResult.newHandler = nullptr;
		myResult.buffer = (unsigned char*)ERROR;
		break;
	}

	return myResult;
}

RequestResult RoomMemberRequestHandler::startGame()
{
	RequestResult myResult;
	StartGameResponse response;
	response.status = SUCCESS_CODE;
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newHandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_room->getData().id, NULL);
	
	return myResult;
}

RequestResult RoomMemberRequestHandler::getRoomState()
{
	RequestResult myResult;
	GetRoomStateResponse response;
	response.status = SUCCESS_CODE;
	try
	{
		response.hasGameBegun = m_roomManager->GetRoomById(this->m_room->getData().id).getData().isActive;
	}
	catch (const std::exception e)
	{
		response.hasGameBegun = false;
	}
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newHandler = RequestHandlerFactory::createRoomMemberRequestHandler(this->m_user->getUsername(), *m_room);
	
	return myResult;
}
RequestResult RoomMemberRequestHandler::leaveGame()
{
	RequestResult myResult;
	LeaveRoomResponse response;
	m_roomManager->removePlayerFromRoom(this->m_room->getData().id, this->m_user->getUsername());
	myResult.newHandler = RequestHandlerFactory::createMenuRequestHandler(m_user->getUsername());
	response.status = SUCCESS_CODE;
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	
	return myResult;
}