#include "libary.h"

/* Variable of display */
const int width = 800, height = 600;
const int fields = 8;
const int tileSize = height / fields;
const int moveRight = width - height;

/* Board */
class Board
{
    public:
        sf::RectangleShape boardChess[fields * fields];
        sf::RectangleShape boardSurface[fields * fields];
        sf::Vector2f boardPositions[fields * fields];
        sf::Color boardColor[fields * fields];
        void boardConfig();
        void boardHighlight(int, int, bool);
};

void Board::boardConfig()
{
    int j = 0;
    for (int i = 0; i < fields*fields; i++)
    {
        sf::RectangleShape bChess(sf::Vector2f(tileSize, tileSize));
        sf::RectangleShape bHighlight(sf::Vector2f(tileSize, tileSize));
        bChess.setPosition(tileSize * (i % fields) + moveRight, tileSize * j);
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
            bChess.setPosition(tileSize * (i % fields) + moveRight, tileSize * j);
            // std::cout << std::endl;
            j++;
        }
        *(boardChess + i) = bChess;
        *(boardSurface + i) = bHighlight;
        // std::cout << bP[i].x << " " << bP[i].y << " " << i << std::endl;
        }
}

void Board::boardHighlight(int count, int moveType, bool isMove)
{
    for (int i = 0; i < fields * fields; i++)
    {
        if(isMove == true && (moveType == -1 || moveType == 1))
        {
            boardSurface[i].setFillColor(sf::Color{101, 232, 65, 100});
        }
        else if(isMove == true && (moveType == -2 || moveType == 2))
        {
            boardSurface[i].setFillColor(sf::Color{52, 180, 235, 100});
        }
        else if(isMove == true && (moveType == -3 || moveType == 3))
        {
            boardSurface[i].setFillColor(sf::Color{71, 53, 232, 100});
        }
        else if(isMove == true && (moveType == -4 || moveType == 4))
        {
            boardSurface[i].setFillColor(sf::Color{224, 52, 213, 100});
        }
        else if(isMove == true && (moveType == -5 || moveType == 5))
        {
            boardSurface[i].setFillColor(sf::Color{212, 168, 59, 100});
        }
        else if(isMove == true && (moveType == -6 || moveType == 6))
        {
            boardSurface[i].setFillColor(sf::Color{207, 29, 61, 100});
        }
        else
        {
            boardSurface[i].setFillColor(sf::Color{0, 0, 0, 0});
        }
    }
}

void defaultBoardCheck(const int dB[] ,int N, int &count)
{
    for(int i = 0; i < N; i++)
    {
        if(*(dB + i) != 0)
        {
            count++;
        }
    }
    // std::cout << count << std::endl;
}

void showDefualtBoard(int dB[])
{
    int j;
    for(int i = 0; i < fields * fields; i++)
    {
        std::cout << dB[i] << " ";
        if (i % fields == fields - 1)
        {
            std::cout << std::endl;
            j++;
        }
    }
    std::cout << "----------------------" << std::endl;
}

