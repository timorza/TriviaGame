#pragma once
#include "WSAInitializer.h"
#include "IRequestHandler.h"
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacket.h"
#include "RequestHandlerFactory.h"
#include <iostream>
#include <map>
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#define PORT 37696
#define BUFFER_SIZE 1024
#define CODE_LENGTH 2
#define MSG_LENGTH 4

class Communicator
{
private:

	static  Communicator* m_ptr;
	
	SOCKET m_serverSocket;
	std::map <SOCKET, IRequestHandler*> m_clients;

	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	Communicator();
	~Communicator();

	RequestInfo getMsgFromClient(SOCKET clientSocket);
	RequestResult PraseData(RequestInfo recived, RequestResult res);
public:
	static Communicator* get_instance();
	static void reset_instance();
	void startHandleRequests();
};