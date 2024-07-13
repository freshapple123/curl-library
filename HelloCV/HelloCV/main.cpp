#include <iostream>
#include <curl/curl.h>

#pragma comment(lib, "libcurld.lib")
#define CURL_STATICLIB
#pragma comment (lib, "wldap32.lib") // 외부 참조 에러 시에 적어준다.
#pragma comment (lib, "ws2_32.lib") // 외부 참조 에러 시에 적어준다.

int main()
{

	return 0;
}