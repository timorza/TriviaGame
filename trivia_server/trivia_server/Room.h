#pragma once
#include "LoggedUser.h"
#include "Structs.h"
#include <vector>


class Room
{
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

public:
	Room() = default;
	Room(RoomData data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<string> getAllUsers();
	void SetGame();
	RoomData getData();
};