#ifndef CURLUTIL_H
#define CURLUTIL_H

#include <curl/curl.h>

#include <string>
#include <cstdlib>

char * ftoa(float, char *, int);

class CurlUtil {
	CURL * handle;

	std::string returnMap(std::string);
public:
	CurlUtil();
	~CurlUtil();

	std::string getMap(float, float);
	std::string getMap(std::string);
		
};

#endif
