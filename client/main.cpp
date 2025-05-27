#include <iostream>
#include <asio.hpp>
#include <thread>

using asio::ip::tcp;

void handle_client(tcp::socket socket) {
    try {
        for (;;) {
            char data[1024];
            size_t length = socket.read_some(asio::buffer(data));
            std::cout << "Received: " << std::string(data, length) << "\n";
            asio::write(socket, asio::buffer(data, length)); // echo
        }
    } catch (...) {
        std::cout << "Client disconnected.\n";
    }
}

int main() {
    asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1234));

    while (true) {
        tcp::socket socket(io);
        acceptor.accept(socket);
        std::thread(handle_client, std::move(socket)).detach();
    }
}
