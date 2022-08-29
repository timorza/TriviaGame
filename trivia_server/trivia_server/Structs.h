#pragma once
#include "IRequestHandler.h"
#include <ctime>
#include <list>
#include <vector>
#include <map>

class IRequestHandler;
using std::string;

//                                     ************** Structs For Classes **************

struct User
{
	string username;
	string password;
	string email;
};

struct RoomData
{
	unsigned int id;
	string roomAdmin;
	string name;
	string difficulty;
	unsigned int maxPlayers;
	unsigned int numOfQuestions;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

struct UserStatistics
{
	string username;
	float averageAnswerTime;
	unsigned int totalCorrectAnswerCount;
	unsigned int  totalWrongAnswerCount;
	int numOfPlayerGames;
};

struct Question
{
	string question;
	string difficulty;
	string firstAnswer;
	string secondAnswer;
	string thirdAnswer;
	string fourthAnswer;
	string correctAnswer;
	int correctAnswerIndex;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int  wrongAnswerCount;
	float averageAnswerTime;
};

struct GameData
{
	string username;
	float totalAnswerTime;
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int  wrongAnswerCount;
	float averageAnswerTime;
};

//                                     ************** Responses **************

struct LoginResponse
{
	unsigned int status;
};

struct  SignUpResponse
{
	unsigned int status;
};
struct  ErrorResponse
{
	string message;
};

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	unsigned int status;
	std::vector<string> players;
};

struct GetHighScoreResponse
{
	unsigned int status;
	std::map<int, string> highScores;
};

struct GetPersonalStatsResponse
{
	unsigned int status;
	UserStatistics personalStatistics;
};

struct JoinRoomResponse
{
	unsigned int status;
	string roomName;
	string difficulty;
	unsigned int questionCount;
	unsigned int answerTimeOut;
	unsigned int roomId;
};

struct CreateRoomResponse
{
	unsigned int status;
	unsigned int roomId;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::list<PlayerResults> results;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	bool isAnswerCorrect;
};

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	std::vector<string> answers;
};

struct LeaveGameResponse
{
	unsigned int status;
};

//                                     ************** Requests **************

struct LoginRequest
{
	string username;
	string password;
};

struct SignupRequest
{
	string username;
	string password;
	string email;
};

struct RequestInfo
{
	int requestId;
	std::time_t recivalTime;
	unsigned char* buffer;
};

struct RequestResult
{
	unsigned char* buffer;
	IRequestHandler* newHandler;
};

struct CreateRoomRequest
{
	string roomName;
	string difficulty;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct SubmitAnswerRequest
{
	float time;
	string answer;
};