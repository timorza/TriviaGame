#pragma once
#include <iostream>
#include "Structs.h"

struct RequestResult;
struct RequestInfo;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
