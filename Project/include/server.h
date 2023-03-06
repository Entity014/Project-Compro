#include "../include/libary.h"

void hostServer()
{
    std::cout << "your server ip : " << sf::IpAddress::getLocalAddress() << std::endl;
    std::cout << "Server Running" << std::endl;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::vector<sf::TcpSocket*> clients;
    std::string id;
    
    listener.listen(2000);
    selector.add(listener);
    while (true)
    {
        // std::cout << clients.size() << std::endl;
        if (selector.wait())
        {
            if (selector.isReady(listener) && clients.size() < 4)
            {
                sf::TcpSocket *socket = new sf::TcpSocket;
                listener.accept(*socket);
                sf::Packet packet;
                if (socket->receive(packet) == sf::Socket::Done) packet >> id;
                
                std::cout << "[ " << clients.size() + 1 << " / 4 ] ";
                std::cout << id << " has connected to the chat room" << std::endl;
                clients.push_back(socket);
                selector.add(*socket);
            }
            else
            {
                for (int i = 0; i < clients.size(); i++)
                {
                    if(selector.isReady(*clients[i]))
                    {
                        sf::Packet packet, sendPacket;
                        if (clients[i]->receive(packet) == sf::Socket::Done)
                        {
                            std::string text;
                            packet >> text;
                            sendPacket << text;
                            for(int j = 0; j < clients.size(); j++)
                            {
                                if (i != j)
                                {
                                    clients[j]->send(sendPacket);
                                }
                            }
                        }
                        else
                        {
                            selector.remove(*clients[i]);
                            delete clients[i];
                            clients.erase(clients.begin() + i);
                            std::cout << "[ " << clients.size() << " / 4 ] ";
                            std::cout << id << " has disconnected to the chat room" << std::endl;
                        }
                    }
                }
            }
            
        }
    }

    for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
    {
        delete *it;
    }
}

void joinServer(sf::TcpSocket &socket, std::string &id, int ipAddr1, int ipAddr2, int ipAddr3, int ipAddr4)
{
    sf::IpAddress ip(ipAddr1, ipAddr2, ipAddr3, ipAddr4);
    socket.connect(ip, 2000);

    sf::Packet packet;
    packet << id;
    socket.send(packet);
    socket.setBlocking(false);
}

void sendMoveSidePayload(sf::TcpSocket &socket, std::string id, std::string &payload)
{
    sf::Packet packet;
    packet << "M," + id + ": "  + "S " + payload;
    socket.send(packet);
    payload = "";
}

// void selectHost(sf::TcpSocket &socket, std::string id, std::string &payload)
// {
//     sf::Packet packet;
//     packet << "M," + id + ": "  + "H" + payload;
//     socket.send(packet);
//     payload = "";
// }