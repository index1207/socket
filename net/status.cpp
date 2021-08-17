#include "socket.hpp"

net::status::status(void) {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		MessageBoxA(nullptr, std::to_string(WSAGetLastError()).c_str(), "ERROR", MB_OK | MB_ICONERROR);
	}
}

net::status::~status() {
	WSACleanup();
}