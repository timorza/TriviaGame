using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;

namespace trivia_client
{
    class JsonRequestSerializer
    {
        public static string serializeRequest(LoginRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.LOGIN_REQUEST, json);
        }
        public static string serializeRequest(GetHighScoreRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.GET_PLAYER_STATISTICS_REQUEST, json);
        }
        public static string serializeRequest(GetRoomStateRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.STATE_ROOM_REQUEST, json);
        }
        public static string serializeRequest(CloseRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.CLOSE_ROOM_REQUEST, json);
        }
        public static string serializeRequest(GetQuestionRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.GET_Q_REQUEST, json);
        }
        public static string serializeRequest(SubmitAnswerRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.SUBMIT_ANSWER_REQUEST, json);
        }
        public static string serializeRequest(GetGameResultsRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.GET_GAME_RESULT_REQUEST, json);
        }
        public static string serializeRequest(StartGameRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.START_GAME_REQUEST, json);
        }
        public static string serializeRequest(LeaveGameRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.LEAVE_GAME_REQUEST, json);
        }
        public static string serializeRequest(SignupRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.SIGNUP_REQUEST, json);
        }
        public static string serializeRequest(LogoutRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.LOGOUT_REQUEST, json);
        }
        public static string serializeRequest(LeaveRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.LEAVE_ROOM_REQUEST, json);
        }
        public static string serializeRequest(JoinRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.JOIN_ROOM_REQUEST, json);
        }
        public static string serializeRequest(GetPlayersInRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.GET_PLAYERS_REQUEST, json);
        }
        public static string serializeRequest(CreateRoomRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.CREATE_ROOM_REQUEST, json);
        }
        public static string GetStatisticsRequest(StatisticsRequest request)
        {
            string json = JsonConvert.SerializeObject(request, Formatting.None);

            return serializeMsg((int)Constants.requests.GET_PLAYER_STATISTICS_REQUEST, json);
        }
        private static string serializeMsg(int RequestId, string msg)
        {
            string length = msg.Length.ToString().PadLeft(4, '0');
            string MsgToServer = RequestId.ToString() + length + msg;

            return MsgToServer;
        }
    }
    class JsonResponeDeserializer
    {
        public static LoginResponse deserializeLoginRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            LoginResponse response = JsonConvert.DeserializeObject<LoginResponse>(JsonMsg);

            return response;
        }
        public static ErrorResponse deserializeErrorRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            ErrorResponse response = JsonConvert.DeserializeObject<ErrorResponse>(JsonMsg);

            return response;
        }
        public static SignUpResponse deserializeSignUpRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            SignUpResponse response = JsonConvert.DeserializeObject<SignUpResponse>(JsonMsg);

            return response;
        }
        public static StatisticsResponse deserializeGetStatisticsRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            StatisticsResponse response = JsonConvert.DeserializeObject<StatisticsResponse>(Buffer);

            return response;
        }
        public static JoinRoomResponse deserializeJoinRoomRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            JoinRoomResponse response = JsonConvert.DeserializeObject<JoinRoomResponse>(JsonMsg);

            return response;
        }
        public static GetPlayersInRoomResponse deserializeGetPlayersInRoomRespone(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            GetPlayersInRoomResponse response = JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(JsonMsg);

            return response;
        }
        public static CreateRoomResponse deserializeCreateRoomResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            CreateRoomResponse response = JsonConvert.DeserializeObject<CreateRoomResponse>(JsonMsg);

            return response;
        }
        public static GetGameResultsResponse deserializeGetGameResultsResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            GetGameResultsResponse response = JsonConvert.DeserializeObject<GetGameResultsResponse>(JsonMsg);

            return response;
        }
        public static GetQuestionResponse deserializeGetNexrQuestionResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            GetQuestionResponse response = JsonConvert.DeserializeObject<GetQuestionResponse>(JsonMsg);

            return response;
        }
        public static SubmitAnswerResponse deserializeSubmitAnswerResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            SubmitAnswerResponse response = JsonConvert.DeserializeObject<SubmitAnswerResponse>(JsonMsg);

            return response;
        }

        public static GetRoomStateRespone deserializeRoomStateResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            GetRoomStateRespone response = JsonConvert.DeserializeObject<GetRoomStateRespone>(JsonMsg);

            return response;
        }
        public static GetHighScoreResponse deserializeHighScoresResponse(string Buffer)
        {
            string JsonMsg = Buffer.Substring(Constants.BUFFER_START_LEN);
            GetHighScoreResponse response = JsonConvert.DeserializeObject<GetHighScoreResponse>(JsonMsg);

            return response;
        }
    }
}
