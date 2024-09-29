
#ifndef _AUTH_H_
#define _AUTH_H_

int auth_client_deauth(unsigned id, const char *reason);
int auth_client_auth(unsigned id, const char *reason);
int auth_client_auth_nolock(const unsigned id, const char *reason);
int auth_client_trust(const char *mac);
int auth_client_untrust(const char *mac);
int auth_client_allow(const char *mac);
int auth_client_unallow(const char *mac);
int auth_client_block(const char *mac);
int auth_client_unblock(const char *mac);

/** @brief Periodically check if connections expired */
void *thread_client_timeout_check(void *arg);

/** @brief Deauth all authenticated clients */
void auth_client_deauth_all();

#endif
