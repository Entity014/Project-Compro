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

void loadTextures(sf::Texture tE[], const std::string pE[], int N)
{
    for (int i = 0; i < N; i++)
    {
        if(!tE[i].loadFromFile(pE[i]))
        {
            std::cout << "Cannot load texture " << pE[i] << std::endl;
        }
        tE[i].setSmooth(true);
    }
}

void entityConfig(const int dB[], const sf::Texture tE[], sf::Sprite sE[], sf::Vector2f bP[], int N)
{
    int countE = 0;
    for(int i = 0; i < N; i++)
    {
        if (*(dB + i) < 0)
        {
            sE[countE].setTexture(tE[abs(*(dB + i)) - 1]);
            sE[countE].setScale(sf::Vector2f(0.45f, 0.45f));
            sE[countE].setPosition(bP[i]);
            // std::cout << countE << std::endl;
            countE++;
        }
        else if (*(dB + i) > 0)
        {
            sE[countE].setTexture(tE[*(dB + i) + 5]);
            sE[countE].setScale(sf::Vector2f(0.45f, 0.45f));
            sE[countE].setPosition(bP[i]);
            // std::cout << countE << std::endl;
            countE++;
        }
    }
}

void playerConfig(const sf::Texture tP[], sf::Sprite sP[], sf::RectangleShape Status, int N)
{
    int countP = 0;
    sf::Vector2f leftBottom = Status.getPosition();
    leftBottom.y += Status.getSize().y / 1.70f;
    for (int i = 0; i < N; i++)
    {
        sP[countP].setTexture(tP[i]);
        sP[countP].setScale(sf::Vector2f(0.25f, 0.25f));
        sP[countP].setPosition(leftBottom);
        countP++;
        // std::cout << leftBottom.y << std::endl;
    }
}
//p