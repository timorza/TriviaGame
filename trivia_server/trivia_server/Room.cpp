#include "Room.h"

Room::Room(RoomData data)
{
	this->m_metadata = data;
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	std::vector<LoggedUser>::iterator usersItr;
	
	for (usersItr = this->m_users.begin(); usersItr != this->m_users.end(); usersItr++)
	{
		if (usersItr->getUsername() == user.getUsername())
		{
			this->m_users.erase(usersItr);
			break;
		}
	}
}

std::vector<string> Room::getAllUsers()
{
	std::vector<LoggedUser>::iterator usersItr;
	std::vector<string> users;

	for (usersItr = this->m_users.begin(); usersItr != this->m_users.end(); usersItr++)
	{
		users.push_back(usersItr->getUsername());
	}

	return users;
}

void Room::SetGame()
{
	this->m_metadata.isActive = true;
}

RoomData Room::getData()
{
	return this->m_metadata;
}
