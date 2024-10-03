#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 8080;
const std::string BASE_DIR = "./www";

// Function to serve the requested file
void serve_file(int client_socket, const std::string &file_path) {
    std::ifstream file(BASE_DIR + file_path);
    
    if (file) {
        // File found, sending 200 OK response
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        response += content;
        send(client_socket, response.c_str(), response.size(), 0);
    } else {
        // File not found, sending 404 response
        std::string response = "HTTP/1.1 404 NOT FOUND\nContent-Type: text/html\n\n"
                               "<html><body><h1>404 Not Found</h1></body></html>";
        send(client_socket, response.c_str(), response.size(), 0);
    }

    close(client_socket); // Close client connection
}

// Function to handle client connections
void handle_client(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024); // Read HTTP request

    std::string request(buffer);
    std::string file_requested = "/index.html"; // Default file

    // Basic request parsing to get the file path
    size_t pos = request.find("GET ");
    if (pos != std::string::npos) {
        size_t end_pos = request.find(" ", pos + 4);
        file_requested = request.substr(pos + 4, end_pos - (pos + 4));
        if (file_requested == "/") file_requested = "/index.html"; // Serve index.html if root is requested
    }

    serve_file(client_socket, file_requested);
}

int main() {
    // Setup socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{AF_INET, htons(PORT), INADDR_ANY};
    bind(server_socket, (sockaddr*)&address, sizeof(address));
    listen(server_socket, 10); // Listen for incoming connections

    std::cout << "Server running on port " << PORT << "...\n";

    // Infinite loop to accept and handle clients
    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        std::thread(handle_client, client_socket).detach(); // Handle client in a new thread
    }

    close(server_socket); // Close server socket
    return 0;
}
