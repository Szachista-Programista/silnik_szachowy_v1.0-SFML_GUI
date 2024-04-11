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
        goBack,
        play,
        settings,
        quit,
        ok
    }menuAction;
    enum NumberOfButtons
    {
        mainMenuButtons = 3,
        playMenuButtons = 4,
        settingsMenuButtons = 2,
    };
    
    float windowHeight;
    float windowWidth;

    float buttonScaleX;
    float buttonScaleY;

//private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite background;

public:
    Game(int width, int height);
    void readBackgroundTexture();
    void run();

MenuAction mainMenu();
    void loadMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);

MenuAction playMenu();
    void loadPlayMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);

MenuAction settingsMenu();
    void loadSettingsMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[]);

void checkWindowSize();
void locateMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[], NumberOfButtons x);
void updateMenuButtons(sf::Sprite button[], NumberOfButtons x);
void drawMenu(sf::Sprite button[], NumberOfButtons x);
int  randomColor()noexcept;
};
#endif//GAME_H
