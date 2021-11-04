#define NET_USE_CPP
#include "net.h"
#include "stdio.h"

int main() {
    UDPSocket6 socket;
    socket.open();
    socket.set_blocking(false);

    IPAddress6 server = resolve_ip_address6("::1", "3323").value();

    char hello[] = "Hello Server";
    socket.send(server, hello, sizeof(hello));

    char buffer[64] = {0};
    socket.wait(SocketState_Readable);
    for (int i = 0; i < 100; ++i) {
        int size = socket.receive_from(buffer, 63);
        if (size) printf("%.*s", size, buffer);
    }

    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"