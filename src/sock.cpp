#include "sock.h"
#include <memory>

SockAddr::SockAddr(sockaddr *addr) {
	if (nullptr != addr) 
		addr_ = *addr;
	else
		memset(&addr_, sizeof(addr_), 0);
}

SockAddr::operator char*() {
    static char buf[/*INET_ADDRSTRLEN*/INET6_ADDRSTRLEN] = {0};	
	
    switch (addr_.sa_family) {
    case AF_INET:
        inet_ntop(addr_.sa_family,
                           &(((struct sockaddr_in*)&addr_)->sin_addr),
						   buf, INET_ADDRSTRLEN);
        break;
    case AF_INET6:
        inet_ntop(addr_.sa_family,
                           &(((struct sockaddr_in6*)&addr_)->sin6_addr),
						   buf, INET6_ADDRSTRLEN);
        break;
    default:
		buf[0] = 0;
        break;
    }
    return buf;
}

