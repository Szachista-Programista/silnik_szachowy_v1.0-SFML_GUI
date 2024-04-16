#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Play.h"
#include "Menu.h"
/**
 * @brief The "Game" class contains the main loop of the program. It initializes the window upon
 * instantiation and depending on the choices made in the main menu, it launches the corresponding game.
 * It serves as the entry point for the application and orchestrates the overall flow of the program.
 */
class Game {
        Menu menu;
        sf::RenderWindow window;

public: Game();
        void run();
private:void checkWindowSize();
        int  randomColor()noexcept;
};
#endif//GAME_H