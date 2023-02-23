void board(const int fields, const int size, const int move,sf::Vector2f bP[], sf::RectangleShape bC[], sf::RectangleShape bH[])
{
    int j = 0;
    for (int i = 0; i < fields*fields; i++)
    {
        sf::RectangleShape bChess(sf::Vector2f(size, size));
        sf::RectangleShape bHighlight(sf::Vector2f(size, size));
        bChess.setPosition(size * (i % fields) + move, size * j);
        bHighlight.setPosition(bChess.getPosition());
        bHighlight.setFillColor(sf::Color{101, 232, 65, 0});
        bP[i] = bChess.getPosition() + 0.15f * bChess.getSize();
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
        *(bC + i) = bChess;
        *(bH + i) = bHighlight;
        // std::cout << bP[i].x << " " << bP[i].y << " " << i << std::endl;
        }
}

void highlight(sf::RectangleShape bC[], sf::RectangleShape bH[], const int fields, int dB[], bool isMove)
{
    for (int i = 0; i < fields * fields; i++)
    {
        if(isMove == true)
        {
            bH[i].setFillColor(sf::Color{101, 232, 65, 100});
        }
        else
        {
            bH[i].setFillColor(sf::Color{101, 232, 65, 0});
        }
    }
}

