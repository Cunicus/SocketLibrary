#define NET_USE_CPP
#include "net.h"
#include "stdio.h"

int main() {
    bool done = false;
    
    SocketCollection socol;
    socol.tcp("127.0.0.1", "3324")
        .on_error([&](Socket* socket){
            done = true;
            if (socket->error != SocketError_Closed)
                std::cout << "Socket error: " << socket->error << '\n';
        })
        .on_connected([](Socket* socket) {
            std::cout << "Connected to server\n";
        })
        .on_data([](Socket* socket, void* data, int size) {
            printf("%.*s", size, (char*)data);
        });

    while (!done) socol.update();

    return 0;
}

#define NET_IMPLEMENTATION
#include "net.h"