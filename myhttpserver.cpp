#include "myhttpserver.h"
#include <evhttp.h>
#include <event.h>
#include "event2/http.h"

int CMyHttpServer::StartServer(int iPort)
{
	const char *http_addr = "0.0.0.0";
	
	m_http_server = evhttp_start(http_addr, iPort);
	if(NULL == m_http_server)
	{
		printf("====line%d:%s\n",__LINE__,"http server start failed!");
		return -1;
	}
	//设置请求超时间
	evhttp_set_timeout(m_http_server, 5);
	//设置事件处理函数，evhttp_set_cb针对每一个事件(请求)注册一个处理函数，
	//区别于evhttp_set_gencb函数，是对所有请求设置一个统一的处理函数
	//evhttp_set_cb(http_server,"/me/testpost",http_handler_testpost_msg,NULL);
	//evhttp_set_cb(http_server,"/me/testget",http_handler_testget_msg,NULL);
	
	evhttp_set_gencb(m_http_server, HttpHandle, this);

	return 0;
}

void CMyHttpServer::HttpHandle(struct evhttp_request * req, void * arg)
{
	CMyHttpServer *pThis = (CMyHttpServer *)arg;

	CMyHttpRequest request(req);
	CMyHttpResponse response;
	
	request.parse();

	if(req->type == EVHTTP_REQ_GET)
	{
		pThis->HandleGet(request, response);	
	}
	else if(req->type == EVHTTP_REQ_POST)
	{
		pThis->HandlePost(request, response);
	}
}

int CMyHttpServer::HandleGet(CMyHttpRequest & request, CMyHttpResponse & response)
{
        std::map<std::string, CMyHttpHandle *>::iterator it;
	it = m_mapHttpHandle.find(request.GetPath());
	if(it == m_mapHttpHandle.end())
	{
		printf("get path not found 404\r\n");
		return -1;
	}	
	printf("handle get request:%s", request.GetPath());
	return 0;
}

int CMyHttpServer::HandlePost(CMyHttpRequest &request, CMyHttpResponse & response)
{
        std::map<std::string, CMyHttpHandle *>::iterator it;
	it = m_mapHttpHandle.find(request.GetPath());
	if(it == m_mapHttpHandle.end())
	{
		printf("post path not found 404\r\n");
		return -1;
	}	
	printf("handle post request:%s", request.GetPath());
	return 0;
}

void CMyHttpServer::AddHandle(const std::string & strPath, CMyHttpHandle * pHandle)
{
	m_mapHttpHandle.insert(std::make_pair(strPath, pHandle));
}

void CMyHttpServer::RemoveHandle(const std::string &strPath)
{
	std::map<std::string , CMyHttpHandle *>::iterator it;
	it = m_mapHttpHandle.find(strPath);
	delete it->second;
	m_mapHttpHandle.erase(strPath);
}

void CMyHttpServer::ClearHandle()
{
	std::map<std::string, CMyHttpHandle *>::iterator it;
	
	for(it = m_mapHttpHandle.begin(); it!= m_mapHttpHandle.end(); it++)
	{
		delete it->second;
	}
	m_mapHttpHandle.clear();
}
