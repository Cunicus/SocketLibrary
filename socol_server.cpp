#define NET_USE_CPP
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

int main() {

    SocketCollection socol;
    socol.listen(3324)
        .on_error([](Socket* socket){
            if (socket->error != SocketError_Closed)
                std::cout << "Listen Socket error: " << socket->error << '\n';
        })
        .on_connection([&](Socket socket, IPAddress address){
            std::cout << "New User connected\n";
            int cursor = 0;
            char* text = some_message_to_send;            
            int message_size = sizeof(some_message_to_send);

            socol.add_already_connected_socket(socket)
                .on_error([](Socket* socket){
                    if (socket->error != SocketError_Closed)
                        std::cout << "Socket error: " << socket->error << '\n';
                })
                .on_writeable([=](TCPSocket socket) mutable {
                    cursor += socket.send(&text[cursor], message_size - cursor);
                    if (cursor >= message_size) socket.close();
                });
        });

    for (int i = 0; i < 10000000; ++i) {
        socol.update(); // busy waiting
    }

    return 0;
}


#define NET_IMPLEMENTATION
#include "net.h"
