#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iomanip>
#include <sstream>
#include "GlobalDefinitions.h"
/**
 * @brief Class responsible for displaying everything that happens during the game,
 * including the chessboard, pieces, capturing user moves, saving and remembering past moves.
 * It handles functionalities such as saving the game to a notebook, updating
 * different piece positions, and managing the game state.
 */
class Chessboard{
        enum NumberOfButtons
        {
            gameOverMenuButtons = 4,
            promotionMenuButtons = 4,
            gameMenuButtons = 4
        };
        enum Pieces{
            no,
            pawn,
            knight,
            bishop,
            rook,
            queen,
            king
        };
        bool color;
        bool notationSaved = false;
public: bool menuButtonPressed = false;

private:float boardSize;
        float marginSize;
        float squareSize;
        float squareScale;
        float promotionMenuButtonScale;
        float menuButtonsScaleX;
        float menuButtonsScaleY;
        float arrowButtonScale;
        float menuButtonScaleX;
        float menuButtonScaleY;
        float notationHeight;
        float notationWidth;

        int showingPositionNumber;

        sf::Texture backgroundTexture;
        sf::Sprite  background;
        sf::Texture boardTexture;
        sf::Sprite  board;
        sf::Texture redUnderlightTexture;
        sf::Sprite  redUnderlight;
        sf::Texture blueUnderlightTexture;
        sf::Sprite  blueUnderlight;
        sf::Texture pieceTextures[12];
        sf::Sprite  piece;
        sf::Texture arrowButtonTextures[4];
        sf::Sprite  arrowButton[4];
        sf::Texture menuButtonTexture;
        sf::Sprite  menuButton;

        sf::Font normalFont;
        sf::Text normalText;
        sf::Font boldFont;
        sf::Text boldText;

        sf::RectangleShape notationBackground;

        std::vector<globalType::chessboardUnderlightPointer> underlights;
public: std::vector<std::string> notation;
        std::vector<globalType::chessboardPointer>positions;
    //******************************************************************************************************
        Chessboard(bool k = true);
private:    void loadFonts();
            void setNotationParameters();
            void loadTextures();
                void loadBackgroundTexture();
                void loadBoardTexture();
                void loadPieceTextures();
                void loadUnderlightTextures();
                void loadButtonsTextures();
            globalType::chessboardPointer loadPiecesArrangement();
            globalType::chessboardPointer reversePiecesArrangement(globalType::chessboardPointer chessboard);
public: ~Chessboard();
            void deletePositions();
            void deleteUnderlights();
        int getUserAction(int positionNumber = 0);
            void updateButtons();
            int  getMousePressActionCode();
                int  getPressedSquareCoords();
        void drawChessboard(bool underlightedCursor = false, int positionNumber = 0/*current position*/);
            void drawUnderlight();
            void underlightCursorSquare();
            void drawPieces();
            void drawNotation();
                void drawNotationContent();
        void updateSquare  (int squareCoordX, int squareCoordY, int piece, bool pieceColor, bool underlight);
            void updateChessboard(int squareCoordX, int squareCoordY, int piece, bool pieceColor);
            void updateUnderlightArray(int squareCoordX, int squareCoordY, bool underlight);
        void offUnderlights();
        void underlight(int coordonates);
        void checkWindowSize();
        void savePosition();
            globalType::chessboardPointer copyChessboard(const globalType::chessboardPointer oryginal);
            globalType::chessboardUnderlightPointer copyChessboardUnderlight(const globalType::chessboardUnderlightPointer oryginal);
        void saveGameInNotebook();
public: bool displayPastMovements(int NumberOfMove, bool afterGame);
};
#endif//CHESSBOARD_H

