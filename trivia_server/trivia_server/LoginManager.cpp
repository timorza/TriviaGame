#include "LoginManager.h"

LoginManager* LoginManager::m_ptr = nullptr;
IDatabase* LoginManager::m_database = nullptr;

LoginManager::LoginManager()
{
	this->m_database = SqliteDataBase::get_instance();
}

LoginManager::~LoginManager()
{
	SqliteDataBase::reset_instance();
	this->m_loggedusers.clear();
}

LoginManager* LoginManager::get_instance()
{
	if (!m_ptr)
		m_ptr = new LoginManager;

	return m_ptr;
}

void LoginManager::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (!this->m_database->doesUserExist(username))
		this->m_database->addNewUser(username, password, email);
	else
		throw std::exception("User already exists");
}

void LoginManager::login(std::string username, std::string password)
{
	if (this->m_database->doesUserExist(username))
	{
		if (this->m_database->doesPasswordMatch(password, username))
			this->m_loggedusers.push_back(LoggedUser(username));
		else
			throw std::exception("Password doesn't match");
	}
	else
		throw std::exception("User doesn't exist");

}

void LoginManager::logout(std::string username)
{
	auto loggedUserItr = m_loggedusers.begin();
	while (loggedUserItr != m_loggedusers.end())
	{
		if (loggedUserItr->getUsername() == username)
		{
			delete& loggedUserItr;
			m_loggedusers.erase(loggedUserItr);
			return;
		}
		loggedUserItr++;
	}
	throw std::exception("Couldn't find user to log out");
}
