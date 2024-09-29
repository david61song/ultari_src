
#ifndef _TC_H_
#define _TC_H_

#define MTU 1500
#define HZ 100


int
tc_init_tc(void);

int
tc_destroy_tc(void);


int
tc_attach_client(const char down_dev[], int download_limit, const char up_dev[], int upload_limit, int idx, const char ip[]);

int
tc_detach_client(const char down_dev[], int download_limit, const char up_dev[], int upload_limit, int idx);


#endif /* _TC_H_ */
