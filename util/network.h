#ifndef ___NETWORK__H__
#define ___NETWORK__H__


#ifdef WIN32
	#include <WinSock2.h>
	#include <ws2tcpip.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

typedef struct sockaddr SA;

void winsock_init(void);

__int32 tcp_listen(const char* host, __int32 port);
__int32 tcp_connect(const char* host, const char* serv);
__int32 connect_nob(__int32 sockfd, const SA* saptr, socklen_t salen, __int32 nsec);
__int32 set_sock_block(__int32 fd, bool block);
__int32 udp_local_server(char* sun_path);
__int32 udp_connect(const char* host);
__int32 get_local_host_mac(char* if_name, char* mac);
__int32 getneterror(void);


#ifdef __cplusplus
}
#endif 

#endif