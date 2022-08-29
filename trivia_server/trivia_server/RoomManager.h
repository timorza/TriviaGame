#pragma once
#include "Room.h"
#include <map>

class RoomManager
{
private:
	RoomManager() = default;
	static RoomManager* m_ptr;
	std::vector<Room> m_rooms; // all open roomes

public:
	static RoomManager* get_instance();
	static void reset_instance();
	std::vector<string> getPlayersInRoom(int room_id);
	void addPlayerToRoom(int room_id, string username);
	void removePlayerFromRoom(int room_id, string username);
	Room GetRoomPlayerIsOn(string usrename);
	Room createRoom(LoggedUser user, RoomData data);
	Room GetRoomById(int roomId);
	void  setGameToBeActive(int room_id);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
};