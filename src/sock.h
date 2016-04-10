#ifndef SOCK_H
#define SOCK_H

#ifdef _WIN32
#include <Winsock2.h>
#include <ws2tcpip.h>
#elif defined(__linux__)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

class SockAddr {
public:
	sockaddr addr_;

	SockAddr(sockaddr *addr);
	operator char*();
};

#endif // SOCK_H
