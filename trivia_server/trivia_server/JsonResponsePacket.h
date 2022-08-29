#pragma once
#include "json.hpp"
#include "structs.h"
#include "Helper.h"

using json = nlohmann::json;

enum requests {
	LOGIN_REQUEST = 20, SIGNUP_REQUEST = 21, LOGOUT_REQUEST,
	GET_ROOMS_REQUEST, GET_PLAYERS_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, GET_HIGH_SCORES_REQUEST,
	CLOSE_ROOM_REQUEST, START_GAME_REQUEST, STATE_ROOM_REQUEST, LEAVE_ROOM_REQUEST,
	GET_Q_REQUEST, SUBMIT_ANSWER_REQUEST, GET_GAME_RESULT_REQUEST, LEAVE_GAME_REQUEST, GET_PERSONAL_STATISTICS
};

enum responses {
	LOGIN_RESPONSE = 20, SIGNUP_RESPONSE = 21, LOGOUT_RESPONSE,
	GET_ROOMS_RESPONSE, GET_PLAYERS_RESPONSE, JOIN_ROOM_RESPONSE, CREATE_ROOM_RESPONSE, GET_HIGH_SCORES_RESPONSE,
	CLOSE_ROOM_RESPONSE, START_GAME_RESPONSE, STATE_ROOM_RESPONSE, LEAVE_ROOM_RESPONSE, GET_GAME_RESULT_RESPONSE,
	SUBMIT_ANSWER_RESPONSE, GET_Q_RESPONSE, LEAVE_GAME_RESPONSE
};

#define LENGTH_BYTES 4
#define BUFFER_START_LEN 6
#define ERR_RESPONSE 0
#define SUCCESS_CODE 1
#define PASSWORD "password"
#define EMAIL "email"
#define USERNAME "username"
#define ID "id"
#define ROOM_ID "roomId"
#define ROOMNAME "roomName" 
#define MAX_USERS "maxUsers"
#define NUM_Q "questionCount"
#define DIFFICULTY "difficulty"
#define TOTAL_ANSWER_TIME "answerTimeout"
#define TOTAL_CORRECT_ANSWERS "totalCorrectAnswerCount"
#define AVREGE_ANSWER_TIME "averangeAnswerTime"
#define TOTAL_WRONG_ANSWERS "totalWrongAnswerCount"
#define NUM_OF_PLAYED_GAMES "numOfPlayerGames"
#define STATUS "status"
#define ERROR "message"
#define ROOMS "rooms"
#define GAME_BEGUN "GameBegun"
#define PLAYERS_IN_ROOM "PlayersInRoom"
#define USER_STATISTICS "personalStatistics"
#define HIGH_SCORES "highScores"
#define RESULTS "Results"
#define IS_ANSWER_CORRECT "isAnswerCorrect" 
#define QUESTION "Question"
#define ANSWERS "Answers"
#define ANSWER "answer"
#define ANSWER_TIME_OUT "answerTimeOut"
#define CORRECT_ANSWER "correctAnswer"
#define TIME "time"
#define COMMA ","

static class JsonResponsePacketSerializer
{
public:
	static JsonResponsePacketSerializer* get_instance();
	static void reset_instance();

	static unsigned char* serializeResponse(LoginResponse response);
	static unsigned char* serializeResponse(SignUpResponse response);
	static unsigned char* serializeResponse(ErrorResponse response);
	static unsigned char* serializeResponse(LogoutResponse response);
	static unsigned char* serializeResponse(GetRoomsResponse response);
	static unsigned char* serializeResponse(GetPlayersInRoomResponse response);
	static unsigned char* serializeResponse(JoinRoomResponse response);
	static unsigned char* serializeResponse(CreateRoomResponse response);
	static unsigned char* serializeResponse(GetHighScoreResponse response);
	static unsigned char* serializeResponse(CloseRoomResponse response);
	static unsigned char* serializeResponse(StartGameResponse response);
	static unsigned char* serializeResponse(GetRoomStateResponse response);
	static unsigned char* serializeResponse(LeaveRoomResponse response);
	static unsigned char* serializeResponse(GetGameResultsResponse response);
	static unsigned char* serializeResponse(SubmitAnswerResponse response);
	static unsigned char* serializeResponse(GetQuestionResponse response);
	static unsigned char* serializeResponse(LeaveGameResponse response);
	static unsigned char* serializeResponse(GetPersonalStatsResponse response);

private:
	static  JsonResponsePacketSerializer* m_ptr;
	JsonResponsePacketSerializer() = default;

	static unsigned char* seralizingMsg(int responseNum, string msg);

	static string creatingResponseData(int respone_code);

	static std::list<string> vectorToList(std::vector<string> src);
};


static class JsonRequestPacketDeserializer
{
public:
	static JsonRequestPacketDeserializer* get_instance();
	static void reset_instance();

	static LoginRequest DeserializeLoginRequest(unsigned char* buffer);
	static SignupRequest DeserializeSignupRequest(unsigned char* buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(unsigned char* buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(unsigned char* buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(unsigned char* buffer);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(unsigned char* buffer);

private:
	static  JsonRequestPacketDeserializer* m_ptr;
	JsonRequestPacketDeserializer() = default;

	static json DeseralizingMsg(unsigned char* buffer);
};
