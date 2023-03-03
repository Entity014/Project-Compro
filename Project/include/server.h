#include "../include/libary.h"

int port = 1000;

void hostServer()
{
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connectionType;
    char buffer[1024];
    std::size_t received;
    std::string text = "Connected to: ";

    sf::TcpListener listener;
    listener.listen(2000);
    listener.accept(socket);
    text += "Server";

    socket.send(text.c_str(), text.length() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << buffer << std::endl;
}

void joinServer()
{
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connectionType;
    char buffer[1024];
    std::size_t received;
    std::string text = "Connected to: ";

    socket.connect(ip, 2000);
    text += "Client";

    socket.send(text.c_str(), text.length() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << buffer << std::endl;
}