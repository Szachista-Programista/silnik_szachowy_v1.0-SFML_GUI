#ifndef NOTEBOOK_H
#define NOTEBOOK_H
#include <iomanip>
#include <sstream>
#include "GlobalDefinitions.h"
/**
 * @brief 
 */
class Notebook{
    bool color;
    bool engineMove;
    bool moveMarked;
    bool gameOver = false;

    int machineKingLocationX;
    int machineKingLocationY;
    int userKingLocationX;
    int userKingLocationY;

    int moveCode;
    int moveFromX;
    int moveFromY;
    int moveToX;
    int moveToY;
    int gameOverParameter;
    int promotionParameter;

    int semiMoveNumber = 0;
    int moveNumber;

    int currentNotationLine    = 0;
    int currentNotationColumn  = 0;
    int previousNotationLine   = 0;
    int previousNotationColumn = 0;

    std::string lastMoveNotation;
    std::string gameResult;
    std::string chessboardUpdateCode;

    std::string notationArray[globalType::letterHeight];

    std::string pixelArtCharacterArray[globalType::numberOfChars]          [globalType::letterHeight];
    std::string notationColumnArray   [globalType::numberOfNotationColumn] [globalType::columnHeight];

    std::vector<std::string>entireDoubleNotation;
    std::vector<std::string>entireSingleNotation;

    globalType::chessboardPointer previousChessboard;
public: globalType::chessboardPointer currentChessboard;
//********************************************************************************
public: Notebook(bool k);
private:    globalType::chessboardPointer loadPiecesArrangement();
            void loadChars();
public:~Notebook()noexcept;
        std::vector<std::string> getNotation (int moveCode);
private:    void updateParameterValues(int moveCode);
                void decipherMoveCode();
                void updateKingsLocation()noexcept;
            void markMoveAndWriteNotation();
                void markCastle()noexcept;
                void markPawnPromotion()noexcept;
                void markEnPassant()noexcept;
                void markCommonMove();
                    void markKnightMove(char movedPiece);
                    void markRookMove  (char movedPiece);
                    std::string getCoordinates(int x, int y);
                bool isThereCheck()noexcept;
            void updateEntireNotation();
                void endgameService();
                    void replacePlusWithHashtag();
public: std::string getChessboardUpdateCode()noexcept;
private:    void generateChessboardUpdateCode()noexcept;
public: std::string saveGameInNotebook();
};
#endif//NOTEBOOK_H
