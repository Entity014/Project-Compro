#include "libary.h"
void movement(Board &mB, Unit &enemy, sf::Event event, sf::Vector2f mouse, int dB[])
{
        /* Check Click and move */
        if (event.type == sf::Event::MouseButtonPressed)
        {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                        for (int i = 0; i < fields * fields; i++)
                        {
                                sf::FloatRect bounds = enemy.entity.getGlobalBounds();
                                if (bounds.contains(mouse))
                                {
                                        enemy.isMove = true;
                                        // std::cout << enemy.moveType << std::endl;
                                }
                                else if (mB.boardSurface[i].getGlobalBounds().contains(mouse) && int(mB.boardSurface[i].getFillColor().a) != 0 && enemy.isMove)
                                {
                                        int temp = 0;
                                        enemy.isMove = false;
                                        enemy.entity.setPosition(mB.boardPositions[i]);
                                        enemy.firstMove = true;
                                        dB[enemy.position] = temp;
                                        dB[i] = enemy.moveType;
                                        enemy.position = i;
                                        std::cout << enemy.moveType << " " << i << std::endl;
                                        // std::cout << int(mB.boardSurface[i].getFillColor().a) << std::endl;
                                        break;
                                }
                        }
                }
                else
                {
                        enemy.isMove = false;
                }
        }
}
