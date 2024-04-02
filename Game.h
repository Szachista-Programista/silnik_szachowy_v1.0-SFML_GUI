#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Play.h"
#include "Chessboard.h"///////////////////////
class Game {
public:///////////////////
    enum MainMenuAction
    {
        playWhiteColor,
        playBlackColor,
        playRandomColor,
        exit
    }mainMenuAction;


//private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Chessboard x;

public:
    Game();
    void readBackgroundTexture();
    void run();

//private:

MainMenuAction mainMenu();
    void loadMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void locateMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void checkWindowSize();
    void updateMainMenuButtons(sf::Sprite button[], sf::Color originalColor, sf::Color darkColor);
    void drawMainMenu(sf::Sprite button[]);
    int randomColor()noexcept;
};

#endif//GAME_H
