#include "board.h"
#include <SFML/Graphics.hpp>

void board(const int flied, const int Size, sf::RectangleShape arrB[])
{
    int j = 0;
    for (int i = 0; i < flied*flied; i++)
    {
        sf::RectangleShape rectangle(sf::Vector2f(Size, Size));
        if (i % 2 == 1 && j % 2 == 0)
        {
            rectangle.setFillColor(sf::Color::Black);
        }
        else if (i % 2 == 0 && j % 2 == 1)
        {
            rectangle.setFillColor(sf::Color::Black);
        }
        else
        {
            rectangle.setFillColor(sf::Color::White);
        }
        *(arrB + i) = rectangle;
        j++;
    }
}