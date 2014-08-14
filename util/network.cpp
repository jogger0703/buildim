#include "network.h"

#include <io.h>
#ifdef WIN32
	#include <WinSock2.h>
	#include <ws2tcpip.h>

	#pragma comment(lib, "ws2_32.lib")
#endif

void winsock_init(void)
{
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif
}

__int32 getneterror(void)
{
#ifdef WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}

__int32 connect_nob(__int32 sockfd, const SA* saptr, socklen_t salen, __int32 nsec)
{
	__int32 n, error;                                                                                    
    socklen_t len;
    fd_set rset, wset;
    struct timeval tval;                                                                                    
    
	if (set_sock_block(sockfd, false) != 0)
		return -1;
    
    error = 0;
    if (( n = connect(sockfd, saptr, salen)) < 0) {
#ifdef WIN32
		if (getneterror() != 10035)
#else
		if (errno != EINPROGRESS)
#endif
            return -1;
	}
    if (n == 0)
        goto DONE; //connect completed immediately
    
    FD_ZERO(&rset);
    FD_SET (sockfd, &rset);
    wset = rset;
    tval.tv_sec = nsec;
    tval.tv_usec = 0;
    if ((n = select(sockfd+1, &rset, &wset, NULL,nsec?&tval:NULL)) == 0)                   
    {
        closesocket(sockfd);
#ifndef WIN32
        errno = ETIMEDOUT;
#endif
        return -1;
    }
    if (FD_ISSET (sockfd, &rset) || FD_ISSET(sockfd, &wset))
    {
        len = sizeof(error);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (char*)&error, &len) < 0)
            return -1;
    }
    else
        return -1;

DONE:
    set_sock_block(sockfd, true);
    if (error)
    {
        closesocket(sockfd);
        errno = error;
        return -1;
    }

	return 0;
}

__int32 tcp_listen(const char* host, __int32 port)
{
	int listenfd;
	const int on = 1;
	int ret;
	struct sockaddr_in servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
		return listenfd;

	ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	if (ret != 0)
		return ret;

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (ret != 0)
		return ret;

	if (listen(listenfd, 5) < 0)
		return -1;
	return (listenfd);
}

__int32 tcp_connect(const char* host, const char* serv)
{
	__int32 sockfd, n;
	struct addrinfo hints, *res, *ressave;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
		return n;

	ressave = res;
	do {
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
			continue;
		if (connect_nob(sockfd, res->ai_addr, res->ai_addrlen, 5) == 0)
			break;
		closesocket(sockfd);
	} while ((res = res->ai_next) != NULL);

	freeaddrinfo(ressave);

	if (res == NULL)
		return -1;

	return sockfd;
}

__int32 set_sock_block(__int32 fd, bool block)
{
#ifndef WIN32
	__int32 flags;
	flags = fcntl(fd, F_GETFL);
	if (flags < 0)
		return flags;

	if (block)
		flags |= O_NONBLOCK;
	else
		flags &= ~O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0)
		return -1;
#else
	u_long flag = block ? 0 : 1;
	if (ioctlsocket(fd, FIONBIO, &flag) != 0)
		return -1;
#endif
	return 0;
}
__int32 udp_local_server(char* sun_path)
{
	return 0;
}
__int32 udp_connect(const char* host)
{
	return 0;
}
__int32 get_local_host_mac(char* if_name, char* mac)
{
	return 0;
}