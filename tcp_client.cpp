#define NET_USE_CPP
#include "net.h"
#include "stdio.h"

int main() {
    TCPSocket socket;
    socket.connect("localhost", "3321");

    auto stream = socket.stream();
    stream << 10 << ' ' << 12 << '\n';

    std::string message;
    stream >> message;

    if (socket.error() != SocketError_None && socket.error() != SocketError_Closed) {
        std::cout << "Socket error: " << socket.error() << '\n';
    } else {
        std::cout << "Server said: " << message << '\n';
    }
}

#define NET_IMPLEMENTATION
#include "net.h"