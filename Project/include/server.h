#include "../include/libary.h"

sf::TcpSocket socket;

void hostServer()
{
    std::cout << "your server ip : " << sf::IpAddress::getLocalAddress() << std::endl;
    char connectionType;
    std::string text = "Connected to: ";

    sf::TcpListener listener;
    listener.listen(2000);
    listener.accept(socket);
    text += "Server";

    socket.send(text.c_str(), text.length() + 1);
}

void joinServer(int ipAddr1, int ipAddr2, int ipAddr3, int ipAddr4)
{
    sf::IpAddress ip(ipAddr1, ipAddr2, ipAddr3, ipAddr4);
    char connectionType;
    std::string text = "Connected to: ";

    socket.connect(ip, 2000);
    text += "Client";

    socket.send(text.c_str(), text.length() + 1);
}

void sendWhoTurn(Board masterBoard)
{
    sf::Packet packet;
    // std::string text = "test";
    packet << "Who" << masterBoard.whoTurn << 0;
    socket.send(packet);
}

void sendMove(int select, int position)
{
    sf::Packet packet;
    packet << "Move" << select << position;
    socket.send(packet);
}

void sendDead(int who)
{
    sf::Packet packet;
    packet << "Dead" << who << 0;
    socket.send(packet);
}

void sendReset()
{
    sf::Packet packet;
    packet << "Reset" << 0 << 0;
    socket.send(packet);
}

void sendTurnCount(int count)
{   
    sf::Packet packet;
    packet << "turnCount" << count << 0;
    socket.send(packet);
}