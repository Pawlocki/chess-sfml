#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>

using namespace std;

struct BoardLayout
{
    float boardSize;
    float boardMargin;
    float playAreaSize;
    float squareSize;
    float pieceSize;

    float boardScale;
    float pieceScale;

    float boardX;
    float boardY;

    float playAreaX;
    float playAreaY;

    float pieceOffset;

    float pieceShiftX;
    float pieceShiftY;
};

BoardLayout createBoardLayout(sf::VideoMode desktopMode, const sf::Texture &boardTexture, const sf::Texture &pieceTexture)
{
    BoardLayout layout;

    layout.boardSize = min(desktopMode.size.x, desktopMode.size.y) * 0.85f;

    layout.boardMargin = layout.boardSize * 0.073f;
    layout.playAreaSize = layout.boardSize - 2.f * layout.boardMargin;
    layout.squareSize = layout.playAreaSize / 8.f;
    layout.pieceSize = layout.squareSize * 0.85f;

    layout.boardScale = layout.boardSize / boardTexture.getSize().x;
    layout.pieceScale = layout.pieceSize / pieceTexture.getSize().x;

    layout.boardX = desktopMode.size.x / 2.f - layout.boardSize / 2.f;
    layout.boardY = desktopMode.size.y / 2.f - layout.boardSize / 2.f;

    layout.playAreaX = layout.boardX + layout.boardMargin;
    layout.playAreaY = layout.boardY + layout.boardMargin;

    layout.pieceOffset = (layout.squareSize - layout.pieceSize) / 2.f;

    layout.pieceShiftX = -2.f;
    layout.pieceShiftY = -8.f;

    return layout;
}

bool wasSquareClicked(sf::Vector2f mousePosition, const BoardLayout &layout, int &row, int &column)
{
    if (mousePosition.x < layout.playAreaX || mousePosition.y < layout.playAreaY)
        return false;
    else if (mousePosition.x >= layout.playAreaX + 8 * layout.squareSize || mousePosition.y >= layout.playAreaY + 8 * layout.squareSize)
        return false;
    else
    {
        column = static_cast<int>((mousePosition.x - layout.playAreaX) / layout.squareSize);
        row = static_cast<int>((mousePosition.y - layout.playAreaY) / layout.squareSize);
        return true;
    }
}