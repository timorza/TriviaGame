using System;
using System.Collections.Generic;
using System.Text;

namespace trivia_client
{
    class GameResponeHandler
    {
        public static GetQuestionResponse getNextQuestion(Communicator com)
        {
            GetQuestionRequest request;
            GetQuestionResponse questionResponse;
            questionResponse.Answers = null;
            questionResponse.question = null;
            questionResponse.status = 0;

            request.code = (uint)Constants.requests.GET_Q_REQUEST;
            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                questionResponse = JsonResponeDeserializer.deserializeGetNexrQuestionResponse(msgFromServer);
            }

            return questionResponse;
        }
        public static SubmitAnswerResponse SubmitAnswer(SubmitAnswerRequest request, Communicator com)
        {
            SubmitAnswerResponse response;
            response.isAnswerCorrect = false;
            response.status = 0;

            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                response = JsonResponeDeserializer.deserializeSubmitAnswerResponse(msgFromServer);

            }

            return response;
        }
        public static GetGameResultsResponse getGameResults(Communicator com)
        {
            GetGameResultsRequest request;
            GetGameResultsResponse response;
            response.results = null;
            response.status = 0;
            request.code = (uint)Constants.requests.GET_GAME_RESULT_REQUEST;

            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                response = JsonResponeDeserializer.deserializeGetGameResultsResponse(msgFromServer);
            }

            return response;
        }
        public static void leaveGame(Communicator com)
        {
            LeaveGameRequest request;
            request.code = (uint)Constants.requests.LEAVE_GAME_REQUEST;

            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
            }
        }
        public static GetHighScoreResponse getHighScores(Communicator com)
        {
            GetHighScoreRequest request;
            GetHighScoreResponse response;
            response.highScores = null;
            response.status = 0;
            request.code = (uint)Constants.requests.GET_PLAYER_STATISTICS_REQUEST;

            if (com != null)
            {
                string msgToServer = JsonRequestSerializer.serializeRequest(request);
                string msgFromServer = com.SendPacket(msgToServer);
                response = JsonResponeDeserializer.deserializeHighScoresResponse(msgFromServer);
            }

            return response;
        }
    }
}
