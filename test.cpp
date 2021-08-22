#include <iostream>
#include "net/socket.hpp"

int main() {
    net::status status;

    net::socket s(AF_INET, IPPROTO_TCP);
    s.setAddr(INADDR_ANY);
    s.setPort(10000);

    s.bind();
    s.listen();

    net::socket cs;
    cs = s.accept();

    const char* str = cs.recv();
    std::cout << str;

    return 0;
}