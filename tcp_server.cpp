#define NET_USE_CPP
#include "net.h"
#include "stdio.h"

int main() {
    TCPSocket socket;
    socket.listen(3321);

    TCPSocket client = socket.accept();
    auto stream = client.stream();

    int x, y;
    stream >> x >> y;
    stream << "Hello_Client";

    if (socket.error() != SocketError_None && socket.error() != SocketError_Closed) {
        std::cout << "Socket error: " << client.error() << '\n'; 
    } else {
        std::cout << "Client send: x = " << x << ", y = " << y << '\n'; 
    }

}

#define NET_IMPLEMENTATION
#include "net.h"