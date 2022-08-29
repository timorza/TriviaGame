#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

void Helper::sendData(SOCKET sc, std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		std::string error = "Error while sending message to client";
		throw std::exception(error.c_str());
	}
}

char* Helper::getPartFromSocket(SOCKET sc, int bytesNum)
{
	if (bytesNum == 0)
		return (char*)"";

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, 0);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

std::string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

int Helper::getIntPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum);
	return atoi(s);
}
