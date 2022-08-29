#include "RoomAdminRequestHandler.h"
#include "RequestHandlerFactory.h"

RoomManager* RoomAdminRequestHandler::m_roomManager = RoomManager::get_instance();
GameManager* RoomAdminRequestHandler::m_gameManager = GameManager::getInstance();
IDatabase* RoomAdminRequestHandler::m_dataBase = SqliteDataBase::get_instance();

RoomAdminRequestHandler::RoomAdminRequestHandler(string username, Room userRoom)
{
    this->m_user = new LoggedUser(username);
    this->m_room = new Room(userRoom.getData());
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
    return (info.requestId == CLOSE_ROOM_REQUEST || info.requestId == START_GAME_REQUEST || info.requestId == GET_PLAYERS_REQUEST);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult myResult;
	int code = info.requestId;

	switch (code)
	{
	case CLOSE_ROOM_REQUEST:
		myResult = closeRoom();
		break;
	case  START_GAME_REQUEST:
		myResult = startGame();
		break;
	case GET_PLAYERS_REQUEST:
		myResult = getPlayersInRoom(info, false, this->m_user->getUsername(), *m_room);
		break;
	default:
		myResult.newHandler = nullptr;
		myResult.buffer = (unsigned char*)ERROR;
		break;
	}

	return myResult;
}

RequestResult RoomAdminRequestHandler::closeRoom()
{
	RequestResult myResult;
	CloseRoomResponse response;
	response.status = SUCCESS_CODE;
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newHandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	m_roomManager->deleteRoom(m_room->getData().id);

	return myResult;
}

RequestResult RoomAdminRequestHandler::startGame()
{
	RequestResult myResult;
	StartGameResponse response;
	response.status = SUCCESS_CODE;
	m_roomManager->setGameToBeActive(m_room->getData().id);
	RoomData roomdata = this->m_room->getData();
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	RoomData data = this->m_room->getData();
	std::vector<Question>questions = this->m_dataBase->getQuestions(data.difficulty, this->m_room->getData().numOfQuestions);
	std::vector<GameData>players = std::vector<GameData>();
	
	for (auto player : this->m_roomManager->GetRoomById(m_room->getData().id).getAllUsers())
	{
		GameData gameData;
		gameData.username = player;
		gameData.currentQuestion = Question();
		players.push_back(gameData);
	}

	Game newGame(data.id, data.difficulty, data.numOfQuestions, questions, players);
	this->m_gameManager->createGame(newGame);
	myResult.newHandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), roomdata.id, NULL);

	return myResult;
}
RequestResult RoomAdminRequestHandler::getPlayersInRoom(RequestInfo info, bool isMember, string username, Room room)
{
	RequestResult myResult;
	GetPlayersInRoomResponse respone;
	GetPlayersInRoomRequest myRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer);
	try
	{
		respone.players = m_roomManager->getPlayersInRoom(myRequest.roomId);
		respone.status = SUCCESS_CODE;
		if (isMember)
			myResult.newHandler = RequestHandlerFactory::createRoomMemberRequestHandler(username, room);
		else
			myResult.newHandler = RequestHandlerFactory::createRoomAdminRequestHandler(username, room);
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		respone.players = std::vector<string>();
		respone.status = ERR_RESPONSE;
		myResult.newHandler = RequestHandlerFactory::createMenuRequestHandler(username);
	}
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(respone);

	return myResult;
}
