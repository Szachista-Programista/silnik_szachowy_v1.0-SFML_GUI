#ifndef GLOBAL_DEFINITIONS_H
#define GLOBAL_DEFINITIONS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include <thread>
#ifdef _WIN32
    #include <Windows.h>
    #include <conio.h>
#elif __APPLE__
    #include <termios.h>
    #include <unistd.h>
#elif __linux__
    #include <termios.h>
    #include <unistd.h>
#else
    #error the program only supports(Windows/Mac_OS/Linux)
#endif

namespace globalType{

    extern double(*userKingBehaviorPoints1)   (double,double);
    extern double(*engineKnightBehaviorPoints)(double,double);
    extern double(*engineBishopBehaviorPoints)(double,double);
    extern double(*engineRookBehaviorPoints1) (double,double);
    extern double(*engineRookBehaviorPoints2) (double,double);
    extern double(*engineQueenBehaviorPoints1)(double,double);
    extern double(*engineQueenBehaviorPoints2)(double,double);
    extern double(*engineKingBehaviorPoints)  (double,double);

    extern double *userKingBehaviorPriority1;
    extern double *engineKnightBehaviorPriority;
    extern double *engineBishopBehaviorPriority;
    extern double *engineRookBehaviorPriority1;
    extern double *engineRookBehaviorPriority2;
    extern double *engineQueenBehaviorPriority1;
    extern double *engineQueenBehaviorPriority2;
    extern double *engineKingBehaviorPriority;

    extern double userKingX;
    extern double userKingY;

    extern sf::RenderWindow *windowPtr;

    enum Languages{
        polish,
        english
    };
    enum GameStage{
        opening,
        middlegame,
        endgame
    };
    enum GameResult{
        engineWin,
        stalemate,
        userWin
    };
    enum KindOfEndgame{
        rooksAndQueensMate,
        rookOrQueenMate,
        unspecifiedMate
    };
    enum UserKingSideLocation{
        engineRightSide,
        engineDownSide,
        engineLeftSide,
        engineUpSide
    };
    enum UserKingCornerLocation{
        engineUpRightCorner,
        engineDownRightCorner,
        engineDownLeftCorner,
        engineUpLeftCorner
    };
    enum MenuAction{
        goBack,
        backToGame,
        black,
        mainMenu,
        play,
        random,
        saveNotation,
        settings,
        watchPlayedGame,
        white,
        quit,
        displayPastMovements,
        knight,
        bishop,
        rook,
        queen
    } extern menuAction;
    
    using chessboardPointer = char(*)[8];
    using chessboardUnderlightPointer = bool(*)[8];
    struct errorType{std::string errorMessage;};

    extern float windowWidth;
    extern float windowHeight;

    extern int numberOfButtonTexture;
    extern int numberOfBackgroundTexture;
    extern int numberOfBoardTexture;

    extern Languages setLanguage;
    extern GameStage gameStage;
    extern KindOfEndgame choosenEndgame;
    extern UserKingSideLocation userKingSideLocation;
    extern UserKingCornerLocation userKingCornerLocation;
//********************************************************************************
    void readConfigFile();
    void writeConfigFile();
}
#endif//GLOBAL_DEFINITIONS_H
