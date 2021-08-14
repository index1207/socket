#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace ws2 {
	class status final{
	public:
		status(void) {
			WSAStartup(MAKEWORD(2, 2), &wsaData);
		}
		~status(void) {
			WSACleanup();
		}
	private:
		WSADATA wsaData;
	};
	class socket {
	public:
		socket(void) : family(AF_INET), proto(IPPROTO_TCP) {
			memset(&addr, 0, sizeof(addr)); 
		}

		socket(u_short _family, int _proto) : family(_family), proto(_proto) {
			memset(&addr, 0, sizeof(addr));

			if (proto == IPPROTO_TCP) {
				s = ::socket(family, SOCK_STREAM, proto);
			}
			else if (proto == IPPROTO_UDP) {
				s = ::socket(family, SOCK_DGRAM, proto);
			}

			addr.sin_family = family;
		}
		~socket() {
			closesocket(s);
		}
	public:
		inline void setFamily(u_short _family) {
			this->family = _family;
		}
		void setAddr(const char* addr) {
			inet_pton(family, addr, &this->addr.sin_addr);
		}
		void setPort(u_short _port) {
			addr.sin_port = htons(_port);
		}
		void makeSocket(void) {
			if (proto == IPPROTO_TCP) {
				s = ::socket(family, SOCK_STREAM, proto);
			}
			else if (proto == IPPROTO_UDP) {
				s = ::socket(family, SOCK_DGRAM, proto);
			}
		}
	public:
		inline operator SOCKET() const {
			return s;
		}
		void operator=(const SOCKET& sock) { 
			this->s = sock; 
		}
		SOCKADDR_IN addr;
	private:
		u_short family;
		u_short proto;
		
		SOCKET s;
	};
}

#endif