#ifndef __MY_HTTPSERVER_H__
#define __MY_HTTPSERVER_H__

#include "myhttprequest.h"
#include "myhttpresponse.h"

class CMyHttpServer
{
public:
	int StartServer(int iPort);
	
	int HandleGet(CMyHttpRequest & request, CMyHttpResponse & response);
	int HandlePost(CMyHttpRequest & request, CMyHttpResponse & response);
};

#endif
