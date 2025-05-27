#include <iostream>
#include <thread>
#include "asio.hpp"

using asio::ip::tcp;

void read_thread(tcp::socket& socket) {
    try {
        while (true) {
            char data[1024];
            size_t len = socket.read_some(asio::buffer(data));
            std::cout << "[Server] " << std::string(data, len) << std::endl;
        }
    } catch (...) {
        std::cout << "Disconnected from server.\n";
    }
}

int main() {
    try {
        asio::io_context io;
        tcp::resolver resolver(io);
        auto endpoints = resolver.resolve("127.0.0.1", "1234");
        tcp::socket socket(io);
        asio::connect(socket, endpoints);

        std::thread t(read_thread, std::ref(socket));

        std::string msg;
        while (std::getline(std::cin, msg)) {
            socket.write_some(asio::buffer(msg));
        }

        t.join();
    } catch (std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }

    return 0;
}
