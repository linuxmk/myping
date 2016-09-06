#include "myping.h"


int datalen = 56;

void sig_alrm(int arg);


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

return 0;
}

void sig_alrm(int arg)
{
return;
}
