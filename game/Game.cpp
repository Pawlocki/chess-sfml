#include "Game.hpp"

Board &Game::getBoard()
{
    return board;
}
void Game::finishSuccessfulMove()
{
    if (board.getCurrentPlayer() == 0)
    {
        board.clearLastPawnPushTableBlack();
        board.changeTurn();
    }
    else
    {
        board.clearLastPawnPushTableWhite();
        board.changeTurn();
        moveNumber++;
    }
}
void Game::updateGameStatus()
{
    if (board.isCheckMate() == true)
    {
        if (board.getCurrentPlayer() == 0)
            gameStatusText = "Checkmate. BLACK wins.";
        else
            gameStatusText = "Checkmate. WHITE wins.";

        isGameFinished = true;
    }
    else if (board.isStaleMate() == true)
    {
        gameStatusText = "Stalemate. The game is a draw.";
        isGameFinished = true;
    }
    else if (board.isSquareAttacked(board.findKingPosition()) == true)
    {
        gameStatusText = board.getCurrentPlayerName() + " is in check.";
    }
    else
    {
        gameStatusText = board.getCurrentPlayerName() + " to move.";
    }
}
bool Game::makeGuiMove(int fromRow, int fromColumn, int toRow, int toColumn, string promotionPiece)
{
    if (isGameFinished == true)
        return false;

    string fromSquare = board.convertPositionToSquare(fromRow, fromColumn);
    string toSquare = board.convertPositionToSquare(toRow, toColumn);

    if (board.isOccupiedByOwnPiece(fromSquare) == false)
        return false;

    if (board.isOccupiedByOwnPiece(toSquare) == true)
        return false;

    MoveResult moveResult = board.tryMovePiece(fromSquare, toSquare, true, promotionPiece);

    if (moveResult.wasMoveDone == false)
        return false;

    finishSuccessfulMove();
    updateGameStatus();

    return true;
}
bool Game::getIsGameFinished()
{
    return isGameFinished;
}
int Game::getMoveNumber()
{
    return moveNumber;
}
string Game::getGameStatusText()
{
    return gameStatusText;
}
