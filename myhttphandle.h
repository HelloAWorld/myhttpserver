#ifndef __MY_HTTPHANDLE_H__
#define __MY_HTTPHANDLE_H__

#include "myhttprequest.h"
#include "myhttpresponse.h"

class CMyHttpHandle
{
public:
	virtual ~CMyHttpHandle(){}
	virtual int handle(int method, CMyHttpRequest & request, CMyHttpResponse & response) = 0;

private:

};

#endif
