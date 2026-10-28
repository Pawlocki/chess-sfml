#pragma once

#include <SFML/Graphics.hpp>
#include "BoardLayout.hpp"

struct Piece
{
    sf::Sprite sprite;

    int row;
    int column;

    char type;
    bool isBlack;

    Piece(const sf::Texture &texture, int startRow, int startCol, char pieceType, bool black, float pieceScale) : sprite(texture)
    {
        row = startRow;
        column = startCol;
        type = pieceType;
        isBlack = black;

        sprite.setScale({pieceScale, pieceScale});
    }

    void updateScreenPosition(const BoardLayout &layout)
    {
        sprite.setPosition({layout.playAreaX + column * layout.squareSize + layout.pieceOffset + layout.pieceShiftX,
                            layout.playAreaY + row * layout.squareSize + layout.pieceOffset + layout.pieceShiftY});
    }
};