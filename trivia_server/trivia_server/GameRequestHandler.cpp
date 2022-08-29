#include "GameRequestHandler.h"
#include "RequestHandlerFactory.h"

GameManager* GameRequestHandler::m_gameManager = GameManager::getInstance();
RoomManager* GameRequestHandler::m_roomManager = RoomManager::get_instance();
StatisticsManager* GameRequestHandler::m_statisticManager = StatisticsManager::get_instance();

RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	RequestResult myResult;
	GetQuestionResponse response;

	try
	{
		Question nextQuestion = this->m_gameManager->getNextQuestionOfPlayer(this->m_user->getUsername(), m_gameId, &this->m_questionCounter);
		response.question = nextQuestion.question;
		response.answers.push_back(nextQuestion.firstAnswer);
		response.answers.push_back(nextQuestion.secondAnswer);
		response.answers.push_back(nextQuestion.thirdAnswer);
		response.answers.push_back(nextQuestion.fourthAnswer);
	}
	catch (const std::exception e)
	{
		response.question = e.what();
		response.answers = std::vector<string>();
	}
	response.status = SUCCESS_CODE;
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newHandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_gameId, this->m_questionCounter);
	
	return myResult;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	RequestResult myResult;
	SubmitAnswerResponse response;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);

	try
	{
		response.isAnswerCorrect = this->m_gameManager->SumbitAnswerOfGame(this->m_user->getUsername(), request.answer, request.time, m_gameId);
		response.status = SUCCESS_CODE;
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		response.isAnswerCorrect = true;
		response.status = ERR_RESPONSE;
	}

	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	myResult.newHandler = RequestHandlerFactory::createGameRequestHandler(this->m_user->getUsername(), this->m_gameId, this->m_questionCounter);

    return myResult;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	RequestResult myResult;
	GetGameResultsResponse response;
	
	response.results = this->m_gameManager->getGameById(m_gameId).getGameResults();
	response.status = SUCCESS_CODE;
	this->m_gameManager->deleteGame(this->m_gameId);
	myResult.newHandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);

    return myResult;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	RequestResult myResult;
	LeaveGameResponse response;
	try
	{
		this->m_gameManager->removeUserFromGame(this->m_user->getUsername(), this->m_gameId);
		response.status = SUCCESS_CODE;
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
		response.status = ERR_RESPONSE;
	}
	myResult.newHandler = RequestHandlerFactory::createMenuRequestHandler(this->m_user->getUsername());
	myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);

    return myResult;
}

RequestResult GameRequestHandler::GetHighScores(RequestInfo info)
{
	RequestResult myResult;
	GetHighScoreResponse respone;
	try
	{
		respone.highScores = m_statisticManager->getHighScore(m_gameManager->getGameById(m_gameId));
		respone.status = SUCCESS_CODE;
		myResult.buffer = JsonResponsePacketSerializer::serializeResponse(respone);
	}
	catch (const std::exception e)
	{
		ErrorResponse respone;
		respone.message = e.what();
		myResult.buffer = JsonResponsePacketSerializer::serializeResponse(respone);
		myResult.newHandler = nullptr;
	}

	return myResult;
}

GameRequestHandler::GameRequestHandler(string username, unsigned int gameId, unsigned int questionCounter)
{
    this->m_user = new LoggedUser(username);
    this->m_gameId = gameId;
    this->m_questionCounter = questionCounter;
}

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
    return (info.requestId == GET_Q_REQUEST || info.requestId == info.requestId == GET_HIGH_SCORES_REQUEST || info.requestId == SUBMIT_ANSWER_REQUEST || info.requestId == GET_GAME_RESULT_REQUEST || info.requestId == LEAVE_GAME_REQUEST);
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult myResult;
    int code = info.requestId;
    switch (code)
    {
    case GET_Q_REQUEST:
		myResult = getQuestion(info);
		break;
	case SUBMIT_ANSWER_REQUEST:
		myResult = submitAnswer(info);
		break;
	case  GET_GAME_RESULT_REQUEST:
		myResult = getGameResults(info);
		break;
	case GET_HIGH_SCORES_REQUEST:
		myResult = GetHighScores(info);
		break;
	case  LEAVE_GAME_REQUEST:
		myResult = leaveGame(info);
		break;
	default:
		myResult.newHandler = nullptr;
		myResult.buffer = (unsigned char*)ERROR;
		break;
	}

	return myResult;
}
