using System;
using System.Collections.Generic;
using System.Text;

namespace trivia_client
{
    class LobbyResponeHandler
    {
        public static GetPlayersInRoomResponse GetPlayersInRoom(Communicator com, uint RoomId)
        {
            GetPlayersInRoomRequest getPlayersInRoom;
            GetPlayersInRoomResponse playersInRoomResponse;
            string msgFromServer = "";
            playersInRoomResponse.playersInRoom = null;
            playersInRoomResponse.status = 0;
            getPlayersInRoom.roomId = RoomId;

            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(getPlayersInRoom);
                msgFromServer = com.SendPacket(msgToServer);
                playersInRoomResponse = JsonResponeDeserializer.deserializeGetPlayersInRoomRespone(msgFromServer);

            }
            return playersInRoomResponse;
        }
        public static bool checkIfGameHasStarted(Communicator com)
        {
            GetRoomStateRequest request;
            GetRoomStateRespone respone;
            request.code = 0;
            respone.GameBegun = false;
            respone.status = 0;

            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                respone = JsonResponeDeserializer.deserializeRoomStateResponse(msgFromServer);

            }
            return respone.GameBegun;
        }
        public static void CloseRoom(Communicator com)
        {
            CloseRoomRequest closeRoomRequest;
            closeRoomRequest.code = (uint)Constants.requests.CLOSE_ROOM_REQUEST;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(closeRoomRequest);
                string msgFromServer = com.SendPacket(msgToServer);
            }
        }
        public static void LeaveRoom(Communicator com)
        {
            LeaveRoomRequest request;
            request.code = (uint)Constants.requests.LEAVE_ROOM_REQUEST;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
            }
        }
        public static void StartGame(Communicator com)
        {
            StartGameRequest request;
            request.code = 0;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
            }
        }
    }
}
