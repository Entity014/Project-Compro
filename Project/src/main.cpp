#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "board.cpp"

const int width = 768, height = 768;
const int fields = 8;
const int tileSize = width / fields;

sf::RectangleShape boardChess[fields * fields];

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Chess Mae");
    board(fields, tileSize, boardChess);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < fields * fields; i++)
        {
            window.draw(boardChess[i]);
        }
        window.display();
    }

    return 0;
}
