#include "net.h"
#include "stdio.h"

char some_message_to_send[] =
    "https://de.wikipedia.org/wiki/Lorem_ipsum\n"
    "Lorem ipsum dolor sit amet, \n"
    "consectetur adipisici elit, \n"
    "sed eiusmod tempor incidunt \n"
    "ut labore et dolore magna aliqua. \n"
    "Ut enim ad minim veniam, \n"
    "quis nostrud exercitation ullamco laboris nisi \n"
    "ut aliquid ex ea commodi consequat. \n"
    "Quis aute iure reprehenderit in voluptate velit \n"
    "esse cillum dolore eu fugiat nulla pariatur. \n"
    "Excepteur sint obcaecat cupiditat non proident, \n"
    "sunt in culpa qui officia deserunt mollit anim id est \n"
    "laborum.\n";

typedef struct Blob {
    char* text;
    int size;
    int cursor;
} Blob;

void on_error(void* userblob, Socket* socket) {
    if (socket->error != SocketError_Closed)
        printf("Socket error: %d\n", socket->error);
}

void on_writeable(void* userblob, Socket* socket) {
    Blob* blob = (Blob*)userblob;
    blob->cursor += tcp_send(socket, &blob->text[blob->cursor], blob->size - blob->cursor);
    if (blob->cursor >= blob->size)
        socol_close(socket);
}

void on_connection(Socol* socol, void* userblob, Socket new_socket, IPAddress address) {
    puts("New User connected");
    
    Blob blob;
    blob.text = some_message_to_send;
    blob.size = sizeof(some_message_to_send);
    blob.cursor = 0;

    Socket* s = socol_add_already_connected_socket(socol, new_socket);
    socol_userblob(socol, s, &blob, sizeof(blob), NULL);
    socol_on_error(s, on_error);
    socol_on_writeable(s, on_writeable);
}

int main() {

    Socol socol = create_socket_collection();
    
    Socket* s = socol_listen(&socol, 3324);
    socol_on_error(s, on_error);
    socol_on_connection(s, on_connection);
    
    for (int i = 0; i < 10000000; ++i) {
        socol_update(&socol); // busy waiting
    }

    socol_destroy(&socol);

    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"
