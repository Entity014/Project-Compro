void board(const int fields, const int size, const int move,sf::Vector2f bP[], sf::RectangleShape arrB[], sf::Color bColor[])
{
    int j = 0;
    for (int i = 0; i < fields*fields; i++)
    {
        sf::RectangleShape rectangle(sf::Vector2f(size, size));
        rectangle.setPosition(size * (i % fields) + move, size * j);
        bP[i] = rectangle.getPosition() + 0.15f * rectangle.getSize();
        if (i % 2 == 1 && j % 2 == 0)
        {
            // std::cout << "1" << " ";
            rectangle.setFillColor(sf::Color{164, 164, 164, 255});
        }
        else if (i % 2 == 0 && j % 2 == 1)
        {
            // std::cout << "1" << " ";
            rectangle.setFillColor(sf::Color{164, 164, 164, 255});
        }
        else
        {
            // std::cout << "0" << " ";
            rectangle.setFillColor(sf::Color{0, 0, 0, 225});
        }
        if (i % fields == fields - 1)
        {
            rectangle.setPosition(size * (i % fields) + move, size * j);
            // std::cout << std::endl;
            j++;
        }
        *(bColor + i) = rectangle.getFillColor();
        *(arrB + i) = rectangle;
        // std::cout << bP[i].x << " " << bP[i].y << " " << i << std::endl;
        }
}

void highlight(sf::RectangleShape bC[], sf::Color bColor[], const int fields, int dB[], bool isMove)
{
    for (int i = 0; i < fields * fields; i++)
    {
        if(isMove == true)
        {
            bC[i].setFillColor(sf::Color::Red);
        }
        else
        {
            bC[i].setFillColor(sf::Color(bColor[i]));
        }
    }
}
//ka
