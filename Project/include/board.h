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
        void boardHighlight(int [], int, int, bool, bool);
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
        boardPositions[i] = bChess.getPosition() + (0.15f * bChess.getSize());
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

void Board::boardHighlight(int dB[] ,int moveType, int postion, bool isMove, bool firstMove)
{
    
    /* Rook */
    if(isMove && (moveType == -1 || moveType == 1))
    {
        /* Move Y */
        /* Down */
        for (int i = 0; i < fields; i++)
        {
            if (postion + int(fields * i) > postion && postion + int(fields * i) < 64)
            {
                // std::cout << postion + int(fields * i) << " " << postion << std::endl;
                boardSurface[postion + int(fields * i)].setFillColor(sf::Color{52, 180, 235, 100});
                if (dB[postion + int(fields * i)] != 0)
                {
                    boardSurface[postion + int(fields * i)].setFillColor(sf::Color{0, 0, 0, 0});
                    break;
                }
            }
        }

        /* Up */
        for (int i = 0; i < fields; i++)
        {
            if (postion - int(fields * i) < postion && postion - int(fields * i) >= 0)
            {
                // std::cout << postion - int(fields * i) << " " << postion << std::endl;
                boardSurface[postion - int(fields * i)].setFillColor(sf::Color{52, 180, 235, 100});
                if (dB[postion - int(fields * i)] != 0)
                {
                    boardSurface[postion - int(fields * i)].setFillColor(sf::Color{0, 0, 0, 0});
                    break;
                }
            }
        }
        
        /* Move X */
        /* Right */
        for (int i = 0; i < fields; i++)
        {
            if (((postion + i) % fields) > (postion % fields))
            {
                // std::cout << (postion + i) % fields << " " << postion % fields << std::endl;
                boardSurface[postion + i].setFillColor(sf::Color{52, 180, 235, 100});
                if (dB[postion + i] != 0)
                {
                    boardSurface[postion + i].setFillColor(sf::Color{0, 0, 0, 0});
                    break;
                }
            }
        }
        /* Left */
        for (int i = 0; i < fields; i++)
        {
            if (((postion - i) % fields) < (postion % fields) && ((postion - i) % fields) >= 0)
            {
                // std::cout << (postion - i) % fields << " " << postion % fields << std::endl;
                boardSurface[postion - i].setFillColor(sf::Color{52, 180, 235, 100});
                if (dB[postion - i] != 0)
                {
                    boardSurface[postion - i].setFillColor(sf::Color{0, 0, 0, 0});
                    break;
                }
            }
        }
    }

    /* Knight */
    else if(isMove && (moveType == -2 || moveType == 2))
    {
        for (int i = 0; i < fields * fields; i++)
        {
            if (*(dB + i) == 0)
            {
                boardSurface[i].setFillColor(sf::Color{52, 180, 235, 100});
            }
        }
    }

    /* King */
    else if(isMove && (moveType == -5 || moveType == 5))
    {
        for (int i = 0; i < fields * fields; i++)
        {
            // std::cout << postion - int(fields * float(1%fields)) << std::endl;
            if (i % fields < 3)
            {
                /* Move Front */
                if (postion + fields + (i % fields - 1) < 64)
                {
                    boardSurface[postion + fields + (i % fields - 1)].setFillColor(sf::Color{212, 168, 59, 100});
                    if ((dB[postion + fields + (i % fields - 1)] != 0) || ((abs((postion % fields) - (postion + fields +(i % fields - 1)) % fields) == 7) && ((i % fields - 1) != 0)))
                    {
                        boardSurface[postion + fields + (i % fields - 1)].setFillColor(sf::Color{0, 0, 0, 0});
                        // std::cout << (postion + fields +(i % fields - 1)) % fields << " " << postion % fields << std::endl;
                    }
                }
                /* Move Back */
                if (postion - fields + (i % fields - 1) >= 0)
                {
                    boardSurface[postion - fields + (i % fields - 1)].setFillColor(sf::Color{212, 168, 59, 100});
                    if ((dB[postion - fields + (i % fields - 1)] != 0) || (abs((postion % fields) - (postion - fields +(i % fields - 1)) % fields) == 7 && (i % fields - 1) != 0))
                    {
                        boardSurface[postion - fields + (i % fields - 1)].setFillColor(sf::Color{0, 0, 0, 0});
                        // std::cout << (postion - fields + (i % fields - 1)) % fields << " " << postion % fields << std::endl;
                    }
                    // std::cout << (postion - fields + (i % fields - 1)) % fields << " " << postion % fields << std::endl;
                }
                /* Move X */
                if ((i % fields - 1) != 0 && postion + (i % fields - 1) < 64)
                {
                    boardSurface[postion + (i % fields - 1)].setFillColor(sf::Color{212, 168, 59, 100});
                    if ((dB[postion + (i % fields - 1)] != 0) || ((abs((postion % fields) - ((postion + (i % fields - 1)) % fields)) == 7) || ((postion % fields) + ((postion + (i % fields - 1)) % fields)) == -1))
                    {
                        boardSurface[postion + (i % fields - 1)].setFillColor(sf::Color{0, 0, 0, 0});
                        // std::cout << (postion + (i % fields - 1)) % fields << " " << postion % fields << std::endl;
                    }
                    // std::cout << (postion + (i % fields - 1)) % fields << " " << postion % fields << std::endl;
                }
            }
        }
    }

    /* Pawn */
    else if(isMove && (moveType == -6 || moveType == 6))
    {
        for (int i = 0; i < fields * fields; i++)
        {
            if(!firstMove)
            {
                /* Move Y */
                if (i % fields < 3 && i % fields > 0)
                {
                    /* Black Pawn */
                    if (moveType == -6)
                    {
                        boardSurface[postion + int(fields * float(i%fields))].setFillColor(sf::Color{207, 29, 61, 100});
                        if (dB[postion + int(fields * float(i%fields))] != 0)
                        {
                            boardSurface[postion + int(fields * float(i%fields))].setFillColor(sf::Color{0, 0, 0, 0});
                            break;
                        }
                    }
                    /* White Pawn */
                    else
                    {
                        boardSurface[postion - int(fields * float(i%fields))].setFillColor(sf::Color{207, 29, 61, 100});
                        if (dB[postion - int(fields * float(i%fields))] != 0)
                        {
                            boardSurface[postion - int(fields * float(i%fields))].setFillColor(sf::Color{0, 0, 0, 0});
                            break;
                        }
                    }
                }
            }
            else
            {
                if (i % fields < 2 && i % fields > 0)
                {
                    if ((moveType == -6) && (dB[postion + int(fields * float(i%fields))] == 0) && ((postion + int(fields * float(i%fields))) < 64))
                    {
                        boardSurface[postion + int(fields * float(i%fields))].setFillColor(sf::Color{212, 168, 59, 100});
                        // std::cout << postion + int(fields * float(i%fields)) << std::endl;
                    }
                    else if ((moveType == 6) && (dB[postion - int(fields * float(i%fields))] == 0) && ((postion - int(fields * float(i%fields))) > 0))
                    {
                        boardSurface[postion - int(fields * float(i%fields))].setFillColor(sf::Color{212, 168, 59, 100});
                        // std::cout << postion - int(fields * float(i%fields)) << std::endl;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < fields * fields; i++) boardSurface[i].setFillColor(sf::Color{0, 0, 0, 0});
    }
    for (int i = 0; i < fields * fields; i++)
    {
        /* Bishop */
        if(isMove && (moveType == -3 || moveType == 3))
        {
            if (*(dB + i) == 0)
            {
                boardSurface[i].setFillColor(sf::Color{71, 53, 232, 100});
            }
        }

        /* Queen */
        else if(isMove && (moveType == -4 || moveType == 4))
        {
            if (*(dB + i) == 0)
            {
                /* Move Y */
                boardSurface[i].setFillColor(sf::Color{224, 52, 213, 100});
                std::cout << postion - int(fields * float(i%fields)) << std::endl;
            }
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