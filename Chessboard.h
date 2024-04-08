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
    enum GameOverMenuAction
    {
        mainMenu,
        saveNotation,
        watchPlayedGame,
        quit
    }gameOverMenuAction;

    bool color;

    float windowHeight;
    float windowWidth;
    float boardSize;
    float marginSize;
    float squareSize;
    float squareScale;
    float promotionMenuButtonScale;
    float gameOverMenuButtonScaleX;
    float gameOverMenuButtonScaleY;
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
        void loadPromotionMenuTextures(sf::Sprite button[]);
        void locatePromotionMenuTextures(sf::Sprite button[]);
        void updatePromotionMenuButtons(sf::Sprite button[]);
        void drawPromotionMenu(sf::Sprite button[]);
            void drawOverlay();
    void savePosition();
    globalType::chessboardPointer copyChessboard(const globalType::chessboardPointer oryginal);
    globalType::chessboardUnderlightPointer copyChessboardUnderlight(const globalType::chessboardUnderlightPointer oryginal);


int gameOverMenu(globalType::GameResult gameResult);
    void loadGameOverMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void locateGameOverMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void updateGameOverMenuButtons(sf::Sprite button[]);
    void drawGameOverMenu(sf::Sprite button[]);


void saveGameInNotebook();

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
