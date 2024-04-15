#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <iomanip>
#include <sstream>
#include "GlobalDefinitions.h"

/**
 * @brief
 */
class Chessboard{

public:////////////////////////////////


    enum NumberOfButtons
    {
        gameOverMenuButtons = 4,
        promotionMenuButtons = 4,
        gameMenuButtons = 4
    };
    bool color;
    bool menuButtonPressed = false;

    float boardSize;
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

/////////////////
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

    bool notationSaved = false;

    sf::RectangleShape notationBackground;

    std::vector<std::string> notation;
    std::vector<globalType::chessboardPointer>positions;
    std::vector<globalType::chessboardUnderlightPointer> underlights;
//******************************************************************************************************
    Chessboard(bool k = true);
        void loadFonts();
        void setNotationParameters();
        void loadTextures();
            void loadBackgroundTexture();
            void loadBoardTexture();
            void loadPieceTextures();
            void loadUnderlightTextures();
            void loadButtonsTextures();
        globalType::chessboardPointer loadPiecesArrangement();
        globalType::chessboardPointer reversePiecesArrangement(globalType::chessboardPointer chessboard);
    ~Chessboard();
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
    void displayPastMovements(int NumberOfMove, bool afterGame);
//******************************************************************************************************
    enum Pieces{
        no,
        pawn,
        knight,
        bishop,
        rook,
        queen,
        king
    };
};
#endif//CHESSBOARD_H
