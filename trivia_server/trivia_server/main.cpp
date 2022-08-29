#pragma comment (lib, "ws2_32.lib")


#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#define PORT 25667
#pragma comment (lib, "ws2_32.lib")


#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#define PORT 37696
int main()
{
	Server* myServer;
	try
	{
		WSAInitializer wsaInit;
		myServer = Server::get_instance();
		myServer->run();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}


