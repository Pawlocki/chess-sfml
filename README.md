C++ Chess Game (SFML)

A two-player chess game written in C++17 with a graphical interface built using SFML 3. Players select pieces and make moves by clicking squares on a fullscreen chessboard. The selected square is highlighted, and illegal moves are rejected.

The game implements standard piece movement, captures, and turn management, including checks that prevent players from leaving their own king in check. It supports castling, en passant, pawn promotion to a queen, check, checkmate, and stalemate. The current game status is displayed in the window title and terminal.

The project separates chess rules and board state from game management and graphical rendering, using object-oriented C++ classes.

Running the project

Requires a C++17-compatible compiler and SFML 3 (Graphics, Window, and System). From the project folder, compile with:

g++ -std=c++17 main.cpp game/Board.cpp game/Game.cpp gui/sfml.cpp -o main.exe -lsfml-graphics -lsfml-window -lsfml-system

Run main.exe from the project folder so the program can load the textures in assets/.