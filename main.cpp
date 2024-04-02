#include "Game.h"


int main() {

    globalType::windowWidth  = 1000;
    globalType::windowHeight =  750;
    sf::RenderWindow window(sf::VideoMode(globalType::windowWidth, globalType::windowHeight), "Chess");
    globalType::windowPtr = &window;

    try
    {
        Game game;
        game.run();
    }
    catch(globalType::errorType &e)
    {
        std::cout<<e.errorMessage;
        systemInfo::getChar();
    }
    return 0;
}


