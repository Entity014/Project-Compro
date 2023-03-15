#include "libary.h"

void checkWin(sf::RectangleShape &result, sf::RectangleShape &bg, sf::Text &text, sf::RectangleShape &resetB, sf::Text &resetT, Board &mB, Unit enemy[], int dB[], int count, int Pturn)
{
    for (int i = 0; i < count; i++)
    {
        if (enemy[i].isDead && enemy[i].moveType == -5)
        {
            mB.isEnd = true;
            if (Pturn == 0) 
            {
                text.setString("You Win!");
                mB.whoLose = 1;
            }
            else
            {
                text.setString("You Lose!");
                mB.whoLose = 1;
            }
            text.setPosition(result.getPosition().x + result.getSize().x / 2 - text.getGlobalBounds().width / 2, result.getPosition().y + result.getSize().y / 2 - text.getGlobalBounds().height);
            result.setFillColor(sf::Color{7, 242, 129, 255});
            resetB.setFillColor(sf::Color{7, 242, 129, 255});
            text.setFillColor(sf::Color::Black);
            resetT.setFillColor(sf::Color::Black);
            bg.setFillColor(sf::Color::Black);

            // std::cout << "White win" << std::endl;
            // std::cout << i << " " << enemy[i].isDead << std::endl;
        }
        else if (enemy[i].isDead && enemy[i].moveType == 5)
        {
            mB.isEnd = true;
            if (Pturn == 0)
            {
                text.setString("You Lose!");
                mB.whoLose = 0;
            }
            else
            {
                text.setString("You Win!");
                mB.whoLose = 0;
            }
            text.setPosition(result.getPosition().x + result.getSize().x / 2 - text.getGlobalBounds().width / 2, result.getPosition().y + result.getSize().y / 2 - text.getGlobalBounds().height);
            result.setFillColor(sf::Color{7, 242, 129, 255});
            resetB.setFillColor(sf::Color{7, 242, 129, 255});
            text.setFillColor(sf::Color::Black);
            resetT.setFillColor(sf::Color::Black);
            bg.setFillColor(sf::Color::Black);

            // std::cout << "Black win" << std::endl;
        }
    }
}

void loadSound(std::vector<sf::Sound> &soundVector, std::vector<sf::SoundBuffer> &soundBufferVector, std::vector<std::string> pathSound)
{
    for (int i = 0; i < pathSound.size(); i++)
    {
        sf::SoundBuffer bufferX;
        bufferX.loadFromFile(pathSound[i]);
        soundBufferVector.push_back(bufferX);
        // std::cout << i << std::endl;
    }
    for (int i = 0; i < soundBufferVector.size(); i++)
    {
        sf::Sound sound;
        sound.setBuffer(soundBufferVector[i]);
        soundVector.push_back(sound);
    }
}