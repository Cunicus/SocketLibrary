#include "net.h"
#include "stdio.h"

int main() {
    Socket socket = create_udp_socket6();
    udp_open6(&socket, 3323, 0);
    udp_set_blocking(&socket, 0);

    char buffer[256] = {0};

    socket_wait(&socket, SocketState_Readable);
    
    IPAddress6 client;
    int size = udp_receive_from6(&socket, &client, buffer, 255);
    puts("Client said:");
    puts(buffer);

    for (int i = 0; i < 30; ++i) {
        int size = snprintf(buffer, 255, "Number: %d\n", i);
        udp_send_ip6(&socket, client, buffer, size);
    }

    udp_close(&socket);
}

#define NET_IMPLEMENTATION
#include "net.h"
