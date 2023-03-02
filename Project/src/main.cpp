/* Include */
#include "../include/board.h"
#include "../include/unitConfig.h"
#include "../include/movement.h"
#include "../include/game.h"

/* Board */
Board masterBoard;

/* Entity */
/* In Future, it must change */
int defaultBoard[fields * fields] =
{
    -1, -2, -3, -4, -5, -3, -2, -1,
    -6, -6, -6, -6, -6, -6, -6, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 6, 6,
    1, 2, 3, 5, 4, 3, 2, 1
};
int tempBoard[fields * fields] =
{
    -1, -2, -3, -4, -5, -3, -2, -1,
    -6, -6, -6, -6, -6, -6, -6, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    6, 6, 6, 6, 6, 6, 6, 6,
    1, 2, 3, 5, 4, 3, 2, 1
};
/* Sandbox */
// int defaultBoard[fields * fields] =
// {
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     6, 0, 0, 6, 0, 0, 0, 6,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, -4, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0
// };
int count = 0;

/* Texture */
std::string pathE[12] = 
{
    "asset/texture/b_rook_png_128px.png", "asset/texture/b_knight_png_128px.png", "asset/texture/b_bishop_png_128px.png", "asset/texture/b_queen_png_128px.png", "asset/texture/b_king_png_128px.png", "asset/texture/b_pawn_png_128px.png",
    "asset/texture/w_rook_png_128px.png", "asset/texture/w_knight_png_128px.png", "asset/texture/w_bishop_png_128px.png", "asset/texture/w_queen_png_128px.png", "asset/texture/w_king_png_128px.png", "asset/texture/w_pawn_png_128px.png"
};
std::string pathP[] =
{
    "asset/texture/test.png"
};

int main()
{
    /* Status */
    srand(time(0));
    sf::RectangleShape Status(sf::Vector2f(moveRight, height));
    masterBoard.boardConfig();
    defaultBoardCheck(defaultBoard, fields * fields, count);
    masterBoard.whoTurn = rand()%2;

    /* Unit */
    Unit player[4], enemy[count];
    int unitChess[count];
    int countE = 0, select = -1;
    for (int i = 0; i < fields * fields; i++)
    {
        if (*(defaultBoard + i) < 0)
        {
            enemy[countE].unitType = "Enemy";
            enemy[countE].entityConfig(pathE[abs(*(defaultBoard + i)) - 1], masterBoard.boardPositions[i], Status);
            enemy[countE].moveType = *(defaultBoard + i);
            enemy[countE].position = i;
            // std::cout << enemy[countE].entityType << std::endl;
            countE++;
        }
        else if (*(defaultBoard + i) > 0)
        {
            enemy[countE].unitType = "Enemy";
            enemy[countE].entityConfig(pathE[*(defaultBoard + i) + 5], masterBoard.boardPositions[i], Status);
            enemy[countE].moveType = *(defaultBoard + i);
            enemy[countE].position = i;
            // std::cout << enemy[countE].entityType << std::endl;
            countE++;
        }
    }

    for (int i = 0; i < sizeof(pathP)/sizeof(pathP[0]); i++)
    {
        player[i].unitType = "Player";
        player[i].entityConfig(pathP[i], sf::Vector2f(0.f, 0.f), Status);
    }
    player[0].entity.setTextureRect(sf::IntRect(700, 0, 700, 1000));

    /* boundingBox */
    // sf::FloatRect boundingBox = enemy[0].entity.getGlobalBounds();
    // sf::RectangleShape boundingBoxShape(sf::Vector2f(boundingBox.width, boundingBox.height));
    // boundingBoxShape.setPosition(boundingBox.left, boundingBox.top);
    // boundingBoxShape.setFillColor(sf::Color::Transparent);
    // boundingBoxShape.setOutlineColor(sf::Color::Red);
    // boundingBoxShape.setOutlineThickness(1.f);

    /* Reander Main Window */
    bool firstLayer = false;
    sf::RenderWindow mainWindow(sf::VideoMode(width, height), "Main Window");
    sf::RenderWindow game(sf::VideoMode(width, height), "Chess Mae");
    game.setVisible(false);
    
    sf::Font font;
    if (!font.loadFromFile("asset/font/arial.TTF"))
    {
        std::cout << "Cannot load font arial.ttf" << std::endl;
    }
    
    sf::Text title("Chess Mae", font, 50);
    title.setFillColor(sf::Color::White);
    title.setPosition(mainWindow.getSize().x / 2 - title.getGlobalBounds().width / 2, 100);

    /* Button Main Window */
    /* First Layer */
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setPosition(mainWindow.getSize().x / 2 - playButton.getSize().x / 2, 250);
    playButton.setFillColor(sf::Color::Black);
    sf::Text playText("Play", font, 30);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(playButton.getPosition().x + playButton.getSize().x / 2 - playText.getGlobalBounds().width / 2, playButton.getPosition().y + playButton.getSize().y / 2 - playText.getGlobalBounds().height / 2);

    sf::RectangleShape quitButton(sf::Vector2f(200, 50));
    quitButton.setFillColor(sf::Color::Black);
    quitButton.setPosition(mainWindow.getSize().x / 2 - quitButton.getSize().x / 2, 350);
    sf::Text quitText("Quit", font, 30);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(quitButton.getPosition().x + quitButton.getSize().x / 2 - quitText.getGlobalBounds().width / 2, quitButton.getPosition().y + quitButton.getSize().y / 2 - quitText.getGlobalBounds().height / 2);

    /* Second Layer */
    sf::RectangleShape hostButton(sf::Vector2f(200, 50));
    hostButton.setFillColor(sf::Color{0, 0, 0, 0});
    hostButton.setPosition(mainWindow.getSize().x / 4 - hostButton.getSize().x / 2, 250);
    sf::Text hostText("Host", font, 30);
    hostText.setFillColor(sf::Color{0, 0, 0, 0});
    hostText.setPosition(hostButton.getPosition().x + hostButton.getSize().x / 2 - hostText.getGlobalBounds().width / 2, hostButton.getPosition().y + hostButton.getSize().y / 2 - hostText.getGlobalBounds().height / 2);

    sf::RectangleShape joinButton(sf::Vector2f(200, 50));
    joinButton.setFillColor(sf::Color{0, 0, 0, 0});
    joinButton.setPosition(3*mainWindow.getSize().x / 4 - joinButton.getSize().x / 2, 450);
    sf::Text joinText("Join", font, 30);
    joinText.setFillColor(sf::Color{0, 0, 0, 0});
    joinText.setPosition(joinButton.getPosition().x + joinButton.getSize().x / 2 - joinText.getGlobalBounds().width / 2, joinButton.getPosition().y + joinButton.getSize().y / 2 - joinText.getGlobalBounds().height / 2);

    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
                game.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && !firstLayer)
                    {
                        playButton.setFillColor(sf::Color{0, 0, 0, 0});
                        playText.setFillColor(sf::Color{0, 0, 0, 0});
                        hostButton.setFillColor(sf::Color::Black);
                        hostText.setFillColor(sf::Color::White);
                        joinButton.setFillColor(sf::Color::Black);
                        joinText.setFillColor(sf::Color::White);
                        firstLayer = true;
                    }
                    else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        mainWindow.close();
                        game.close();
                    }
                    else if (hostButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer)
                    {
                        mainWindow.close();
                        game.setVisible(true);
                    }
                    else if (joinButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer)
                    {
                        std::cout << "Testing" << std::endl;
                    }
                }
            }
        }

        mainWindow.clear();
        mainWindow.draw(title);
        mainWindow.draw(playButton);
        mainWindow.draw(playText);
        mainWindow.draw(quitButton);
        mainWindow.draw(quitText);
        mainWindow.draw(hostButton);
        mainWindow.draw(hostText);
        mainWindow.draw(joinButton);
        mainWindow.draw(joinText);
        mainWindow.display();
    }

    /* Reander Game */
    game.setActive(true);

    /* Button Game */
    sf::RectangleShape resetButton(sf::Vector2f(200, 50));
    // resetButton.setPosition(Status.getSize().x / 2 - resetButton.getSize().x / 2, 0);
    resetButton.setPosition(game.getSize().x / 2 - resetButton.getSize().x / 2, 0);
    resetButton.setFillColor(sf::Color{0, 0, 0, 0});
    sf::Text resetText("Reset", font, 30);
    resetText.setFillColor(sf::Color{0, 0, 0, 0});
    resetText.setPosition(resetButton.getPosition().x + resetButton.getSize().x / 2 - resetText.getGlobalBounds().width / 2, resetButton.getPosition().y + resetButton.getSize().y / 2 - resetText.getGlobalBounds().height);

    /* Result Screen */
    sf::RectangleShape isTurnScreen(sf::Vector2f(250, 50));
    sf::RectangleShape background(sf::Vector2f(width, height));
    sf::RectangleShape resultScreen(sf::Vector2f(1000, 200));

    /* Position */
    isTurnScreen.setPosition(Status.getSize().x / 2 - isTurnScreen.getSize().x / 2, 700);
    resultScreen.setPosition(game.getSize().x / 2 - resultScreen.getSize().x / 2, game.getSize().y / 2 - resultScreen.getSize().y / 2);
    background.setPosition(sf::Vector2f(0.0f, 0.0f));

    /* Color */
    isTurnScreen.setFillColor(sf::Color{7, 242, 129, 255});
    resultScreen.setFillColor(sf::Color{0, 0, 0, 0});
    background.setFillColor(sf::Color{0, 0, 0, 0});

    /* Text */
    sf::Text isTurnText("Turn Test", font, 30);
    sf::Text resultText("result Test", font, 200);
    resultText.setFillColor(sf::Color{0, 0, 0, 0});
    isTurnText.setFillColor(sf::Color{0, 0, 0, 0});

    while (game.isOpen())
    {
        countE = 0;
        sf::Event event;
        sf::Vector2f mouse = game.mapPixelToCoords(sf::Mouse::getPosition(game));

        /* Check */
        checkWin(resultScreen, background, resultText, resetButton, resetText, masterBoard, enemy, defaultBoard, count);

        // std::cout << masterBoard.isEnd << std::endl;
        while (game.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) game.close();

            /* Reset Button */
            if (masterBoard.isEnd)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (resetButton.getGlobalBounds().contains(mouse))
                        {
                            // std::cout << "Reset button pressed" << std::endl;
                            for (int j = 0; j < fields * fields; j++)
                            {
                                defaultBoard[j] = tempBoard[j];
                                if (enemy[countE].moveType == tempBoard[j])
                                {
                                    // std::cout << enemy[dummy].moveType << std::endl;
                                    // std::cout << masterBoard.boardPositions[j].x << " " << masterBoard.boardPositions[j].y << " " << j << std::endl;
                                    /* Screen */
                                    resultScreen.setFillColor(sf::Color{0, 0, 0, 0});
                                    resultText.setFillColor(sf::Color{0, 0, 0, 0});
                                    background.setFillColor(sf::Color{0, 0, 0, 0});
                                    resetButton.setFillColor(sf::Color{0, 0, 0, 0});
                                    resetText.setFillColor(sf::Color{0, 0, 0, 0});

                                    /* Unit */
                                    enemy[countE].entity.setPosition(masterBoard.boardPositions[j]);
                                    enemy[countE].position = j;
                                    enemy[countE].firstMove = false;
                                    enemy[countE].isMove = false;
                                    enemy[countE].isDead = false;
                                    enemy[countE].canAttack = false;
                                    enemy[countE].kill = false;
                                    masterBoard.isEnd = false;
                                    masterBoard.whoTurn = rand()%2;
                                    countE++;
                                }
                            }
                            countE = 0;
                            // std::cout << "-----------------------------------" << std::endl;
                        }
                    }
                }
            }

            /* Movement */
            // std::cout << enemy[select].isMove << std::endl;
            for (int i = 0; i < count; i++)
            {
                if (!enemy[select].canAttack)
                {
                    if (!masterBoard.whoTurn && enemy[i].moveType > 0)
                    {
                        movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count);
                        isTurnText.setString("White's Turn");
                        isTurnText.setFillColor(sf::Color::Black);
                        isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                    }
                    else if (masterBoard.whoTurn && enemy[i].moveType < 0)
                    {
                        movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count);
                        isTurnText.setString("Black's Turn");
                        isTurnText.setFillColor(sf::Color::Black);
                        isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                    }
                }
                if (select != -1)
                {
                    if (enemy[select].canAttack)
                    {
                        // std::cout << enemy[select].canAttack << std::endl;
                        if (!masterBoard.whoTurn && enemy[i].moveType > 0)
                        {
                            movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count);
                            isTurnText.setString("White's Turn");
                            isTurnText.setFillColor(sf::Color::Black);
                            isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                        }
                        else if (masterBoard.whoTurn && enemy[i].moveType < 0)
                        {
                            movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count);
                            isTurnText.setString("White's Turn");
                            isTurnText.setFillColor(sf::Color::Black);
                            isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                        }
                        // std::cout << enemy[select].isMove << std::endl;
                    }
                }
                if (enemy[i].isMove && !enemy[select].isMove) 
                {
                    select = i;
                }
                if (enemy[i].isMove && enemy[select].isMove && i != select)
                {
                    enemy[select].isMove = false;
                }
            }
            masterBoard.boardHighlight(defaultBoard, enemy[select].moveType, enemy[select].position, enemy[select].target, enemy[select].isMove, enemy[select].firstMove, enemy[select].canAttack);
        }

        // showDefualtBoard(defaultBoard);

        /* Draw */
        game.clear();
        game.draw(Status);
        for (int i = 0; i < fields * fields; i++)
        {
            game.draw(masterBoard.boardChess[i]);
            game.draw(masterBoard.boardSurface[i]);
        }
        for (int i = 0; i < count; i++)
        {
            game.draw(enemy[i].entity);
        }
        game.draw(player[0].entity);
        game.draw(isTurnScreen);
        game.draw(isTurnText);
        game.draw(background);
        game.draw(resultScreen);
        game.draw(resultText);
        game.draw(resetButton);
        game.draw(resetText);
        // game.draw(boundingBoxShape);
        game.display();
    }

    return 0;
}