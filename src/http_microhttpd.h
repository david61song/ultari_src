#ifndef ULTARI_MICROHTTPD_H
#define ULTARI_MICROHTTPD_H

#include <stdio.h>

struct MHD_Connection;

/** @brief Get an IP's MAC address from the ARP cache.*/
int arp_get(char mac_addr[18], const char req_ip[]);


enum MHD_Result libmicrohttpd_cb (void *cls,
					struct MHD_Connection *connection,
					const char *url,
					const char *method,
					const char *version,
					const char *upload_data, size_t *upload_data_size, void **ptr);


#endif 
