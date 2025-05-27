#include <iostream>
#include <thread>
#include "asio.hpp"

using asio::ip::tcp;

void handle_client(tcp::socket socket) {
    try {
        while (true) {
            char data[1024];
            size_t len = socket.read_some(asio::buffer(data));
            std::cout << "[Client] " << std::string(data, len) << std::endl;

            // Kirim balik pesan (echo)
            asio::write(socket, asio::buffer(data, len));
        }
    } catch (...) {
        std::cout << "Client disconnected\n";
    }
}

int main() {
    try {
        asio::io_context io;
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1234));
        std::cout << "Server running on port 1234...\n";

        while (true) {
            tcp::socket socket(io);
            acceptor.accept(socket);
            std::cout << "Client connected.\n";
            std::thread(handle_client, std::move(socket)).detach();
        }

    } catch (std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}
