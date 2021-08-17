#include "socket.hpp"

net::socket::socket(void) : family(AF_INET), proto(IPPROTO_TCP) {
	memset(&addr, 0, sizeof(addr)); 
}

net::socket::socket(u_short _family, int _proto) : family(_family), proto(_proto) {
	memset(&addr, 0, sizeof(addr));

	if (proto == IPPROTO_TCP) {
		s = ::socket(family, SOCK_STREAM, proto);
	}
	else if (proto == IPPROTO_UDP) {
		s = ::socket(family, SOCK_DGRAM, proto);
	}

	addr.sin_family = family;
}

net::socket::~socket() {
	closesocket(s);
}

inline void net::socket::setFamily(u_short _family) {
	this->family = _family;
}

inline void net::socket::setAddr(const char* addr) {
	inet_pton(family, addr, &this->addr.sin_addr);
}

inline void net::socket::setPort(u_short _port) {
	addr.sin_port = htons(_port);
}

void net::socket::bind() {
    ::bind(s, (SOCKADDR*)&addr, sizeof(addr));
}

void net::socket::bind(const char* _addr) {
    this->setAddr(_addr);
    ::bind(s, (SOCKADDR*)&addr, sizeof(addr));
}

void net::socket::listen(int backlog = SOMAXCONN) {
    ::listen(s, backlog);
}

void net::socket::connect(const char* addr, u_short _port) {
    ::connect(s, (SOCKADDR*)&addr, sizeof(addr));
}

net::socket& net::socket::accept() {
    net::socket cs;
    int len = sizeof(cs.addr);
    cs.s = ::accept(s, (SOCKADDR*)&cs.addr, &len);

    return cs;
}

void net::socket::makeSocket(void) {
	if (proto == IPPROTO_TCP) {
		s = ::socket(family, SOCK_STREAM, proto);
	}
	else if (proto == IPPROTO_UDP) {
		s = ::socket(family, SOCK_DGRAM, proto);
	}
}

void net::socket::send(const char* str, int flag = 0) {
    ::send(s, str, strlen(str)+1, 0);
}

const char* net::socket::recv(int len = 8192, int flag = 0) {
    char* buf = new char[len];
    ZeroMemory(buf, 8192);

    ::recv(s, buf, sizeof(buf), 0);
    return buf;
}