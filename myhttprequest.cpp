#include "myhttprequest.h"

CMyHttpRequest::CMyHttpRequest(struct evhttp_request *req)
{
	m_req = req;
}

int CMyHttpRequest::parse()
{
	m_uri = evhttp_request_get_uri(m_req); //获取请求uri
	if(NULL == m_uri)
	{
		printf("====line:%d,evhttp_request_get_rui return null\n", __LINE__);
		return -1;
	}	
	printf("====line:%d GOT a request for<%s>\n", __LINE__, m_uri);

	//解码uri
	m_decoded = evhttp_uri_parse(m_uri);
	if(NULL == m_decoded)
	{
		printf("====line:%d It's not a good URI. Sending BADREQUEST\N", __LINE__);		evhttp_send_error(m_req, HTTP_BADREQUEST, 0);
		return -1;
	}	

	m_path = evhttp_uri_get_path(m_decoded);
	if(NULL == m_path)
	{
		m_path = "/";
	}
	else
	{
		printf("====line:%d path is :%s\r\n", __LINE__, m_path);
	}
	
	//获取uri中的参数部分
	m_query = (char *)evhttp_uri_get_query(m_decoded);
	if(NULL == m_query)
	{
		printf("====line:%d, evhttp_uri_get_query return null\r\n", __LINE__);
		return -1;
	}

	//查询指定参数的值
	evhttp_parse_query_str(m_query, &m_params);
}


const char * CMyHttpRequest::GetPath()
{
	return m_path;
}

const char * CMyHttpRequest::GetQuery(const char * data_name)
{
	return (const char *)evhttp_find_header(&m_params, data_name);

}
