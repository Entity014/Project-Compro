#include "libary.h"
void movement(Board &mB, Unit &enemy, sf::Event event, sf::Vector2f mouse, int dB[])
{
        /* Check Click and move */
        if (event.type == sf::Event::MouseButtonPressed)
        {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                        sf::FloatRect bounds = enemy.entity.getGlobalBounds();
                        for (int i = 0; i < fields * fields; i++)
                        {
                                if (bounds.contains(mouse))
                                {
                                        enemy.isMove = true;
                                        // std::cout << enemy.moveType << std::endl;
                                }
                                else if (mB.boardSurface[i].getGlobalBounds().contains(mouse) && int(mB.boardSurface[i].getFillColor().a) != 0 && int(mB.boardSurface[i].getFillColor().r) == 101 && enemy.isMove)
                                {
                                        int temp = 0;
                                        enemy.isMove = false;
                                        enemy.entity.setPosition(mB.boardPositions[i]);
                                        enemy.firstMove = true;
                                        dB[enemy.position] = temp;
                                        dB[i] = enemy.moveType;
                                        enemy.position = i;
                                        enemy.target.clear();
                                        // std::cout << enemy.moveType << " " << i << std::endl;
                                        // std::cout << int(mB.boardSurface[i].getFillColor().a) << std::endl;
                                        break;
                                }
                        }
                }
                else
                {
                        enemy.isMove = false;
                        enemy.canAttack = false;
                }
        }
}

void attack (Board &mB, Unit enemy[], sf::Event event, sf::Vector2f mouse, int dB[], int select, int count)
{
        for (unsigned int i = 0; i < enemy[select].target.size(); i++)
        {
                std::cout << enemy[select].target[i] << " " << enemy[select].target.size() << " " << enemy[select].canAttack << std::endl;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                        // sf::FloatRect bounds = enemy.entity.getGlobalBounds();
                        for (unsigned int i = 0; i < enemy[select].target.size(); i++)
                        {
                                // std::cout << int(mB.boardSurface[enemy.target[i]].getFillColor().a) << " " << enemy.canAttack << std::endl;
                                if (mB.boardSurface[enemy[select].target[i]].getGlobalBounds().contains(mouse) && int(mB.boardSurface[enemy[select].target[i]].getFillColor().a) != 0 && enemy[select].canAttack)
                                {
                                        // std::cout << enemy[select].target[i] << " " << enemy[select].target.size() << " " << enemy[select].canAttack << std::endl;
                                        enemy[select].isMove = false;
                                        // enemy[select].canAttack = false;
                                        // int temp = 0;
                                        // dB[enemy[select].position] = temp;
                                        // dB[enemy[select].target[i]] = enemy[select].moveType;
                                        // enemy[select].position = i;
                                        // enemy[select].target.clear();
                                        // std::cout << "attack " << std::endl;
                                        enemy[select].entity.setPosition(mB.boardPositions[enemy[select].target[i]]);
                                        for (int j = 0; j < count; j++)
                                        {
                                                if (enemy[j].position == enemy[select].target[i])
                                                {
                                                        // std::cout << enemy[j].position << std::endl;
                                                        enemy[j].entity.setPosition(400, 300);
                                                }
                                        }
                                        // enemy.entity[enemy.target[i]].setPosition(400,400) ;
                                }
                        }
                }
        }
}