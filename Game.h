#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Play.h"

class Game {
public:///////////////////
    enum MenuAction
    {
        playWhiteColor,
        playBlackColor,
        playRandomColor,
        back,
        play,
        settings,
        quit
    }menuAction;


    float buttonScaleX;
    float buttonScaleY;

//private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

public:
    Game();
    void readBackgroundTexture();
    void run();

//private:

void checkWindowSize();


MenuAction mainMenu();
    void loadMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void locateMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void updateMainMenuButtons(sf::Sprite button[]);
    void drawMainMenu(sf::Sprite button[]);
/*
MenuAction playMenu();
    void loadPlayMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void locatePlayMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void updatePlayMenuButtons(sf::Sprite button[]);
    void drawPlayMenu(sf::Sprite button[]);

MenuAction settingsMenu();
    void loadSettingsMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void locateSettingsMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);
    void updateSettingsMenuButtons(sf::Sprite button[]);
    void drawSettingsMenu(sf::Sprite button[]);
*/

int  randomColor()noexcept;
};

#endif//GAME_H
