void board(const int flied, const int Size, sf::RectangleShape arrB[])
{
    int j = 0;
    for (int i = 0; i < flied*flied; i++)
    {
        sf::RectangleShape rectangle(sf::Vector2f(Size, Size));
        if (i % 2 == 1 && j % 2 == 0)
        {
            rectangle.setFillColor(sf::Color::Red);
            rectangle.setPosition(Size*i, 0);
        }
        else if (i % 2 == 0 && j % 2 == 1)
        {
            rectangle.setFillColor(sf::Color::Red);
            rectangle.setPosition(Size*i, 0);
        }
        else
        {
            rectangle.setFillColor(sf::Color::White);
            rectangle.setPosition(Size * i, 0);
        }
        if (i % flied == fields - 1)
        {
            j++;
        }
        *(arrB + i) = rectangle;
    }
}
