#include "sfml.hpp"
#include "BoardLayout.hpp"
#include "GameTextures.hpp"
#include "Piece.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <string>
#include <iostream>

using namespace std;

const sf::Texture &getTextureForPiece(string piece, GameTextures &textures)
{
    if (piece == "p")
        return textures.blackPawnTexture;
    else if (piece == "r")
        return textures.blackRookTexture;
    else if (piece == "n")
        return textures.blackKnightTexture;
    else if (piece == "b")
        return textures.blackBishopTexture;
    else if (piece == "q")
        return textures.blackQueenTexture;
    else if (piece == "k")
        return textures.blackKingTexture;
    else if (piece == "P")
        return textures.whitePawnTexture;
    else if (piece == "R")
        return textures.whiteRookTexture;
    else if (piece == "N")
        return textures.whiteKnightTexture;
    else if (piece == "B")
        return textures.whiteBishopTexture;
    else if (piece == "Q")
        return textures.whiteQueenTexture;
    else if (piece == "K")
        return textures.whiteKingTexture;

    return textures.whitePawnTexture;
}

vector<Piece> createPieces(Board &chessBoard, GameTextures &textures, const BoardLayout &layout)
{
    vector<Piece> pieces;

    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            string piece = chessBoard.getPiece(row, column);

            if (piece != ".")
            {
                bool isBlack = chessBoard.isBlackPiece(piece);
                pieces.push_back(Piece(getTextureForPiece(piece, textures), row, column, piece[0], isBlack, layout.pieceScale));
            }
        }
    }

    return pieces;
}

int startSfmlWindow(Game &game)
{
    Board &chessBoard = game.getBoard();

    GameTextures textures;

    if (!textures.loadFiles())
        return -1;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Chess - WHITE to move", sf::State::Fullscreen);

    sf::Sprite boardSprite(textures.boardTexture);

    BoardLayout layout = createBoardLayout(desktopMode, textures.boardTexture, textures.whitePawnTexture);

    boardSprite.setScale({layout.boardScale, layout.boardScale});
    boardSprite.setPosition({layout.boardX, layout.boardY});

    sf::RectangleShape selectedSquare({layout.squareSize, layout.squareSize});
    selectedSquare.setFillColor(sf::Color(0, 255, 0, 120));

    bool isPieceSelected = false;
    int selectedRow = -1;
    int selectedColumn = -1;

    vector<Piece> pieces = createPieces(chessBoard, textures, layout);

    cout << game.getGameStatusText() << endl;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            else if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(mouseButtonPressed->position);

                    int clickedRow;
                    int clickedColumn;

                    if (wasSquareClicked(mousePosition, layout, clickedRow, clickedColumn) == false)
                    {
                        isPieceSelected = false;
                    }
                    else if (game.getIsGameFinished() == false)
                    {
                        string clickedSquare = chessBoard.convertPositionToSquare(clickedRow, clickedColumn);

                        if (isPieceSelected == false)
                        {
                            if (chessBoard.isOccupiedByOwnPiece(clickedSquare) == true)
                            {
                                selectedRow = clickedRow;
                                selectedColumn = clickedColumn;
                                selectedSquare.setPosition({layout.playAreaX + selectedColumn * layout.squareSize,
                                                            layout.playAreaY + selectedRow * layout.squareSize});
                                isPieceSelected = true;
                            }
                        }
                        else
                        {
                            string selectedSquareName = chessBoard.convertPositionToSquare(selectedRow, selectedColumn);

                            if (clickedRow == selectedRow && clickedColumn == selectedColumn)
                            {
                                isPieceSelected = false;
                            }
                            else if (chessBoard.isOccupiedByOwnPiece(clickedSquare) == true)
                            {
                                selectedRow = clickedRow;
                                selectedColumn = clickedColumn;
                                selectedSquare.setPosition({layout.playAreaX + selectedColumn * layout.squareSize,
                                                            layout.playAreaY + selectedRow * layout.squareSize});
                            }
                            else
                            {
                                bool wasMoveDone = game.makeGuiMove(selectedRow, selectedColumn, clickedRow, clickedColumn, "Q");

                                if (wasMoveDone == true)
                                {
                                    pieces = createPieces(chessBoard, textures, layout);
                                    isPieceSelected = false;

                                    cout << selectedSquareName << " -> " << clickedSquare << endl;
                                    cout << game.getGameStatusText() << endl;

                                    window.setTitle("Chess - " + game.getGameStatusText());
                                }
                                else
                                {
                                    cout << "Invalid move." << endl;
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(boardSprite);

        if (isPieceSelected == true)
            window.draw(selectedSquare);

        for (Piece &piece : pieces)
        {
            piece.updateScreenPosition(layout);
            window.draw(piece.sprite);
        }

        window.display();
    }

    return 0;
}
