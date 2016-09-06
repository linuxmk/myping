#include "myping.h"


int main(int argc, char *argv[])
{
	int c;

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

return 0;
}
