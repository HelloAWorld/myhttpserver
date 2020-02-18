#ifndef __MY_HTTPSERVER_H__
#define __MY_HTTPSERVER_H__

#include <string>
#include <map>
#include "myhttprequest.h"
#include "myhttpresponse.h"
#include "myhttphandle.h"

class CMyHttpServer
{
public:
	int StartServer(int iPort);
	
	static void HttpHandle(struct evhttp_request * req, void * arg);
	int HandleGet(CMyHttpRequest & request, CMyHttpResponse & response);
	int HandlePost(CMyHttpRequest & request, CMyHttpResponse & response);
	
	void AddHandle(const std::string & strPath, CMyHttpHandle* pHandle);
	void RemoveHandle(const std::string & strPath);
	void ClearHandle();
private:
	int http_port;
	struct evhttp * m_http_server;
	std::string m_strHttpAddr;
	std::map<std::string, CMyHttpHandle *> m_mapHttpHandle;
};

#endif
