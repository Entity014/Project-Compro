#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "board.h"

const int width = 800, height = 600;
const int fields = 8;
const int tileSize = height / fields;
const int moveRight = width - height;

sf::RectangleShape boardChess[fields * fields];


int main()
{
    sf::Texture t1;
    t1.loadFromFile("asset/texture/test.png");
    t1.setSmooth(true);

    sf::Sprite s(t1);
    s.setScale(sf::Vector2f(0.25f, 0.25f));
    s.setPosition(sf::Vector2f(-175,350));

    /* Reander window */
    sf::RenderWindow window(sf::VideoMode(width, height), "Chess Mae");
    board(fields, tileSize, moveRight, boardChess);
    sf::RectangleShape Status(sf::Vector2f(moveRight, height));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* Draw */
        window.clear();
        window.draw(Status);
        window.draw(s);
        for (int i = 0; i < fields * fields; i++)
        {
            window.draw(boardChess[i]);
        }
        window.display();
    }

    return 0;
}
