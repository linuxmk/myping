#include "myping.h"

extern int sockfd;

void readloop(void)
{
	int size;
	char recvbuf[BUFSIZE];
	char controlbuf[BUFSIZE];
	struct iovec iov;
	struct msghdr msg;
	ssize_t n;
	struct timeval tval;

	sockfd = socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto);
	if(sockfd < 0)
		err_quit("Can not create raw socket");
	setuid(getuid());

	if(pr->finit)
		(*pr->finit)();

	size = 60 * 1024;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

	sig_alrm(SIGALRM);

	iov.iov_base = recvbuf;	
	iov.iov_len = sizeof(recvbuf);
	msg.msg_name = pr->sarecv;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = controlbuf;

	for( ; ; )
	{
		msg.msg_namelen = pr->salen;
		msg.msg_controllen = sizeof(controlbuf);
		n = recvmsg(sockfd, &msg, 0);
		if(n < 0)
		{
			if (errno == EINTR)
				continue;
			else
				err_sys("recvmsg error");
		}
		gettimeofday(&tval, NULL);
		fprintf(stderr, "%s\n", msg.msg_iov.iov_base);
		(*pr->fproc)(recvbuf, n, &msg, &tval);
	}
}
