/* Include */
#include "../include/board.h"
#include "../include/unitConfig.h"
#include "../include/movement.h"

/* Board */
Board masterBoard;

/* Entity */
/* In Future, it must change */
// int defaultBoard[fields * fields] =
// {
//     -1, -2, -3, -4, -5, -3, -2, -1,
//     -6, -6, -6, -6, -6, -6, -6, -6,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0,
//     6, 6, 6, 6, 6, 6, 6, 6,
//     1, 2, 3, 5, 4, 3, 2, 1
// };
/* Sandbox */
int defaultBoard[fields * fields] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};
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
    sf::RectangleShape Status(sf::Vector2f(moveRight, height));
    masterBoard.boardConfig();
    defaultBoardCheck(defaultBoard, fields * fields, count);

    /* Unit */
    Unit player[4], enemy[count];
    int unitChess[count];
    int countE = 0, select = 0;
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
    // sf::FloatRect boundingBox = spriteE[0].getGlobalBounds();
    // sf::RectangleShape boundingBoxShape(sf::Vector2f(boundingBox.width, boundingBox.height));
    // boundingBoxShape.setPosition(boundingBox.left, boundingBox.top);
    // boundingBoxShape.setFillColor(sf::Color::Transparent);
    // boundingBoxShape.setOutlineColor(sf::Color::Red);
    // boundingBoxShape.setOutlineThickness(1.f);

    /* Reander Main Window */
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

    /* Button */
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
                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        mainWindow.close();
                        game.setVisible(true);
                    }
                    else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        mainWindow.close();
                        game.close();
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
        mainWindow.display();
    }

    /* Reander Game */
    game.setActive(true);
    while (game.isOpen())
    {
        sf::Event event;
        sf::Vector2f mouse = game.mapPixelToCoords(sf::Mouse::getPosition(game));
        while (game.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) game.close();
            // showDefualtBoard(defaultBoard);
            /* Movement */
            for (int i = 0; i < count; i++)
            {
                movement(masterBoard, enemy[i], event, mouse, defaultBoard);
                if (enemy[i].isMove && !enemy[select].isMove) 
                {
                    select = i;
                }
                else if (enemy[i].isMove && enemy[select].isMove && i != select)
                {
                    enemy[select].isMove = false;
                }
                masterBoard.boardHighlight(defaultBoard, enemy[select].moveType, enemy[select].position, enemy[select].isMove, enemy[select].firstMove);
            }
        }

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
        // game.draw(boundingBoxShape);
        game.display();
    }

    return 0;
}

