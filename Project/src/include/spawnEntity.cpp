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
    sf::Texture t;
    int countE = 0;
    for(int i = 0; i < N; i++)
    {
        if (*(dB + i) < 0)
        {
            sE[countE].setTexture(tE[abs(*(dB + i)) - 1]);
            sE[countE].setScale(sf::Vector2f(0.45f, 0.45f));
            // std::cout << countE << std::endl;
            countE++;
        }
        else if (*(dB + i) > 0)
        {
            sE[countE].setTexture(tE[*(dB + i) + 5]);
            sE[countE].setScale(sf::Vector2f(0.45f, 0.45f));
            // std::cout << countE << std::endl;
            countE++;
        }
    }
}