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

    globalType::chessboardPointer chessboard;
    bool underlightArray[8][8]{0};
//******************************************************************************************************
    Chessboard(bool k = true);
        void readTextures();
            void readBackgroundTexture();
            void readBoardTexture();
            void readPieceTextures();
            void readUnderlightTextures();
        globalType::chessboardPointer loadPiecesArrangement();
        globalType::chessboardPointer reversePiecesArrangement(globalType::chessboardPointer chessboard);
    ~Chessboard();
    int loadCoordinates();
    int drawChessboard(bool underlightedCursor);
        void drawUnderlight();
        void underlightCursorSquare();
        void drawPieces();
        int  getCursorCoords();
    void updateSquare  (int squareCoordX, int squareCoordY, int piece, bool pieceColor, bool underlight);
        void updateChessboard(int squareCoordX, int squareCoordY, int piece, bool pieceColor);
        void updateUnderlightArray(int squareCoordX, int squareCoordY, bool underlight);
    void checkWindowSize();






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
