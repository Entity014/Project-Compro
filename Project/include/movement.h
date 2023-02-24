#include "libary.h"

// void movement(sf::Sprite sE[], sf::Vector2f bP[], sf::RectangleShape bC[], sf::Vector2f mouse, sf::Event event, int count, int uC[], const int fields, bool isMove[]){
//         int j = 0;
//         /* Check Click and move */
//         if(event.type == sf::Event::MouseButtonPressed)
//         {
//                 if (event.mouseButton.button == sf::Mouse::Left)
//                 {
//                         for (int i = 0; i < fields * fields; i++)
//                         {
//                                 /* Get Variable of entity */
//                                 for (int j = 0; j < count; j++)
//                                 {
//                                         sf::FloatRect bounds = sE[j].getGlobalBounds();
//                                         /* Check mouse click on entity */
//                                         if (bounds.contains(mouse))
//                                         {
//                                                 isMove = true;
//                                         }
//                                         else if(bC[i].getGlobalBounds().contains(mouse) && isMove == true)
//                                         {
//                                                 isMove = false;
//                                                 sE[j].setPosition(bP[i]);
//                                                 break;
//                                         }
//                                         // std::cout << isMove << " " << bC[0].getGlobalBounds().contains(mouse) << std::endl;
//                                 }
//                         }

//                 }
//         }
// }

void movement(Board mB, Unit &enemy, sf::Event event, sf::Vector2f mouse)
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
                                }
                                if (mB.boardChess[i].getGlobalBounds().contains(mouse) && enemy.isMove == true)
                                {
                                        enemy.isMove = false;
                                        enemy.entity.setPosition(mB.boardPositions[i]);
                                        break;
                                }
                                // else if (bounds.contains(mouse) && enemy.isMove == true)
                                // {
                                //         enemy.isMove = false;
                                // }
                        }
                }
        }
}