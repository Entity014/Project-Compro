#include "libary.h"

const int fields = 8;

/* Board */
class board
{
    public:
        sf::RectangleShape boardChess[fields * fields];
        sf::RectangleShape boardSurface[fields * fields];
        sf::Vector2f boardPositions[fields * fields];
        sf::Color boardColor[fields * fields];
        void boardConfig(const int, const int, const int);
        void boardHighlight(const int, int [], bool);
};

void board::boardConfig(const int fields, const int size, const int move)
{
    int j = 0;
    for (int i = 0; i < fields*fields; i++)
    {
        sf::RectangleShape bChess(sf::Vector2f(size, size));
        sf::RectangleShape bHighlight(sf::Vector2f(size, size));
        bChess.setPosition(size * (i % fields) + move, size * j);
        bHighlight.setPosition(bChess.getPosition());
        bHighlight.setFillColor(sf::Color{101, 232, 65, 0});
        boardPositions[i] = bChess.getPosition() + 0.15f * bChess.getSize();
        if (i % 2 == 1 && j % 2 == 0)
        {
            // std::cout << "1" << " ";
            bChess.setFillColor(sf::Color{164, 164, 164, 255});
        }
        else if (i % 2 == 0 && j % 2 == 1)
        {
            // std::cout << "1" << " ";
            bChess.setFillColor(sf::Color{164, 164, 164, 255});
        }
        else
        {
            // std::cout << "0" << " ";
            bChess.setFillColor(sf::Color{0, 0, 0, 225});
        }
        if (i % fields == fields - 1)
        {
            bChess.setPosition(size * (i % fields) + move, size * j);
            // std::cout << std::endl;
            j++;
        }
        *(boardChess + i) = bChess;
        *(boardSurface + i) = bHighlight;
        // std::cout << bP[i].x << " " << bP[i].y << " " << i << std::endl;
        }
}

void board::boardHighlight(const int fields, int dB[], bool isMove)
{
    for (int i = 0; i < fields * fields; i++)
    {
        if(isMove == true)
        {
            boardSurface[i].setFillColor(sf::Color{101, 232, 65, 100});
        }
        else
        {
            boardSurface[i].setFillColor(sf::Color{101, 232, 65, 0});
        }
    }
}

