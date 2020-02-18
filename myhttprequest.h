#ifndef __MY_HTTPREQUEST_H__
#define __MY_HTTPREQUEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <evhttp.h>
#include <event.h>
#include <string.h>
#include "event2/http.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include "event2/bufferevent_compat.h"
#include "event2/http_struct.h"
#include "event2/http_compat.h"
#include "event2/util.h"
#include "event2/listener.h"

class CMyHttpRequest
{
public:
	CMyHttpRequest(struct evhttp_request *req);

	int parse();

	const char * GetPath();
	
	const char * GetQuery(const char * data_name);
	
private:
	char * m_query;
	const char * m_path;
	const char * m_uri;
	struct evhttp_uri * m_decoded;
	struct evkeyvalq m_params;
	struct evhttp_request * m_req;
};


#endif
