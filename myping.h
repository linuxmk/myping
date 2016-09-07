#ifndef __MYPING_
#define __MYPING_

#include "stdclib.h"
#include "linuxsyscall.h"
#include "error.h"
#include "signal.h"
#include "socket.h"

#define BUFSIZE		1500

char sendbuf[BUFSIZE];

void proc_v4(char *, ssize_t , struct msghdr *, struct timeval *);
void proc_v6(char *, ssize_t , struct msghdr *, struct timeval *);
void send_v4(void);
void send_v6(void);
void readloop(void);
void sig_alrm(int);


struct proto {
	void (*fproc) (char *, ssize_t , struct msghdr *, struct timeval *);
	void (*fsend) ( void );
	void (*finit) ( void );
	struct sockaddr *sasend;
	struct sockaddr *sarecv;
	socklen_t salen;
	int	icmpproto;
} *pr;


#endif
