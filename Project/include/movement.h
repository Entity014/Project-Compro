#include "libary.h"

void movement(sf::Sprite sE[], sf::Vector2f bP[], sf::RectangleShape bC[], sf::Vector2f mouse, sf::Event event, const int fields, bool &isMove){
        /* Check Click and move */
        int j = 0;
        if(event.type == sf::Event::MouseButtonPressed)
        {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                        for (int i = 0; i < fields * fields; i++)
                        {
                                /* Get Variable of entity */
                                sf::FloatRect bounds = sE[0].getGlobalBounds();

                                /* Check mouse click on entity */
                                if (bounds.contains(mouse))
                                {
                                        isMove = true;
                                }
                                else if(bC[i].getGlobalBounds().contains(mouse) && isMove == true)
                                {
                                        isMove = false;
                                        sE[0].setPosition(bP[i]);
                                        break;
                                }
                                std::cout << isMove << " " << bC[0].getGlobalBounds().contains(mouse) << std::endl;
                        }
                }
        }
        //  if(event sf::Event::MouseButtonReleased(sf::Mouse::Left))
        //         {
        //                 sf::FloatRect bounds = sE[0].getGlobalBounds();
        //                 if (bounds.contains(mouse))
        //         {
        //                 sE[0].setPosition(mouse);
        //                 // mouse is on sprite!
        //         }
        //         }
}

