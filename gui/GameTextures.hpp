#pragma once

#include <SFML/Graphics.hpp>

struct GameTextures
{
    sf::Texture boardTexture;

    sf::Texture whitePawnTexture;
    sf::Texture whiteKingTexture;
    sf::Texture whiteQueenTexture;
    sf::Texture whiteRookTexture;
    sf::Texture whiteBishopTexture;
    sf::Texture whiteKnightTexture;

    sf::Texture blackPawnTexture;
    sf::Texture blackKingTexture;
    sf::Texture blackQueenTexture;
    sf::Texture blackRookTexture;
    sf::Texture blackBishopTexture;
    sf::Texture blackKnightTexture;

    bool loadFiles()
    {
        if (!boardTexture.loadFromFile("assets/board/board.png"))
            return false;

        if (!whitePawnTexture.loadFromFile("assets/pieces/white_pawn.png"))
            return false;

        if (!whiteKingTexture.loadFromFile("assets/pieces/white_king.png"))
            return false;

        if (!whiteQueenTexture.loadFromFile("assets/pieces/white_queen.png"))
            return false;

        if (!whiteRookTexture.loadFromFile("assets/pieces/white_rook.png"))
            return false;

        if (!whiteBishopTexture.loadFromFile("assets/pieces/white_bishop.png"))
            return false;

        if (!whiteKnightTexture.loadFromFile("assets/pieces/white_knight.png"))
            return false;

        if (!blackPawnTexture.loadFromFile("assets/pieces/black_pawn.png"))
            return false;

        if (!blackKingTexture.loadFromFile("assets/pieces/black_king.png"))
            return false;

        if (!blackQueenTexture.loadFromFile("assets/pieces/black_queen.png"))
            return false;

        if (!blackRookTexture.loadFromFile("assets/pieces/black_rook.png"))
            return false;

        if (!blackBishopTexture.loadFromFile("assets/pieces/black_bishop.png"))
            return false;

        if (!blackKnightTexture.loadFromFile("assets/pieces/black_knight.png"))
            return false;

        return true;
    }
};