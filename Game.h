#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Play.h"
#include "Menu.h"

class Game {
        Menu menu;
        sf::RenderWindow window;

public: Game();
        void run();
private:void checkWindowSize();
        int  randomColor()noexcept;
};
#endif//GAME_H
