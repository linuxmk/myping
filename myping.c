#include "myping.h"


void sig_alrm(int arg);


int main(int argc, char *argv[])
{
	int c;
	Sigfunc *sigfunc;

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


return 0;
}

void sig_alrm(int arg)
{
return;
}
