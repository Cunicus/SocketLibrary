#define NET_USE_CPP
#include "net.h"
#include "stdio.h"

int main() {
    UDPSocket6 socket;
    socket.open(3323);
    socket.set_blocking(false);

    char buffer[256] = {};
    socket.wait(SocketState_Readable);

    IPAddress6 client;
    int size = socket.receive_from(client, buffer, 255);
    std::cout << "Client said: " << buffer <<'\n';

    for (int i = 0; i < 30; ++i) {
        int size = snprintf(buffer, 255, "Number: %d\n", i);
        socket.send(client, buffer, size);
    }

    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"