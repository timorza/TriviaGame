#include "Server.h"

Server* Server::m_ptr = nullptr;
Communicator* Server::m_communicator = nullptr;

Server::~Server()
{
	m_communicator->reset_instance();
}

Server* Server::get_instance()
{
	if (!m_ptr)
		m_ptr = new Server;

	return m_ptr;
}

Server::Server()
{
	m_communicator = m_communicator->get_instance();
}

void Server::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

void Server::run()
{
	std::thread t_connector(&Communicator::startHandleRequests, m_communicator);
	std::string input = "";
	t_connector.detach();

	while (input != "exit")
		std::cin >> input;

	t_connector.~thread();
	std::cout << "Exited Server Succesfully" << std::endl;

}