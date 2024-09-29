#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "auth_curl.h"
#include "input_validation.h"

struct memory_struct{
	char *memory;
	size_t size;
};

static size_t write_memory(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct memory_struct *mem = (struct memory_struct *)userp;
	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (ptr == NULL) {
		return 1;
	}
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}

static enum smul_error_code get_error_code(const char *memory) {
	if (strstr(memory, "errorcode=1") != NULL) return COOKIE_NOT_WORKING;
	if (strstr(memory, "errorcode=2") != NULL) return WRONG_ID_FORMAT;
	if (strstr(memory, "errorcode=3") != NULL) return WRONG_CREDENTIAL;
	if (strstr(memory, "errorcode=4") != NULL) return SESSION_TERMINATED;
	return UNKNOWN_ERROR;
}

int main(int argc, char *argv[]) {
	if (argc < 5) {
		fprintf(stderr, "Usage: %s auth_client <client_mac> '<username>' '<password>'\n", argv[0]);
		return 1;	
	}

	const char *client_mac = argv[2];
	const char *username = argv[3];
	const char *password = argv[4];
	char postdata[256];
	struct memory_struct chunk;
	chunk.memory = malloc(1);
	chunk.size = 0;
	if ((strcmp(username,"on") == 0) && (strcmp(password,"on") == 0)) return 2;	

	if ((!validate_student_id(username)) && (!validate_password(password))){	
		//printf("0 0 0\n");
		return 1;
	}

	CURL *curl;
	CURLcode res;
	snprintf(postdata, sizeof(postdata), "username=%s&password=%s", username, password);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, LOGIN_SERVER_URL);
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		snprintf(postdata, sizeof(postdata), "username=%s&password=%s", username, password);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "");
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
//			printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			curl_easy_cleanup(curl);
			free(chunk.memory);

		//	result->curl = curl;
		//	result->errorcode = INTERNAL_ERROR;
			return 1;
		}

		if (strstr(chunk.memory, "errorcode") == NULL) {
			free(chunk.memory);
			//printf("Client : %s (mac address) succeed to login\n", client_mac);
			//printf("%d 0 0\n", EXPIRATION_TIME);

		//	result->curl = curl;
		//	result->errorcode = LOGIN_SUCCESS;
			return 0;
		}

		else {
//			error_code = get_error_code(chunk.memory);
			//printf("Client : %s (mac address) failed to login to smul server. Error: %s\n",client_mac, smul_error_messages[error_code]);
			curl_easy_cleanup(curl);
			free(chunk.memory);
		//	result->curl = NULL;
		//	result->errorcode = error_code;
			return 1;
		}


		curl_easy_cleanup(curl);
	}
}
