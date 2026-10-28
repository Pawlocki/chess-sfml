#pragma once

#include "Board.hpp"

class Game
{
private:
    Board board;

    int moveNumber = 1;
    bool isGameFinished = false;
    string gameStatusText = "WHITE to move.";

public:
    Board &getBoard();

    void finishSuccessfulMove();
    void updateGameStatus();
    bool makeGuiMove(int fromRow, int fromColumn, int toRow, int toColumn, string promotionPiece = "Q");

    bool getIsGameFinished();
    int getMoveNumber();
    string getGameStatusText();
};
