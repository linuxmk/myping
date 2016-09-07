#include "myping.h"
#include "linuxsyscall.h"
#include "socket.h"

extern pid_t pid;
extern int datalen;
extern int sockfd;
extern int nsent;
extern int verbose;


static void tv_sub (struct timeval *out, struct timeval *in);
uint16_t in_cksum(uint16_t * addr, int len);

void proc_v4 (char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{
	int hlenl, icmplen;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;
	double rtt;
	char host[128];

	ip = (struct ip*) ptr;
	hlenl = ip->ip_hl << 2;
	if( ip->ip_p != IPPROTO_ICMP)
		return;

	icmp = (struct icmp *) (ptr +hlenl);
	if( ( icmplen = len - hlenl) < 8)
		return;

	if( icmp->icmp_type == ICMP_ECHOREPLY)
	{
		if( icmp->icmp_id != pid)
			return;
		if( icmplen < 16)
			return;

		tvsend = (struct timeval *) icmp->icmp_data;
		tv_sub( tvrecv, tvsend);		
		rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

		fprintf(stderr, "%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n", icmplen, Sock_ntop_host(pr->sarecv, pr->salen, host), icmp->icmp_seq, ip->ip_ttl, rtt);
	}
	else
	if( verbose)
	{
		fprintf(stderr, "%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n", icmplen, Sock_ntop_host(pr->sarecv, pr->salen, host), icmp->icmp_seq, ip->ip_ttl, rtt);
	}
	
}

void send_v4(void)
{
	int len;
	struct icmp *icmp;

	icmp = (struct icmp*)sendbuf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = pid;
	icmp->icmp_seq = nsent++;
	memset(icmp->icmp_data , 0xa5, datalen);
	gettimeofday( (struct timeval *) icmp->icmp_data, NULL);

	len = 8 + datalen;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = in_cksum( ( u_short *)icmp, len);
	sendto(sockfd, sendbuf, len , 0, pr->sasend, pr->salen);	
}

uint16_t in_cksum(uint16_t * addr, int len)
{
	int nleft = len;
	uint32_t sum = 0;
	uint16_t *w = addr;
	uint16_t answer = 0;

	while(nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}

	if(nleft == 1)
	{
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}

	sum = ( sum >> 16) + ( sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}

static void tv_sub (struct timeval *out, struct timeval *in)
{
     if ((out->tv_usec -= in->tv_usec) < 0) {     /* out -= in */
         --out->tv_sec;
         out->tv_usec += 1000000;
     }
     out->tv_sec -= in->tv_sec;
}
