#include "net.h"
#include "stdio.h"

void on_error(void* userblob, Socket* socket) {
    int* done = (int*)userblob;
    *done = 1;
    if (socket->error != SocketError_Closed)
        printf("Socket error: %d\n", socket->error);
}

void on_connected(void* userblob, Socket* socket) {
    puts("Connected to server");
}

void on_data(void* userblob, Socket* socket, void* data, int size) {
    printf("%.*s", size, (char*)data);    
}

int main() {

    Socol socol = create_socket_collection();
    
    int blob = 0;
    Socket* s = socol_tcp(&socol, "127.0.0.1", "3324");
    socol_userblob(&socol, s, &blob, sizeof(blob), NULL);
    socol_on_error(s, on_error);
    socol_on_connected(s, on_connected);
    socol_on_data(s, on_data);

    int* done = (int*)socol_get_userblob(s);

    while (!*done) socol_update(&socol);

    socol_destroy(&socol);
    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"