#include "RoomManager.h"

RoomManager* RoomManager::m_ptr = nullptr;

RoomManager* RoomManager::get_instance()
{
	if (!m_ptr)
		m_ptr = new  RoomManager;
	
	return m_ptr;
}

void RoomManager::reset_instance()
{
	delete m_ptr;
	m_ptr = nullptr;
}

std::vector<string> RoomManager::getPlayersInRoom(int room_id)
{
	Room room = GetRoomById(room_id);

	return room.getAllUsers();
}

void RoomManager::addPlayerToRoom(int room_id, string username)
{
	for (int i = 0; i < this->m_rooms.size(); i++)
	{
		if (m_rooms[i].getData().id == room_id)
		{
			this->m_rooms[i].addUser(username);
			return;
		}
	}
	throw std::exception("Room Doesn't exists");
}

void RoomManager::removePlayerFromRoom(int room_id, string username)
{
	for (int i = 0; i < this->m_rooms.size(); i++)
	{
		if (m_rooms[i].getData().id == room_id)
		{
			this->m_rooms[i].removeUser(username);
			return;
		}
	}
}
void RoomManager::setGameToBeActive(int room_id)
{
	for (int i = 0; i < this->m_rooms.size(); i++)
	{
		if (m_rooms[i].getData().id == room_id)
		{
			this->m_rooms[i].SetGame();
			return;
		}
	}
}
Room RoomManager::GetRoomPlayerIsOn(string usrename)
{
	for (auto room : m_rooms)
	{
		if (std::find(room.getAllUsers().begin(), room.getAllUsers().end(), usrename) != room.getAllUsers().end())
			return room;
	}
	throw std::exception("This user isnt in a room...");
}

Room RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room room(data);
	room.addUser(user);
	this->m_rooms.push_back(room);

	return room;
}

Room RoomManager::GetRoomById(int roomId)
{
	for (auto room : this->m_rooms)
	{
		if (room.getData().id == roomId)
			return room;
	}
	throw std::exception("Room Doesn't exists");
}

void RoomManager::deleteRoom(int id)
{
	auto Iter = this->m_rooms.begin();

	while (Iter != this->m_rooms.end())
	{
		if (Iter->getData().id == id)
		{
			this->m_rooms.erase(Iter);
			break;
		}
		Iter++;
	}

}

unsigned int RoomManager::getRoomState(int id)
{
	Room room = GetRoomById(id);

	return room.getData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> allRooms;

	for (auto room : this->m_rooms)
	{
		allRooms.push_back(room.getData());
	}

	return allRooms;
}