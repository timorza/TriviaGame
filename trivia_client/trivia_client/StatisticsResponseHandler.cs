using System;
using System.Collections.Generic;
using System.Text;

namespace trivia_client
{
	class StatisticsResponseHandler
	{

		public static StatisticsResponse GetStatisticsOfUser(Communicator com)
		{
			StatisticsRequest request;
			request.code = Convert.ToUInt32(Constants.requests.GET_PLAYER_STATISTICS_REQUEST);
			string msgToServer = JsonRequestSerializer.GetStatisticsRequest(request);
			string msgFromServer = com.SendPacket(msgToServer);
			StatisticsResponse response = JsonResponeDeserializer.deserializeGetStatisticsRespone(msgFromServer);

			return response;
		}
	}
}
