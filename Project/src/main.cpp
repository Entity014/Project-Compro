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
    "asset/texture/New/black_rook.png", "asset/texture/New/black_horse.png", "asset/texture/New/black_bishop.png", "asset/texture/New/black_queen.png", "asset/texture/New/black_king.png", "asset/texture/New/black_pond.png",
    "asset/texture/New/white_rook.png", "asset/texture/New/white_horse.png", "asset/texture/New/white_bishop.png", "asset/texture/New/white_queen.png", "asset/texture/New/white_king.png", "asset/texture/New/white_pond.png"
};
std::string pathP[] =
{
    "asset/texture/New/test.png"
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

    /*UI*/
    sf::Texture Play;
    Play.loadFromFile("asset/UI/play.png");
    sf::Texture Back;
    Back.loadFromFile("asset/UI/back.png");
    sf::Texture Quit;
    Quit.loadFromFile("asset/UI/quit.png");
    sf::Texture host;
    host.loadFromFile("asset/UI/host.png");
    sf::Texture join;
    join.loadFromFile("asset/UI/join.png");
    sf::Texture connect;
    connect.loadFromFile("asset/UI/connect.png");

    sf::Texture Chess;
    Chess.loadFromFile("asset/UI/chess mea.png");
    sf::Sprite chess(Chess);
    chess.setPosition(mainWindow.getSize().x / 2 - chess.getGlobalBounds().width / 2, 80);

    sf::Texture BG2;
    BG2.loadFromFile("asset/UI/genshin1.png");
    sf::Sprite bg2(BG2);
    bg2.setPosition(mainWindow.getSize().x / 2 - chess.getGlobalBounds().width / 2 + 480, 50);

    sf::Texture BG3;
    BG3.loadFromFile("asset/UI/genshin2.png");
    sf::Sprite bg3(BG3);
    bg3.setPosition(mainWindow.getSize().x / 2 - chess.getGlobalBounds().width / 2 - 450, 50);

    sf::Texture BG4;
    BG4.loadFromFile("asset/UI/genshin3.png");
    sf::Sprite bg4(BG4);
    bg4.setPosition(950, 370);

    sf::Texture BG1;
    BG1.loadFromFile("asset/UI/BG.png");
    sf::Sprite bg1(BG1);
    bg1.setPosition(0,480);


    /* Button Main Window */
    sf::Sprite backButton(Back);
    backButton.setPosition(mainWindow.getSize().x / 2 - backButton.getGlobalBounds().width / 2, 1000);

    /* First Layer */
    sf::Sprite playButton(Play);
    playButton.setPosition(mainWindow.getSize().x / 2 - playButton.getGlobalBounds().width / 2, 350);

    sf::Sprite quitButton(Quit);
    quitButton.setPosition(mainWindow.getSize().x / 2 - quitButton.getGlobalBounds().width / 2, 500);

    /* Second Layer */
    sf::Sprite serverButton(host);
    serverButton.setPosition(mainWindow.getSize().x / 2 - serverButton.getGlobalBounds().width / 2, 1000);

    sf::Sprite joinButton(join);
    joinButton.setPosition(mainWindow.getSize().x / 2 - joinButton.getGlobalBounds().width / 2, 1000);

    /* Third Layer */
    sf::Sprite connectButton(connect);
    connectButton.setPosition(mainWindow.getSize().x / 2 - connectButton.getGlobalBounds().width / 2, 1000);


    sf::Text guideText1("Enter to comfirm", font, 30);
    guideText1.setFillColor(sf::Color{0, 0, 0, 0});
    guideText1.setPosition(mainWindow.getSize().x / 2 - guideText1.getGlobalBounds().width / 2, 550);
    sf::Text drawInputText(inputText, font, 30);

    sf::RectangleShape usernameBox(sf::Vector2f(300,50));
    usernameBox.setFillColor(sf::Color{0, 0, 0, 0});
    usernameBox.setPosition(mainWindow.getSize().x * 1.15 / 2 - usernameBox.getSize().x / 2, 250);
    sf::Text usernameText("Username :", font, 30);
    usernameText.setFillColor(sf::Color{0, 0, 0, 0});
    usernameText.setPosition(mainWindow.getSize().x / 2.8 - usernameText.getGlobalBounds().width / 2, 250);
    
    sf::RectangleShape ipAddressBox(sf::Vector2f(300,50));
    ipAddressBox.setFillColor(sf::Color{0, 0, 0, 0});
    ipAddressBox.setPosition(mainWindow.getSize().x * 1.15 / 2 - ipAddressBox.getSize().x / 2, 350);
    sf::Text ipAddressText("Ip Address :", font, 30);
    ipAddressText.setFillColor(sf::Color{0, 0, 0, 0});
    ipAddressText.setPosition(mainWindow.getSize().x / 2.8 - ipAddressText.getGlobalBounds().width / 2, 350);

    /* Sound */
    sf::SoundBuffer firstBuffer;
    firstBuffer.loadFromFile("asset/sound/Chess_Mae.wav");
    sf::Sound firstOpen;
    firstOpen.setBuffer(firstBuffer);
    firstOpen.play();

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
                        /* Color */
                        
                        playButton.setPosition(-1000, -1000);
                        quitButton.setPosition(-1000, -1000);
                        connectButton.setPosition(-1000,-1000);
                        serverButton.setPosition(mainWindow.getSize().x / 2 - serverButton.getGlobalBounds().width / 2, 350);
                        joinButton.setPosition(mainWindow.getSize().x / 2 - joinButton.getGlobalBounds().width / 2, 450);
                        backButton.setPosition(mainWindow.getSize().x / 2 - backButton.getGlobalBounds().width / 2, 550);
                        //serverButton.setFillColor(sf::Color::Black);
                        //serverText.setFillColor(sf::Color::White);
                        //joinButton.setFillColor(sf::Color::Black);
                        //joinText.setFillColor(sf::Color::White);
                        //backButton.setFillColor(sf::Color::Black);
                        //backText.setFillColor(sf::Color::White);
                        firstLayer = true;
                    }
                    else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && secondLayer)
                    {
                        inputText = "";
                        inputMainMenu.clear();

                        connectButton.setPosition(-1000,-1000);
                        serverButton.setPosition(mainWindow.getSize().x / 2 - serverButton.getGlobalBounds().width / 2, 350);
                        joinButton.setPosition(mainWindow.getSize().x / 2 - joinButton.getGlobalBounds().width / 2, 450);
                        backButton.setPosition(mainWindow.getSize().x / 2 - backButton.getGlobalBounds().width / 2, 550);
                        

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
                        secondLayer = false;
                    }
                    else if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer)
                    {
                        playButton.setPosition(mainWindow.getSize().x / 2 - playButton.getGlobalBounds().width / 2, 350);
                        quitButton.setPosition(mainWindow.getSize().x / 2 - quitButton.getGlobalBounds().width / 2, 500);
                        serverButton.setPosition(-1000,-1000);
                        backButton.setPosition(-1000,-1000);
                        joinButton.setPosition(-1000,-1000);
                        connectButton.setPosition(-1000,-1000);

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
                        //quitText.setPosition(quitText.getPosition().x - 200, quitText.getPosition().y);
                        backButton.setPosition(mainWindow.getSize().x / 1.97 - backButton.getGlobalBounds().width / 2, 550);
                        connectButton.setPosition(mainWindow.getSize().x / 2 - connectButton.getGlobalBounds().width / 2, 450);
                        //backText.setPosition(backText.getPosition().x - 200, backText.getPosition().y + 25);
                        /* Color */
                        usernameBox.setFillColor(sf::Color{0, 0, 0, 0});
                        //serverButton.setFillColor(sf::Color{0, 0, 0, 0});
                        //serverText.setFillColor(sf::Color{0, 0, 0, 0});
                        //joinButton.setFillColor(sf::Color{0, 0, 0, 0});
                        //joinText.setFillColor(sf::Color{0, 0, 0, 0});

                        serverButton.setPosition(-1000,-1000);
                        joinButton.setPosition(-1000,-1000);

                        usernameBox.setFillColor(sf::Color::White);
                        usernameText.setFillColor(sf::Color::White);
                        ipAddressBox.setFillColor(sf::Color::White);
                        ipAddressText.setFillColor(sf::Color::White);
                        //connectButton.setFillColor(sf::Color::Black);
                        //connectText.setFillColor(sf::Color::White);
                        drawInputText.setFillColor(sf::Color::Red);
                        secondLayer = true;
                    }
                    else if (connectButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && firstLayer && secondLayer &&inputMainMenu.size() == 2)
                    {
                        // int d1, d2, d3, d4;
                        // id = usernameAndIp[0];
                        // sscanf(usernameAndIp[1].c_str(), "%d.%d.%d.%d", &d1, &d2, &d3, &d4);
                        // std::cout << d1 << d2 << d3 << d4 << std::endl;
                        // std::cout << usernameAndIp[1] << std::endl;
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
        mainWindow.draw(chess);
        mainWindow.draw(bg1);
        mainWindow.draw(bg2);
        mainWindow.draw(bg3);
        mainWindow.draw(bg4);
        mainWindow.draw(quitButton);
        mainWindow.draw(playButton);

        //mainWindow.draw(quitText);

        /* Render Second Layer */
        mainWindow.draw(serverButton);
        //mainWindow.draw(serverText);
        mainWindow.draw(joinButton);
        //mainWindow.draw(joinText);
        mainWindow.draw(backButton);
        //mainWindow.draw(backText);

        /* Render Third Layer */
        mainWindow.draw(usernameBox);
        mainWindow.draw(usernameText);
        mainWindow.draw(ipAddressBox);
        mainWindow.draw(ipAddressText);
        mainWindow.draw(connectButton);
        //mainWindow.draw(connectText);
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
    int preTurn = masterBoard.whoTurn, preSelect, prePosition, preDead ,preDeadW ,preDeadB ,preTurnCount;
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
    if(tServerClient == "Server")
    {
        Pturn = 0;
        game.setTitle("Chess Mae Server");
    }
    else
    {
        Pturn = 1 ;
        game.setTitle("Chess Mae Client");
    }
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
    if(Pturn == 0) whoText.setString("You are White Side");
    else whoText.setString("You are Black Side");
    roundText.setFillColor(sf::Color::Black);
    roundText.setPosition(roundScreen.getPosition().x + roundScreen.getSize().x / 2 - roundText.getGlobalBounds().width / 2, roundScreen.getPosition().y + roundScreen.getSize().y / 2 - roundText.getGlobalBounds().height);
    
    std::vector<int> deadStack;
    std::vector<int> deadStackW;
    std::vector<int> deadStackB;

    /* Sound and Music */
    std::vector<sf::Sound> soundVector;
    std::vector<sf::SoundBuffer> soundBufferVector;
    std::vector<std::string> pathMusic = {"asset/music/PVZ.ogg", "asset/music/MC.ogg", "asset/music/RickRoll.ogg"} ;
    std::vector<std::string> pathSound = {"asset/sound/wanjeab.wav", "asset/sound/Dead.wav", "asset/sound/Lose.wav", "asset/sound/win.wav"} ;
    sf::Music music1, music2, music3;
    bool musicPlaying1 = false, musicPlaying2 = false, musicPlaying3 = false;
    bool soundEndPlaying1 = false, soundEndPlaying2 = false;

    music1.openFromFile(pathMusic[0]);
    music2.openFromFile(pathMusic[1]);
    music3.openFromFile(pathMusic[2]);
    music1.setVolume(10.0f);
    music2.setVolume(10.0f);
    music3.setVolume(10.0f);

    loadSound(soundVector, soundBufferVector, pathSound);
    // std::cout << soundBufferVector.size() << " " << soundVector.size() << std::endl;
    if (!musicPlaying1)
    {
        music1.play();
        music1.setLoop(true);
        music2.stop();
        music3.stop();
        musicPlaying1 = true;
    }
    while (game.isOpen())
    {
        // std::cout << Pturn << " " << masterBoard.whoLose << " " << soundEndPlaying1 << " " << soundEndPlaying2 << std::endl;
        // std::cout << deadStackBlack.size() << " " << deadStackWhite.size() << std::endl;
        // std::cout << " P1: " << musicPlaying1 << "P2: " << musicPlaying2 << "P3: " << musicPlaying3 << std::endl;
        // std::cout << masterBoard.isEnd << std::endl;
        countE = 0;
        sf::Event event;
        sf::Vector2f mouse = game.mapPixelToCoords(sf::Mouse::getPosition(game));
        // std::cout << turnCount << std::endl;
        roundText.setString("Round : " + std::to_string(turnCount));

        /* Logic Music */
        for (int i = 0; i < count; i++)
        {
            if (enemy[i].firstMove && ((enemy[i].moveType == -4) || (enemy[i].moveType == 4)))
            {
                if (!musicPlaying2)
                {
                    music1.stop();
                    music2.play();
                    music2.setLoop(true);
                    music3.stop();
                    musicPlaying2 = true;
                }
            }
        }
        if(masterBoard.isEnd)
        {
            /* Sound */
            if (masterBoard.whoLose == 0)
            {
                if (Pturn == 0 && !soundEndPlaying1)
                {
                    soundVector[2].play();
                }
                else if (Pturn == 1 && !soundEndPlaying2)
                {
                    soundVector[3].play();
                }
            }
            if (masterBoard.whoLose == 1)
            {
                if (Pturn == 1 && !soundEndPlaying1)
                {
                    soundVector[2].play();
                    soundEndPlaying1 = true;
                }
                else if (Pturn == 0 && !soundEndPlaying2)
                {
                    soundVector[3].play();
                    soundEndPlaying2 = true;
                }
            }
            /* Music */
            if (!musicPlaying3 && (soundEndPlaying1 || soundEndPlaying2))
            {
                music1.stop();
                music2.stop();
                music3.play();
                music3.setLoop(true);
                musicPlaying3 = true;
            }
        }

        /* Check */
        checkWin(resultScreen, background, resultText, resetButton, resetText, masterBoard, enemy, defaultBoard, count, Pturn);

        //std::cout << deadStackB.size() << " " << deadStackW.size() << std::endl ;
        //std::cout << Pturn << " " << masterBoard.whoTurn << std::endl ;
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
            // std::cout << i << " " << enemy[i].moveType << std::endl;
            if (enemy[i].isDead)
            {
                if (std::count(deadStack.begin(), deadStack.end(), i) < 1)
                {
                    deadStack.push_back(i);
                    if(enemy[i].moveType < 0)
                    {
                        deadStackB.push_back(i);
                    }
                    else deadStackW.push_back(i);
                }
                // std::cout << std::count(deadStack.begin(), deadStack.end(), i)  << std::endl;
                // sendDead(i);
                if (preDead != deadStack.size())
                {
                    sendDead(i);
                    // std::cout << i << " " << deadStack.size() << " " << preDead << std::endl;
                    preDead = deadStack.size();
                    //soundVector[0].play();

                }

                if(preDeadB != deadStackB.size())
                {
                    preDeadB = deadStackB.size();
                    if(preDeadB > 0 && enemy[i].moveType != -5)
                    {
                        if(Pturn == 0) soundVector[0].play();
                        else soundVector[1].play();
                    }
                    
                }

                if(preDeadW != deadStackW.size())
                {
                    preDeadW = deadStackW.size();
                    if(preDeadW > 0 && enemy[i].moveType != 5)
                    {
                        if(Pturn == 1) soundVector[0].play();
                        else soundVector[1].play();
                    }
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
                                    deadStack.clear();
                                    deadStackB.clear();
                                    deadStackW.clear();
                                    countE++;

                                    /* Music */
                                    musicPlaying1 = false;
                                    if (!musicPlaying1)
                                    {
                                        music1.play();
                                        music1.setLoop(true);
                                        music2.stop();
                                        music3.stop();
                                        musicPlaying1 = true;
                                    }
                                    musicPlaying1 = false;
                                    musicPlaying2 = false;
                                    musicPlaying3 = false;
                                    soundEndPlaying1 = false;
                                    soundEndPlaying2 = false;
                                    
                                    /* Server */
                                    masterBoard.whoLose = -1;
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
            if (!masterBoard.isEnd)
            {
                for (int i = 0; i < count; i++)
                {   
                    if (!enemy[select].canAttack)
                    {
                        if (masterBoard.whoTurn == 0 && enemy[i].moveType > 0)
                        {
                            if(Pturn == masterBoard.whoTurn)
                            {
                                movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count, turnCount);
                                isTurnText.setString("Your Turn");
                            }
                            else isTurnText.setString("Opponent's Turn");
                            isTurnText.setFillColor(sf::Color::Black);
                            isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                        }
                        else if (masterBoard.whoTurn == 1 && enemy[i].moveType < 0)
                        {
                            if(Pturn == masterBoard.whoTurn)
                            {
                                movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count,turnCount);
                                isTurnText.setString("Your Turn");
                            }
                            else isTurnText.setString("Opponent's Turn");
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
                                if(Pturn == masterBoard.whoTurn)
                                {
                                    movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count,turnCount);
                                    isTurnText.setString("Your Turn");
                                }
                                else isTurnText.setString("Opponent's Turn");
                                isTurnText.setFillColor(sf::Color::Black);
                                isTurnText.setPosition(isTurnScreen.getPosition().x + isTurnScreen.getSize().x / 2 - isTurnText.getGlobalBounds().width / 2, isTurnScreen.getPosition().y + isTurnScreen.getSize().y / 2 - isTurnText.getGlobalBounds().height);
                            }
                            else if (masterBoard.whoTurn == 1 && enemy[i].moveType < 0)
                            {
                                if(Pturn == masterBoard.whoTurn)
                                {
                                    movement(masterBoard, enemy[i], enemy, event, mouse, defaultBoard, count,turnCount);
                                    isTurnText.setString("Your Turn");
                                }
                                else isTurnText.setString("Opponent's Turn");
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
                // std::cout << tempInt1 << " " << turnCount << std::endl ;
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
        game.draw(roundScreen);
        game.draw(roundText);
        game.draw(whoScreen);
        game.draw(whoText);
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