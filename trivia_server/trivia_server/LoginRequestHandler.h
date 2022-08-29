#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"

class LoginRequestHandler : public IRequestHandler
{
private:
	static LoginManager* m_loginManager;
	
public:
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
	RequestResult login(RequestInfo);
	RequestResult signup(RequestInfo);
};
