
#ifndef _CLIENT_LIST_H_
#define _CLIENT_LIST_H_

/** Counters struct for a client's bandwidth usage (in bytes)
 */
typedef struct _t_counters {
	unsigned long long incoming;	/**< @brief Incoming data total */
	unsigned long long outgoing;	/**< @brief Outgoing data total */
	time_t last_updated;	/**< @brief Last update of the counters */
} t_counters;

/** Client node for the connected client linked list.
 */
typedef struct _t_client {
	struct _t_client *next;	/**< @brief Pointer to the next client */
	char *ip;				/**< @brief Client IP address */
	char *mac;				/**< @brief Client MAC address */
	char *token;		/**< @brief Client token */
	unsigned int fw_connection_state;	/**< @brief Connection state in the firewall */
	time_t session_start;	/**< @brief Time the client was authenticated */
	time_t session_end;		/**< @brief Time until client will be deauthenticated */
	t_counters counters;	/**< @brief Counters for input/output of the client. */
	int download_limit;		/**< @brief Download limit, kb/s */
	int upload_limit;		/**< @brief Upload limit, kb/s */
	unsigned id;
} t_client;

/** @brief Get the first element of the list of connected clients
 */
t_client *client_get_first_client(void);

/** @brief Initializes the client list */
void client_list_init(void);

/** @brief Returns number of clients currently on client list */
int get_client_list_length();

/** @brief Adds a new client to the client list */
t_client *client_list_add_client(const char mac[], const char ip[]);

/** @brief Finds a client by its MAC, IP or token */
t_client *client_list_find_by_any(const char mac[], const char ip[], const char token[]);

/** @brief Finds a client by its MAC and IP */
t_client * client_list_find(const char mac[], const char ip[]);

/** @brief Finds a client by its client id */
t_client * client_list_find_by_id(const unsigned id);

/** @brief Finds a client only by its IP */
t_client *client_list_find_by_ip(const char ip[]); /* needed by fw_iptables.c, auth.c * and ndsctl_thread.c */

/** @brief Finds a client only by its MAC */
t_client *client_list_find_by_mac(const char mac[]); /* needed by ultarictl_thread.c */

/** @brief Finds a client by its token */
t_client *client_list_find_by_token(const char token[]);

/** @brief Reset volatile client fields */
void client_reset(t_client *client);

/** @brief Deletes a client from the client list */
void client_list_delete(t_client *client);

#define LOCK_CLIENT_LIST() do { \
	debug(LOG_DEBUG, "Locking client list"); \
	pthread_mutex_lock(&client_list_mutex); \
	debug(LOG_DEBUG, "Client list locked"); \
} while (0)

#define UNLOCK_CLIENT_LIST() do { \
	debug(LOG_DEBUG, "Unlocking client list"); \
	pthread_mutex_unlock(&client_list_mutex); \
	debug(LOG_DEBUG, "Client list unlocked"); \
} while (0)

extern pthread_mutex_t client_list_mutex;

#endif /* _CLIENT_LIST_H_ */
