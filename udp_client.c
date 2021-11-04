#include "net.h"
#include "stdio.h"

int main() {
    Socket socket = create_udp_socket6();
    udp_open6(&socket, 0, 0);
    udp_set_blocking(&socket, 0);

    IPAddress6 server;
    resolve_ip_address6(&server, "::1", "3323");

    char hello[] = "Hello Server";
    udp_send_ip6(&socket, server, hello, sizeof(hello));

    char buffer[64] = {0};
    socket_wait(&socket, SocketState_Readable);
    for (int i = 0; i < 100; ++i) {
        int size = udp_receive_from6(&socket, NULL, buffer, 63);
        if (size) printf("%.*s", size, buffer);
    }

    udp_close(&socket);
    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"