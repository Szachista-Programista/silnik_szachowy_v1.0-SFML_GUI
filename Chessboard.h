#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "GlobalDefinitions.h"

/**
 * @brief
 */
class Chessboard{

public:////////////////////////////////
    bool color;

    float windowHeight;
    float windowWidth;
    float boardSize;
    float marginSize;
    float squareSize;
    float squareScale;
    float buttonScale;
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

    sf::Font normalFont;
    sf::Text normalText;
    sf::Font boldFont;
    sf::Text boldText;

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
        globalType::chessboardPointer loadPiecesArrangement();
        globalType::chessboardPointer reversePiecesArrangement(globalType::chessboardPointer chessboard);
    ~Chessboard();
        void deletePositions();
        void deleteUnderlights();
    int loadCoordinates();
    int drawChessboard(bool underlightedCursor = false, int positionNumber = 0/*current position*/);
        void drawUnderlight();
        void underlightCursorSquare();
        void drawPieces();
        void drawNotation();
            void drawNotationContent();        
        int  getCursorCoords();
    void updateSquare  (int squareCoordX, int squareCoordY, int piece, bool pieceColor, bool underlight);
        void updateChessboard(int squareCoordX, int squareCoordY, int piece, bool pieceColor);
        void updateUnderlightArray(int squareCoordX, int squareCoordY, bool underlight);
    void offUnderlights();
    void underlight(int coordonates);
    void checkWindowSize();
    int promotionMenu();
        void loadPromotionMenuTextures(sf::Sprite buttons[]);
        void locatePromotionMenuTextures(sf::Sprite buttons[]);
        void updatePromotionMenuButtons(sf::Sprite buttons[]);
        void drawPromotionMenu(sf::Sprite buttons[]);
            void drawOverlay();
    void savePosition();
    globalType::chessboardPointer copyChessboard(const globalType::chessboardPointer oryginal);
    globalType::chessboardUnderlightPointer copyChessboardUnderlight(const globalType::chessboardUnderlightPointer oryginal);
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
