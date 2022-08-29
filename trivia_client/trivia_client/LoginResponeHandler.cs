using System;
using System.Collections.Generic;
using System.Text;

namespace trivia_client
{
    class LoginResponeHandler
	{
		public static string CheckSignUp(Communicator com, SignupRequest request)
		{
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				if (MsgFromServer[0].ToString() == Constants.Fail.ToString())
				{
					ErrorResponse response = JsonResponeDeserializer.deserializeErrorRespone(MsgFromServer);
					return response.message;
				}
				SignUpResponse respone = JsonResponeDeserializer.deserializeSignUpRespone(MsgFromServer);
				if (respone.status == Constants.Success)
					return null;
			}
			return "Not connected to the server";

		}

		public static bool CheckLogin(Communicator com, LoginRequest request)
		{
			if (com != null)
			{
				string MsgToServer = JsonRequestSerializer.serializeRequest(request);
				string MsgFromServer = com.SendPacket(MsgToServer);
				LoginResponse respone = JsonResponeDeserializer.deserializeLoginRespone(MsgFromServer);

				return respone.status == Constants.Success;
			}

			return false;
		}

	}
}
