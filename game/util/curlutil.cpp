#include "curlutil.h"

CurlUtil::CurlUtil() {
	handle = curl_easy_init();
}

CurlUtil::~CurlUtil() {
	curl_easy_cleanup(handle);
}

std::string CurlUtil::getMap(float latitude, float longitude) {
	char slat[12];
	char slong[12];

	snprintf( slat, 12, "%f", latitude );
	snprintf( slong, 12, "%f", longitude );

	std::string location(slat);
	location.append(",");
	location.append(slong);
	return returnMap(location);
}
std::string CurlUtil::getMap(std::string centerName) {
	return returnMap(centerName);
}

//32-bit ints hard-coded as upper limit.
std::string CurlUtil::returnMap(std::string center) {
	char fn[10];
	snprintf( fn, 10, "%i", std::rand());

	std::string path("tmp/");
	path.append(fn);
	FILE * fh = fopen(path.c_str(), "w");

	std::string url("https://maps.googleapis.com/maps/api/staticmap?center=");
	url.append(center);
	url.append("&zoom=20&size=640x640&scale=1&maptype=satellite");
	printf("%s\n",url.c_str());

	curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, fh);

	curl_easy_perform(handle);

	fclose(fh);

	return path;
}
