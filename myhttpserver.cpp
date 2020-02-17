#include "myhttpserver.h"
#include <evhttp.h>
#include <event.h>
#include "event2/http.h"

int CMyHttpServer::StartServer(int iPort)
{
	struct evhttp *http_server = NULL;
	const char *http_addr = "0.0.0.0";
	
	http_server = evhttp_start(http_addr, iPort);
	if(NULL == http_server)
	{
		printf("====line%d:%s\n",__LINE__,"http server start failed!");
		return -1;
	}
	//设置请求超时间
	evhttp_set_timeout(http_server, 5);
	//设置事件处理函数，evhttp_set_cb针对每一个事件(请求)注册一个处理函数，
	//区别于evhttp_set_gencb函数，是对所有请求设置一个统一的处理函数
	//evhttp_set_cb(http_server,"/me/testpost",http_handler_testpost_msg,NULL);
	//evhttp_set_cb(http_server,"/me/testget",http_handler_testget_msg,NULL);
	
	return 0;
}

int CMyHttpServer::HandleGet(CMyHttpRequest & request, CMyHttpResponse & response)
{
	return 0;
}

int CMyHttpServer::HandlePost(CMyHttpRequest &request, CMyHttpResponse & response)
{
	return 0;
}
