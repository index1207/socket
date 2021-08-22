#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__
#include <iostream>
#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>

namespace net {
	class status final{
	public:
		status(void);

		~status();
	private:
		WSADATA wsaData;
	};


	class socket {
	public:
		socket(void);

		socket(u_short _family, int _proto);

		~socket();
	public:
		inline void setFamily(u_short _family);

		inline void setAddr(const char* addr);

		inline void setAddr(ULONG addr);

		inline void setPort(u_short _port);

		void bind();

		void listen(int backlog = SOMAXCONN);

		void connect(void);

		void connect(u_short _port);

		void connect(const char* _addr);

		void connect(const char* _addr, u_short _port);

		socket& accept(void);

		void makeSocket(void);
	public:
		const char* recv(int flag = 0);

		void send(const char* str, int flag = 0);
	private:
		bool isSetAddr;
		bool isSetPort;
	private:
		u_short family;
		u_short proto;
		
		SOCKET s;
		SOCKADDR_IN addr;
	};
}

#endif