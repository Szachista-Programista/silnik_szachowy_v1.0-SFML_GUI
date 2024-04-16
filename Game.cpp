#include "Game.h"

Game::Game(): window(sf::VideoMode(globalType::windowWidth, globalType::windowHeight), "Chess")
{
    globalType::windowPtr = &window;
}
void Game::run()
{
    while (globalType::windowPtr->isOpen())
    {
        globalType::menuAction = menu.displayMainMenu();
        if     (globalType::menuAction == globalType::white)  Play(1).playWithUser();
        else if(globalType::menuAction == globalType::black)  Play(0).playWithUser();
        else if(globalType::menuAction == globalType::random) Play(randomColor()).playWithUser();
        else if(globalType::menuAction == globalType::quit)   break;
    }
}
void Game::checkWindowSize()
{
    sf::Vector2u windowSize = globalType::windowPtr->getSize();
    if (windowSize.x != globalType::windowWidth || windowSize.y != globalType::windowHeight)
    {
        globalType::windowPtr->setSize({globalType::windowWidth, globalType::windowHeight});
    }
}
int  Game::randomColor()noexcept
{
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % 2;
}