#include "LoginRequestHandler.h"
#include "JsonResponsePacket.h"
#include "RequestHandlerFactory.h"

LoginManager* LoginRequestHandler::m_loginManager = m_loginManager->get_instance();

RequestResult LoginRequestHandler::login(RequestInfo reqInfo)
{
	RequestResult myResult;
	bool success = true;
	LoginResponse response;
	LoginRequest myRequest = JsonRequestPacketDeserializer::DeserializeLoginRequest(reqInfo.buffer);
	try
	{
		m_loginManager->login(myRequest.username, myRequest.password);
	}
	catch (...)
	{
		success = false;
		response.status = ERR_RESPONSE;
		myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
		myResult.newHandler = RequestHandlerFactory::createLoginRequestHandler();
	}
	if (success)
	{
		myResult.newHandler = RequestHandlerFactory::createMenuRequestHandler(myRequest.username);
		response.status = SUCCESS_CODE;
		myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	}

	return myResult;
}

RequestResult LoginRequestHandler::signup(RequestInfo reqInfo)
{
	RequestResult myResult;
	bool success = true;
	SignUpResponse response;
	SignupRequest myRequest = JsonRequestPacketDeserializer::DeserializeSignupRequest(reqInfo.buffer);
	try
	{
		m_loginManager->signup(myRequest.username, myRequest.password, myRequest.email);
	}
	catch (...)
	{
		success = false;
		response.status = ERR_RESPONSE;
		myResult.newHandler = RequestHandlerFactory::createLoginRequestHandler();
		myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	}
	if (success)
	{
		myResult.newHandler = RequestHandlerFactory::createMenuRequestHandler(myRequest.username);
		response.status = SUCCESS_CODE;
		myResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	}

	return myResult;
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.requestId == LOGIN_REQUEST || info.requestId == SIGNUP_REQUEST)
		return true;
	else
		return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult reqResult;
	if (info.requestId == LOGIN_REQUEST)
	{
		reqResult = login(info);
	}
	else if (info.requestId == SIGNUP_REQUEST)
	{
		reqResult = signup(info);
	}
	else
	{
		ErrorResponse response;
		response.message = ERROR;
		reqResult.buffer = JsonResponsePacketSerializer::serializeResponse(response);
		reqResult.newHandler = nullptr;
	}

	return reqResult;
}
