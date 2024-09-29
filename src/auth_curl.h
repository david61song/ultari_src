#ifndef AUTH_SH_H
#define AUTH_SH_H

#include <curl/curl.h>

#define LOGIN_SERVER_URL "https://ecampus.smu.ac.kr/login/index.php"
#define USER_INFO_URL "https://ecampus.smu.ac.kr/user/user_edit.php"
#define EXPIRATION_TIME 7200

enum smul_error_code{
	UNKNOWN_ERROR,
	COOKIE_NOT_WORKING,
	WRONG_ID_FORMAT,
	WRONG_CREDENTIAL,
	SESSION_TERMINATED,
	LOGIN_SUCCESS,
	CANNOT_FIND_MAC,
	INTERNAL_ERROR
};

struct curl_res{
	CURL *curl;
	enum smul_error_code errorcode;
};

#endif
