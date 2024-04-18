#ifndef PLAY_H
#define PLAY_H
#include <cctype>
#include "Chessboard.h"
#include "Engine.h"
#include "Notebook.h"
#include "Menu.h"
/**
 * @brief Class responsible for managing a single game session. It interacts with classes such as
 * Chessboard, Engine, Notebook, and Menu to display appropriate menus during the game,
 * check for game termination conditions, and communicate between these subordinate classes.
 * Primarily, it serves as the game loop, alternately handling user input and
 * generating moves by the engine.
 */
class Play{
        bool color;
        bool correctMovementMade;
        bool firstCoordChoosen;
        bool gameOver = false;
        bool isNotationSaved = false;

        int engineMoveCode;
        int userMoveCode;
        int chosenCoordinates;
        int userActionCode;

        Chessboard chessboard;
        Engine     engine;
        Notebook   notebook;
        Menu       menu;
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
