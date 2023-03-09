/* Include */
#include "../include/board.h"
#include "../include/unitConfig.h"
#include "../include/movement.h"
#include "../include/game.h"
#include "../include/server.h"

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

/* Client Setting*/
std::string id;
std::string inputText = "";
std::vector<sf::Text> inputMainMenu;
std::vector<std::string> usernameAndIp;
char connectionType;

int main()
{
    /* Reander Main Window */
    bool firstLayer = false;
    bool secondLayer = false;
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
    sf::RectangleShape backButton(sf::Vector2f(200, 50));
    backButton.setPosition(mainWindow.getSize().x / 2 - backButton.getSize().x / 2, 350);
    backButton.setFillColor(sf::Color{0, 0, 0, 0});
    sf::Text backText("Back", font, 30);
    backText.setFillColor(sf::Color{0, 0, 0, 0});
    backText.setPosition(backButton.getPosition().x + backButton.getSize().x / 2 - backText.getGlobalBounds().width / 2, backButton.getPosition().y + backButton.getSize().y / 2 - backText.getGlobalBounds().height / 2);

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
    sf::RectangleShape serverButton(sf::Vector2f(200, 50));
    serverButton.setFillColor(sf::Color{0, 0, 0, 0});
    serverButton.setPosition(mainWindow.getSize().x / 4 - serverButton.getSize().x / 2, 250);
    sf::Text serverText("Server", font, 30);
    serverText.setFillColor(sf::Color{0, 0, 0, 0});
    serverText.setPosition(serverButton.getPosition().x + serverButton.getSize().x / 2 - serverText.getGlobalBounds().width / 2, serverButton.getPosition().y + serverButton.getSize().y / 2 - serverText.getGlobalBounds().height / 2);

    sf::RectangleShape joinButton(sf::Vector2f(200, 50));
    joinButton.setFillColor(sf::Color{0, 0, 0, 0});
    joinButton.setPosition(3*mainWindow.getSize().x / 4 - joinButton.getSize().x / 2, 450);
    sf::Text joinText("Join", font, 30);
    joinText.setFillColor(sf::Color{0, 0, 0, 0});
    joinText.setPosition(joinButton.getPosition().x + joinButton.getSize().x / 2 - joinText.getGlobalBounds().width / 2, joinButton.getPosition().y + joinButton.getSize().y / 2 - joinText.getGlobalBounds().height / 2);

    /* Third Layer */
    sf::RectangleShape connectButton(sf::Vector2f(200, 50));
    connectButton.setFillColor(sf::Color{0, 0, 0, 0});
    connectButton.setPosition(3*mainWindow.getSize().x / 4 - connectButton.getSize().x / 2, 375);
    sf::Text connectText("Connect", font, 30);
    connectText.setFillColor(sf::Color{0, 0, 0, 0});
    connectText.setPosition(connectButton.getPosition().x + connectButton.getSize().x / 2 - connectText.getGlobalBounds().width / 2, connectButton.getPosition().y + connectButton.getSize().y / 2 - connectText.getGlobalBounds().height / 2);
    
    sf::Text guideText1("Enter to comfirm", font, 30);
    guideText1.setFillColor(sf::Color{0, 0, 0, 0});
    guideText1.setPosition(mainWindow.getSize().x / 2 - guideText1.getGlobalBounds().width / 2, 550);
    sf::Text drawInputText(inputText, font, 30);

    sf::RectangleShape usernameBox(sf::Vector2f(300,50));
    usernameBox.setFillColor(sf::Color{0, 0, 0, 0});
    usernameBox.setPosition(mainWindow.getSize().x * 1.2 / 2 - usernameBox.getSize().x / 2, 200);
    sf::Text usernameText("Username :", font, 30);
    usernameText.setFillColor(sf::Color{0, 0, 0, 0});
    usernameText.setPosition(mainWindow.getSize().x / 4 - usernameText.getGlobalBounds().width / 2, 200);
    
    sf::RectangleShape ipAddressBox(sf::Vector2f(300,50));
    ipAddressBox.setFillColor(sf::Color{0, 0, 0, 0});
    ipAddressBox.setPosition(mainWindow.getSize().x * 1.2 / 2 - ipAddressBox.getSize().x / 2, 300);
    sf::Text ipAddressText("Ip Address :", font, 30);
    ipAddressText.setFillColor(sf::Color{0, 0, 0, 0});
    ipAddressText.setPosition(mainWindow.getSize().x / 4 - ipAddressText.getGlobalBounds().width / 2, 300);

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

            // std::cout << firstLayer << " " << secondLayer << std::endl;
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && !firstLayer)
                    {
                        quitButton.setPosition(quitButton.getPosition().x, quitButton.getPosition().y + 100);
                        quitText.setPosition(quitText.getPosition().x, quitText.getPosition().y + 100);
                        /* Color */
                        playButton.setFillColor(sf::Color{0, 0, 0, 0});
                        playText.setFillColor(sf::Color{0, 0, 0, 0});
                        serverButton.setFillColor(sf::Color::Black);
                        serverText.setFillColor(sf::Color::White);
                        joinButton.setFillColor(sf::Color::Black);
                        joinText.setFillColor(sf::Color::White);
                        backButton.setFillColor(sf::Color::Black);
                        backText.setFillColor(sf::Color::White);
                        firstLayer = true;
                    }
                    else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && secondLayer)
                    {
                        inputText = "";
                        inputMainMenu.clear();
                        /* Position */
                        quitButton.setPosition(quitButton.getPosition().x + 200, quitButton.getPosition().y);
                        quitText.setPosition(quitText.getPosition().x + 200, quitText.getPosition().y);
                        backButton.setPosition(backButton.getPosition().x + 200, backButton.getPosition().y - 25);
                        backText.setPosition(backText.getPosition().x + 200, backText.getPosition().y - 25);

                        /* Color */
                        drawInputText.setFillColor(sf::Color{0, 0, 0, 0});
                        for (int i = 0; i < inputMainMenu.size(); i++)
                        {
                            inputMainMenu[i].setFillColor(sf::Color{0, 0, 0, 0});
                        }
                        guideText1.setFillColor(sf::Color{0, 0, 0, 0});
                        usernameBox.setFillColor(sf::Color{0, 0, 0, 0});
                        usernameText.setFillColor(sf::Color{0, 0, 0, 0});
                        ipAddressBox.setFillColor(sf::Color{0, 0, 0, 0});
                        ipAddressText.setFillColor(sf::Color{0, 0, 0, 0});
                        connectButton.setFillColor(sf::Color{0, 0, 0, 0});
                        connectText.setFillColor(sf::Color{0, 0, 0, 0});
                        serverButton.setFillColor(sf::Color::Black);
                        serverText.setFillColor(sf::Color::White);
                        joinButton.setFillColor(sf::Color::Black);
                        joinText.setFillColor(sf::Color::White);
                        backButton.setFillColor(sf::Color::Black);
                        backText.setFillColor(sf::Color::White);
                        secondLayer = false;
                    }
                    else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer)
                    {
                        quitButton.setPosition(quitButton.getPosition().x, quitButton.getPosition().y - 100);
                        quitText.setPosition(quitText.getPosition().x, quitText.getPosition().y - 100);

                        /* Color */
                        playButton.setFillColor(sf::Color::Black);
                        playText.setFillColor(sf::Color::White);
                        serverButton.setFillColor(sf::Color{0, 0, 0, 0});
                        serverText.setFillColor(sf::Color{0, 0, 0, 0});
                        joinButton.setFillColor(sf::Color{0, 0, 0, 0});
                        joinText.setFillColor(sf::Color{0, 0, 0, 0});
                        backButton.setFillColor(sf::Color{0, 0, 0, 0});
                        backText.setFillColor(sf::Color{0, 0, 0, 0});
                        firstLayer = false;
                    }
                    else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        mainWindow.close();
                        game.close();
                    }
                    else if (serverButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer && !secondLayer)
                    {
                        mainWindow.close();
                        connectionType = 's';
                        // hostServer();
                        // game.setVisible(true);
                    }
                    else if (joinButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer && !secondLayer)
                    {
                        quitButton.setPosition(quitButton.getPosition().x - 200, quitButton.getPosition().y);
                        quitText.setPosition(quitText.getPosition().x - 200, quitText.getPosition().y);
                        backButton.setPosition(backButton.getPosition().x - 200, backButton.getPosition().y + 25);
                        backText.setPosition(backText.getPosition().x - 200, backText.getPosition().y + 25);
                        /* Color */
                        usernameBox.setFillColor(sf::Color{0, 0, 0, 0});
                        serverButton.setFillColor(sf::Color{0, 0, 0, 0});
                        serverText.setFillColor(sf::Color{0, 0, 0, 0});
                        joinButton.setFillColor(sf::Color{0, 0, 0, 0});
                        joinText.setFillColor(sf::Color{0, 0, 0, 0});
                        usernameBox.setFillColor(sf::Color::White);
                        usernameText.setFillColor(sf::Color::White);
                        ipAddressBox.setFillColor(sf::Color::White);
                        ipAddressText.setFillColor(sf::Color::White);
                        connectButton.setFillColor(sf::Color::Black);
                        connectText.setFillColor(sf::Color::White);
                        drawInputText.setFillColor(sf::Color::Red);
                        secondLayer = true;
                    }
                    else if (connectButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer && secondLayer &&inputMainMenu.size() == 2)
                    {
                        // int d1, d2, d3, d4;
                        // id = usernameAndIp[0];
                        // sscanf(usernameAndIp[1].c_str(), "%d.%d.%d.%d", &d1, &d2, &d3, &d4);
                        // // std::cout << d1 << d2 << d3 << d4 << std::endl;
                        // // std::cout << usernameAndIp[1] << std::endl;
                        // joinServer(d1, d2, d3, d4);
                        connectionType = 'c';
                        mainWindow.close();
                        game.setVisible(true);
                    }
                    else if (connectButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer && secondLayer &&inputMainMenu.size() < 2)
                    {
                        guideText1.setFillColor(sf::Color::Red);
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    sf::Text inputMainMenuText(inputText, font, 30);
                    inputMainMenuText.setString(inputText);
                    inputMainMenuText.setFillColor(sf::Color::Red);
                    inputMainMenu.push_back(inputMainMenuText);
                    usernameAndIp.push_back(inputText);
                    inputText = "";
                }
            }

            if (event.type == sf::Event::TextEntered && secondLayer && inputMainMenu.size() < 2)
            {
                if (int(event.text.unicode) != 8) inputText += event.text.unicode;
                else if (int(event.text.unicode) == 8 && inputText.size() > 0) inputText.pop_back();
            }
            // std::cout << inputText << std::endl;
        }

        /* Render */
        mainWindow.clear();

        /* Render First Layer */
        mainWindow.draw(title);
        mainWindow.draw(playButton);
        mainWindow.draw(playText);
        mainWindow.draw(quitButton);
        mainWindow.draw(quitText);

        /* Render Second Layer */
        mainWindow.draw(serverButton);
        mainWindow.draw(serverText);
        mainWindow.draw(joinButton);
        mainWindow.draw(joinText);
        mainWindow.draw(backButton);
        mainWindow.draw(backText);

        /* Render Third Layer */
        mainWindow.draw(usernameBox);
        mainWindow.draw(usernameText);
        mainWindow.draw(ipAddressBox);
        mainWindow.draw(ipAddressText);
        mainWindow.draw(connectButton);
        mainWindow.draw(connectText);
        mainWindow.draw(guideText1);

        /* Render Input */
        int dummyX = 0;
        for (dummyX; dummyX < inputMainMenu.size(); dummyX++)
        {
            if (dummyX == 0)
            {
                inputMainMenu[dummyX].setPosition(usernameBox.getPosition().x + usernameBox.getSize().x / 2 - inputMainMenu[dummyX].getGlobalBounds().width / 2, usernameBox.getPosition().y + usernameBox.getSize().y / 2 - inputMainMenu[dummyX].getGlobalBounds().height / 2);
            }
            else
            {
                inputMainMenu[dummyX].setPosition(ipAddressBox.getPosition().x + ipAddressBox.getSize().x / 2 - inputMainMenu[dummyX].getGlobalBounds().width / 2, ipAddressBox.getPosition().y + ipAddressBox.getSize().y / 2 - inputMainMenu[dummyX].getGlobalBounds().height / 2);
            }
            mainWindow.draw(inputMainMenu[dummyX]);
        }

        drawInputText.setString(inputText);
        if (dummyX == 0)
        {
            drawInputText.setPosition(usernameBox.getPosition().x + usernameBox.getSize().x / 2 - drawInputText.getGlobalBounds().width / 2, usernameBox.getPosition().y + usernameBox.getSize().y / 2 - drawInputText.getGlobalBounds().height / 2);
        }
        else
        {
            drawInputText.setPosition(ipAddressBox.getPosition().x + ipAddressBox.getSize().x / 2 - drawInputText.getGlobalBounds().width / 2, ipAddressBox.getPosition().y + ipAddressBox.getSize().y / 2 - drawInputText.getGlobalBounds().height / 2);
        }
        mainWindow.draw(drawInputText);
    
        mainWindow.display();
    }

    /* Network */
    int preTurn = masterBoard.whoTurn, preSelect, prePosition, preDead, preTurnCount;
    bool serverReset = false;
    if (connectionType == 's')
    {
        hostServer();
        game.setVisible(true);
    }
    else
    {
        int d1, d2, d3, d4;
        id = usernameAndIp[0];
        sscanf(usernameAndIp[1].c_str(), "%d.%d.%d.%d", &d1, &d2, &d3, &d4);
        // std::cout << d1 << d2 << d3 << d4 << std::endl;
        // std::cout << usernameAndIp[1] << std::endl;
        joinServer(d1, d2, d3, d4);
    }

    char buffer[1024];
    std::size_t received;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << buffer << std::endl;
    
    char connectedTo[64];
    char serverClient[32];
    sscanf(buffer,"%[^:]: %s",connectedTo,serverClient);
    int Pturn;
    std::string tServerClient(serverClient);
    if(tServerClient == "Server"  ) Pturn = 0;
    else Pturn = 1 ;
    // std::cout << Pturn;
    sendWhoTurn(masterBoard);

    /* Status */
    socket.setBlocking(false);
    srand(time(0));
    sf::RectangleShape Status(sf::Vector2f(moveRight, height));
    masterBoard.boardConfig();
    defaultBoardCheck(defaultBoard, fields * fields, count);
    masterBoard.whoTurn = rand()%2;
    int turnCount = 0;

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
    sf::RectangleShape isTurnScreen(sf::Vector2f(250, 50)); // 250 * 50
    sf::RectangleShape background(sf::Vector2f(width, height));
    sf::RectangleShape resultScreen(sf::Vector2f(width - 440 , 200)); // 1000 * 200
    sf::RectangleShape whoScreen(sf::Vector2f(Status.getGlobalBounds().width, 50));
    sf::RectangleShape roundScreen(sf::Vector2f(Status.getGlobalBounds().width, 50));

    /* Position */
    isTurnScreen.setPosition(Status.getSize().x * 2.5 / 4 - isTurnScreen.getSize().x / 2, 650); // 700
    resultScreen.setPosition(game.getSize().x / 2 - resultScreen.getSize().x / 2, game.getSize().y / 2 - resultScreen.getSize().y / 2);
    background.setPosition(sf::Vector2f(0.0f, 0.0f));
    whoScreen.setPosition(sf::Vector2f(0.0f, 0.0f));
    roundScreen.setPosition(sf::Vector2f(0.0f, 100.0f));

    /* Color */
    isTurnScreen.setFillColor(sf::Color{7, 242, 129, 255});
    whoScreen.setFillColor(sf::Color{7, 242, 129, 255});
    roundScreen.setFillColor(sf::Color{7, 242, 129, 255});
    resultScreen.setFillColor(sf::Color{0, 0, 0, 0});
    background.setFillColor(sf::Color{0, 0, 0, 0});
    

    /* Text */
    sf::Text isTurnText("Turn Test", font, 30);
    sf::Text resultText("result Test", font, 200);
    sf::Text whoText("You are Test", font, 30);
    sf::Text roundText("Round : Test ", font, 30);
    resultText.setFillColor(sf::Color{0, 0, 0, 0});
    isTurnText.setFillColor(sf::Color{0, 0, 0, 0});
    whoText.setFillColor(sf::Color::Black);
    whoText.setPosition(whoScreen.getPosition().x + whoScreen.getSize().x / 2 - whoText.getGlobalBounds().width / 2, whoScreen.getPosition().y + whoScreen.getSize().y / 2 - whoText.getGlobalBounds().height);
    if(Pturn == 0) whoText.setString("You are White");
    else whoText.setString("You are Black");
    roundText.setFillColor(sf::Color::Black);
    roundText.setPosition(roundScreen.getPosition().x + roundScreen.getSize().x / 2 - roundText.getGlobalBounds().width / 2, roundScreen.getPosition().y + roundScreen.getSize().y / 2 - roundText.getGlobalBounds().height);
    
    std::vector<int> deadStack;
    while (game.isOpen())
    {
        countE = 0;
        sf::Event event;
        sf::Vector2f mouse = game.mapPixelToCoords(sf::Mouse::getPosition(game));
        // std::cout << turnCount << std::endl;
        roundText.setString("Round : " + std::to_string(turnCount));

        /* Check */
        checkWin(resultScreen, background, resultText, resetButton, resetText, masterBoard, enemy, defaultBoard, count);

        /* Send Data */
        if (preTurn != masterBoard.whoTurn)
        {
            sendWhoTurn(masterBoard);
            preTurn = masterBoard.whoTurn;
            // std::cout << preTurn << std::endl;
        }
        if (((preSelect != select) || (prePosition != enemy[select].position)) && (select != -1))
        {
            sendMove(select, enemy[select].position);
            preSelect = select;
            prePosition = enemy[select].position;
            // std::cout << select << " " << enemy[select].position << std::endl;
            // std::cout << preSelect << " " << prePosition << std::endl;
        }
        if(preTurnCount != turnCount)
        {
            sendTurnCount(turnCount);
            preTurnCount = turnCount;
        }
        for (int i = 0; i < count; i++)
        {
            if (enemy[i].isDead)
            {
                if (std::count(deadStack.begin(), deadStack.end(), i) < 1)
                {
                    deadStack.push_back(i);
                }
                // std::cout << std::count(deadStack.begin(), deadStack.end(), i)  << std::endl;
                // sendDead(i);
                if (preDead != deadStack.size())
                {
                    sendDead(i);
                    // std::cout << i << " " << deadStack.size() << " " << preDead << std::endl;
                    preDead = deadStack.size();
                }
            }
        }

        // std::cout << masterBoard.isEnd << std::endl;
        /* Game Event */
        while (game.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game.close();
            }

                            //std::cout << serverReset << std::endl;
            /* Reset Button */
            if (masterBoard.isEnd)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if ((resetButton.getGlobalBounds().contains(mouse)) || (serverReset))
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
                                    
                                    /* Server */
                                    turnCount = 0 ;
                                    serverReset = false;
                                    sendReset();
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
                    if (masterBoard.whoTurn == 0 && enemy[i].moveType > 0)
                    {
                        if(Pturn == masterBoard.whoTurn) movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count,turnCount);
                        isTurnText.setString("White's Turn");
                        isTurnText.setFillColor(sf::Color::Black);
                        isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                    }
                    else if (masterBoard.whoTurn == 1 && enemy[i].moveType < 0)
                    {
                        if(Pturn == masterBoard.whoTurn) movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count,turnCount);
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
                        if (masterBoard.whoTurn == 0 && enemy[i].moveType > 0)
                        {
                            if(Pturn == masterBoard.whoTurn) movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count,turnCount);
                            isTurnText.setString("White's Turn");
                            isTurnText.setFillColor(sf::Color::Black);
                            isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                        }
                        else if (masterBoard.whoTurn == 1 && enemy[i].moveType < 0)
                        {
                            if(Pturn == masterBoard.whoTurn)movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count,turnCount);
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
        


        /* Client Receive*/
        sf::Packet packet;
        socket.receive(packet);

        int tempInt1, tempInt2;
        std::string tempText;
        if(packet >> tempText >> tempInt1 >> tempInt2)
        {
            // std::cout << tempText << " " << tempInt1 << " " << tempInt2 << std::endl;
            if (tempText == "Who")
            {
                // std::cout << tempInt << " " << masterBoard.whoTurn << std::endl;
                masterBoard.whoTurn = tempInt1;
                preTurn = tempInt1;
            }
            if (tempText == "Move")
            {
                int temp = 0;
                select = tempInt1;
                defaultBoard[enemy[select].position] = temp;
                defaultBoard[tempInt2] = enemy[select].moveType;
                enemy[select].position = tempInt2;
                enemy[select].entity.setPosition(masterBoard.boardPositions[tempInt2]);
                preSelect = tempInt1;
                prePosition = tempInt2;
                // std::cout << select << " " << enemy[select].position << std::endl;
            }
            if (tempText == "Dead")
            {
                // std::cout << tempText << " " << tempInt1 << " " << tempInt2 << std::endl;
                enemy[tempInt1].isDead = true;
                enemy[tempInt1].entity.setPosition(-100, -100);
            }
            if (tempText == "Reset")
            {
                // std::cout << tempText << std::endl; 
                serverReset = true;
            }
            if (tempText == "turnCount")
            {
                turnCount = tempInt1;
                std::cout << tempInt1 << " " << turnCount << std::endl ;
            }
        }
        // std::cout << masterBoard.whoTurn << " " << tempInt << std::endl;

        // showDefualtBoard(defaultBoard);

        /* Render Screen */
        game.clear();

        /* Render Game */
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
        game.draw(roundScreen);
        game.draw(roundText);
        game.draw(whoScreen);
        game.draw(whoText);
        game.draw(resultScreen);
        game.draw(resultText);
        game.draw(resetButton);
        game.draw(resetText);
        // game.draw(boundingBoxShape);
        game.display();
    }

    return 0;
}