
#ifndef _ULTARICTL_THREAD_H_
#define _ULTARICTL_THREAD_H_


#define DEFAULT_ultarictl_SOCK "/tmp/ultarictl.sock"

/** @brief Listen for ultari control messages on a unix domain socket */
void *thread_ultarictl(void *arg);


#endif
