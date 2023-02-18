void board(const int field, const int size, const int move,sf::Vector2f bP[], sf::RectangleShape arrB[])
{
    int j = 0;
    for (int i = 0; i < field*field; i++)
    {
        sf::RectangleShape rectangle(sf::Vector2f(size, size));
        rectangle.setPosition(size * (i % field) + move, size * j);
        bP[i] = rectangle.getPosition();
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
        if (i % field == field - 1)
        {
            rectangle.setPosition(size * (i % field) + move, size * j);
            // std::cout << std::endl;
            j++;
        }
        *(arrB + i) = rectangle;
        std::cout << bP[i].x << " " << bP[i].y << " " << i << std::endl;
    }
}