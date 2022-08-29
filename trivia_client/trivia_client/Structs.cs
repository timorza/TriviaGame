using System;
using System.Collections.Generic;
using System.Text;

namespace trivia_client
{
	//**************************** Const *********************************//
	static class Constants
	{
		public const int BUFFER_START_LEN = 6;
		public const int MAX_PASSWORD_LENGTH = 20;
		public const int MIN_PASSWORD_LENGTH = 8;
		public const int MAX_USERNAME_LENGTH = 15;
		public const int MIN_USERNAME_LENGTH = 6;
		public const int Success = 1;
		public const int Fail = 0;
		public const int SEC_IN_MIN = 60;

		public enum requests
		{
			LOGIN_REQUEST = 20, SIGNUP_REQUEST = 21, LOGOUT_REQUEST,
			GET_ROOMS_REQUEST, GET_PLAYERS_REQUEST, JOIN_ROOM_REQUEST, CREATE_ROOM_REQUEST, GET_HIGH_SCORES_REQUEST,
			CLOSE_ROOM_REQUEST, START_GAME_REQUEST, STATE_ROOM_REQUEST, LEAVE_ROOM_REQUEST,
			GET_Q_REQUEST, SUBMIT_ANSWER_REQUEST, GET_GAME_RESULT_REQUEST,
			LEAVE_GAME_REQUEST, GET_PLAYER_STATISTICS_REQUEST
		};
	}

	//**************************** Requests *********************************//
	struct LoginRequest
	{
		public string username;
		public string password;
	};
	struct StartGameRequest
	{
		public uint code;
	};
	struct SignupRequest
	{
		public string username;
		public string password;
		public string email;
		public SignupRequest(string username, string password, string email)
		{
			this.username = username;
			this.password = password;
			this.email = email;
		}
	};
	struct JoinRoomRequest
	{
		public uint roomId;
	};
	struct GetRoomStateRequest
	{
		public uint code;
	};
	struct GetPlayersInRoomRequest
	{
		public uint roomId;
	};

	struct CreateRoomRequest
	{
		public string roomName;
		public string difficulty;
		public uint maxUsers;
		public uint questionCount;
		public uint answerTimeOut;
	};
	struct LogoutRequest
	{
		public uint code;
	};

	struct CloseRoomRequest
	{
		public uint code;
	};
	struct LeaveRoomRequest
	{
		public uint code;
	};
	struct GetQuestionRequest
	{
		public uint code;
	};
	struct StatisticsRequest
	{
		public uint code;
	};

	struct SubmitAnswerRequest
	{
		public float time;
		public string answer;
	};
	struct GetGameResultsRequest
	{
		public uint code;
	};
	struct LeaveGameRequest
	{
		public uint code;
	};
	struct GetHighScoreRequest
	{
		public uint code;
	}

	//**************************** Responses  *********************************//
	struct LoginResponse
	{
		public uint status;
	};

	struct SignUpResponse
	{
		public uint status;
	};
	struct GetHighScoreResponse
	{
		public uint status;
		public Dictionary<int, string> highScores;
	};
	struct ErrorResponse
	{
		public string message;
	};
	struct JoinRoomResponse
	{
		public uint status;
		public string roomName;
		public string difficulty;
		public uint questionCount;
		public uint answerTimeOut;
		public uint roomId;
	};
	struct CreateRoomResponse
	{
		public string roomName;
		public uint status;
		public uint roomId;
	};
	struct GetRoomStateRespone
	{
		public uint status;
		public bool GameBegun;
	}
	struct StatisticsResponse
	{
		public string username;

		public uint numPlayedGames;

		public uint correctAnswerCount;

		public uint wrongAnswerCount;

		public float averangeAnswerTime;
	};
	struct GetPlayersInRoomResponse
	{
		public uint status;
		public List<string> playersInRoom;
	};
	struct GetQuestionResponse
	{
		public uint status;
		public string question;
		public List<string> Answers;
	};
	struct SubmitAnswerResponse
	{
		public uint status;
		public bool isAnswerCorrect;
	};
	struct GetGameResultsResponse
	{
		public uint status;
		public List<StatisticsResponse> results;
	};

}
