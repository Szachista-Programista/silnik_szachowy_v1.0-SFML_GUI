#ifndef PLAY_H
#define PLAY_H
#include <cctype>
#include "Chessboard.h"
#include "Engine.h"
#include "Notebook.h"
#include "Menu.h"
/**
 * @brief
 */
class Play{
    bool color;
    bool correctMovementMade;
    bool firstCoordChoosen;
    bool gameOver = false;
    int engineMoveCode;
    int userMoveCode;
    int chosenCoordinates;
    int userActionCode;

    Chessboard chessboard;
    Engine     engine;
    Notebook   notebook;
    Menu       menu;

    bool isNotationSaved = false;

//********************************************************************************
public: Play(bool k)noexcept;
        void playWithUser();
private:    bool userMoveService();
                bool userActionService();
                bool isChosenUserPiece();
                void firstCoordService();
                void secondCoordService();
                    bool isUserMakesPromotion()noexcept;
                        void updateChessboard(std::string updateCode, bool underlight);
                            int  getPieceCode (char cHar);
                            bool getPieceColor(char cHar);
            bool engineMoveService(int moveCode);
                bool isItGameover();


};
#endif//PLAY_H
