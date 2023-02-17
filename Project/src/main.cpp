#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "include/board.cpp"
#include "include/spawnEntity.cpp"

/* Variable of display */
const int width = 800, height = 600;
const int fields = 8;
const int tileSize = height / fields;
const int moveRight = width - height;

/* Board */
sf::RectangleShape boardChess[fields * fields];

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

sf::Texture textureE[12];
sf::Texture textureP[1];

int main()
{
    /* Load Textures */
    loadTextures(textureP, pathP, sizeof(pathP)/sizeof(pathP[0]));
    loadTextures(textureE, pathE, sizeof(pathE)/sizeof(pathE[0]));

    /* Status */
    sf::Sprite sP1(textureP[0]);
    sP1.setScale(sf::Vector2f(0.25f, 0.25f));
    sP1.setPosition(sf::Vector2f(-175,350));

    /* Entity on game */
    defaultBoardCheck(defaultBoard, sizeof(defaultBoard)/sizeof(defaultBoard[0]), count);
    sf::Sprite spriteE[count];
    entityConfig(defaultBoard, textureE, spriteE, fields * fields);

    /* Reander window */
    sf::RenderWindow window(sf::VideoMode(width, height), "Chess Mae");
    board(fields, tileSize, moveRight, boardChess);
    sf::RectangleShape Status(sf::Vector2f(moveRight, height));

    /* Window Here */
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /* Draw */
        window.clear();
        window.draw(Status);
        window.draw(sP1);
        for (int i = 0; i < fields * fields; i++)
        {
            window.draw(boardChess[i]);
        }
        // window.draw(spriteE[0]);
        window.display();
    }

    return 0;
}
