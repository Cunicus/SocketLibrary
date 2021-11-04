#include "net.h"
#include "stdio.h"

int main() {

    Socket socket = create_tcp_socket();
    tcp_connect_domain(&socket, "localhost", "3321");
    
    int x = 10, y = 12;
    tcp_send(&socket, &x, sizeof(x));
    tcp_send(&socket, &y, sizeof(y));

    char message[64] = {0};
    int message_size = 0;
    tcp_receive_exact(&socket, &message_size, sizeof(message_size));
    
    if (message_size > 63) message_size = 63;
    tcp_receive_exact(&socket, message, message_size);

    if (socket.error != SocketError_None && socket.error != SocketError_Closed) {
        printf("Socket error: %d\n", socket.error);
    } else {
        printf("Server said: %s\n", message);
    }

    tcp_close(&socket);

    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"
