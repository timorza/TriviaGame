#pragma once
#include "Communicator.h"

class Server
{
private:
	static  Server* m_ptr;
	Server();
	~Server();
	static Communicator* m_communicator;
public:
	static Server* get_instance();
	static void reset_instance();
	void run();
};
