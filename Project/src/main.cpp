/* SFML */
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

/* C++ */
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

/* Include */
#include "include/board.cpp"
#include "include/spawnEntity.cpp"
#include "include/movement.cpp"

/* Variable of display */
const int width = 800, height = 600;
const int fields = 8;
const int tileSize = height / fields;
const int moveRight = width - height;

/* Board */
sf::RectangleShape boardChess[fields * fields];
sf::Vector2f boardPositions[fields * fields];

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

sf::Texture textureE[sizeof(pathE)/sizeof(pathE[0])];
sf::Texture textureP[sizeof(pathP)/sizeof(pathP[0])];

int main()
{
    /* Load Textures */
    loadTextures(textureP, pathP, sizeof(pathP)/sizeof(pathP[0]));
    loadTextures(textureE, pathE, sizeof(pathE)/sizeof(pathE[0]));

    /* Status */
    sf::Sprite spriteP[4];
    sf::RectangleShape Status(sf::Vector2f(moveRight, height));
    playerConfig(textureP, spriteP, Status, sizeof(pathP)/sizeof(pathP[0]));
    board(fields, tileSize, moveRight, boardPositions, boardChess);
    spriteP[0].setTextureRect(sf::IntRect(700, 0, 700, 1000));

    /* Entity on game */
    defaultBoardCheck(defaultBoard, sizeof(defaultBoard)/sizeof(defaultBoard[0]), count);
    sf::Sprite spriteE[count];
    entityConfig(defaultBoard, textureE, spriteE, boardPositions, fields * fields);
    // spriteE[0].setPosition(boardPositions[0]);

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
    if (!font.loadFromFile("font/arial.ttf"))
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
        while (game.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) game.close();
        }

        /* Draw */
        game.clear();
        game.draw(Status);
        game.draw(spriteP[0]);
        for (int i = 0; i < fields * fields; i++)
        {
            game.draw(boardChess[i]);
        }
        for (int i = 0; i < sizeof(spriteE)/sizeof(spriteE[0]); i++)
        {
            game.draw(spriteE[i]);
        }
        // game.draw(boundingBoxShape);
        game.display();
    }

    return 0;
}
