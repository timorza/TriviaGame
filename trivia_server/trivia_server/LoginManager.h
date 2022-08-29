#pragma once
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include <algorithm>

class LoginManager
{
private:
	static  LoginManager* m_ptr;
	LoginManager();
	~LoginManager();
	static IDatabase* m_database;
	std::vector<LoggedUser> m_loggedusers;
public:
	static LoginManager* get_instance();
	static void reset_instance();
	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);

};