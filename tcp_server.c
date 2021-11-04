#include "net.h"
#include "stdio.h"

int main() {

    Socket socket = create_tcp_socket();
    tcp_listen(&socket, 3321);

    IPAddress address;
    Socket client = tcp_accept_socket(&socket, &address);

    int x, y;
    tcp_receive_exact(&client, &x, sizeof(x));
    tcp_receive_exact(&client, &y, sizeof(y));

    char message[] = "Hello Client";
    int message_size = sizeof(message) - 1;
    tcp_send(&client, &message_size, sizeof(message_size));
    tcp_send(&client, message, sizeof(message));

    
    if (socket.error != SocketError_None && socket.error != SocketError_Closed) {
        printf("Socket error: %d\n", client.error);
    } else {
        printf("Client send: x = %d, y = %d\n", x, y);
    }

    tcp_close(&socket);

    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"
