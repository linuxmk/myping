#ifndef __SOCKET_H_
#define __SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>

struct addrinfo * Host_serv(const char *host, const char *serv, int family, int socktype);
char * sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *h);
char * Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *h);


#endif
