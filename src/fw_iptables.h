
#ifndef _FW_IPTABLES_H_
#define _FW_IPTABLES_H_

#include "auth.h"
#include "client_list.h"

/*@{*/
/**Iptable chain names used by ultari */
#define CHAIN_TO_INTERNET "ultariNET"
#define CHAIN_TO_ROUTER "ultariRTR"
#define CHAIN_TRUSTED_TO_ROUTER "ultariTRT"
#define CHAIN_OUTGOING  "ultariOUT"
#define CHAIN_INCOMING  "ultariINC"
#define CHAIN_AUTHENTICATED     "ultariAUT"
#define CHAIN_PREAUTHENTICATED   "ultariPRE"
#define CHAIN_BLOCKED    "ultariBLK"
#define CHAIN_ALLOWED    "ultariALW"
#define CHAIN_TRUSTED    "ultariTRU"
/*@}*/


/** Used to mark packets, and characterize client state.  Unmarked packets are considered 'preauthenticated' */
extern unsigned int  FW_MARK_PREAUTHENTICATED; /**< @brief 0: Actually not used as a packet mark */
extern unsigned int  FW_MARK_AUTHENTICATED;    /**< @brief The client is authenticated */
extern unsigned int  FW_MARK_BLOCKED;          /**< @brief The client is blocked */
extern unsigned int  FW_MARK_TRUSTED;          /**< @brief The client is trusted */
extern unsigned int  FW_MARK_MASK;             /**< @brief Iptables mask: bitwise or of the others */


/** @brief Initialize the firewall */
int iptables_fw_init(void);

/** @brief Destroy the firewall */
int iptables_fw_destroy(void);

/** @brief Helper function for iptables_fw_destroy */
int iptables_fw_destroy_mention( const char table[], const char chain[], const char mention[]);

/** @brief Define the access of a specific client */
int iptables_fw_authenticate(t_client *client);
int iptables_fw_deauthenticate(t_client *client);

/** @brief Return the total download usage in bytes */
unsigned long long int iptables_fw_total_download();

/** @brief Return the total upload usage in bytes */
unsigned long long int iptables_fw_total_upload();

/** @brief All counters in the client list */
int iptables_fw_counters_update(void);

/** @brief Return a string representing a connection state */
const char *fw_connection_state_as_string(int mark);

/** @brief Fork an iptables command */
int iptables_do_command(const char format[], ...);

int iptables_block_mac(const char mac[]);
int iptables_unblock_mac(const char mac[]);

int iptables_allow_mac(const char mac[]);
int iptables_unallow_mac(const char mac[]);

int iptables_trust_mac(const char mac[]);
int iptables_untrust_mac(const char mac[]);

#endif /* _IPTABLES_H_ */
