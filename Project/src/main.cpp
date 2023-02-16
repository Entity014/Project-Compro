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
    sf::RenderWindow window(sf::VideoMode(453, 453), "Chess Mae");
    // sf::RectangleShape rectangle(sf::Vector2f(tileSize, tileSize));
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
        window.draw(boardChess[1]);
        window.display();
    }

    return 0;
}