#include "myping.h"

struct proto proto_v4 = { proc_v4, send_v4, NULL, NULL, NULL, 0, IPPROTO_ICMP};
#ifdef IPV6
struct proto proto_v6 = { proc_v6, send_v6, NULL, NULL, NULL, 0, IPPROTO_ICMP6};
#endif 

int datalen = 56;
int verbose;
char *host;
pid_t pid;
int sockfd;
int nsent;


int main(int argc, char *argv[])
{
	int c;
	Sigfunc *sigfunc;
	struct addrinfo *ai;
	char h[128];

	opterr = 0;
	while( ( c = getopt( argc, argv, "v") ) != -1)
	{
		switch(c)
		{
			case 'v':
				verbose++;
				break;
			case '?':
				err_quit("Unrecognized option: %c", c);
				break;
		}
	}
	
	if(optind != argc -1)
		err_quit("usage: myping [ -v ] <hostname>");

	host = argv[optind];
		
	pid = getpid() & 0xffff;
	sigfunc = Signal(SIGALRM, sig_alrm);

	ai = Host_serv(host, NULL , 0 , 0);
	Sock_ntop_host(ai->ai_addr, ai->ai_addrlen, h);
	
	fprintf(stderr, "Ping %s (%s): %d data bytes\n", ai->ai_canonname ? ai->ai_canonname : h, h, datalen);

	if(ai->ai_family == AF_INET)
	{
		pr = &proto_v4;
	}
	else
	if(ai->ai_family == AF_INET6)
	{

	}
	else
	{
		err_quit("unknown address family %d", ai->ai_family);
	}	


	pr->sasend = ai->ai_addr;
	pr->sarecv = calloc(1, ai->ai_addrlen);
	pr->salen = ai->ai_addrlen;

	readloop();	

return 0;
}

void sig_alrm(int arg)
{
	(*pr->fsend)();

	alarm(1);
return;
}
