#include "Game.h"

Game::Game()
{
    readBackgroundTexture();
}
void Game::readBackgroundTexture()
{
    if (!backgroundTexture.loadFromFile("img/other/background.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);
    background.setScale(globalType::windowPtr->getSize().x / background.getLocalBounds().width, globalType::windowPtr->getSize().y / background.getLocalBounds().height);
}
void Game::run()
{
    while (globalType::windowPtr->isOpen())
    {
        mainMenuAction = mainMenu();
        if(mainMenuAction == playWhiteColor)
            Play(1).playWithUser();
        if(mainMenuAction == playBlackColor)
            Play(0).playWithUser();
        if(mainMenuAction == exit)
            break;
    }
}
Game::MainMenuAction Game::mainMenu()
{
    sf::Texture buttonTexture[4];
    sf::Sprite button[4];
    loadMainMenuButtons(buttonTexture, button);
    locateMainMenuButtons(buttonTexture, button);
    sf::Color originalColor = button[0].getColor();
    sf::Color darkColor = sf::Color(150, 150, 150);

    while (globalType::windowPtr->isOpen()) {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                //globalType::windowPtr->close();
                return MainMenuAction::exit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMainMenuButtons(button, originalColor, darkColor);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < 4; i++) {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if(i == 2)
                            return static_cast<MainMenuAction>(randomColor());
                        else
                            return static_cast<MainMenuAction>(i);
                    }
                }
            }
        }
        drawMainMenu(button);
    }
}
void Game::loadMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    if (!buttonTexture[0].loadFromFile("img/buttons/playWhiteButton.png"))
        {}//return EXIT_FAILURE;
    button[0].setTexture(buttonTexture[0]);
    if (!buttonTexture[1].loadFromFile("img/buttons/playBlackButton.png"))
        {}//return EXIT_FAILURE;
    button[1].setTexture(buttonTexture[1]);
    if (!buttonTexture[2].loadFromFile("img/buttons/playRandomColorButton.png"))
        {}//return EXIT_FAILURE;
    button[2].setTexture(buttonTexture[2]);
    if (!buttonTexture[3].loadFromFile("img/buttons/exitButton.png"))
        {}//return EXIT_FAILURE;
    button[3].setTexture(buttonTexture[3]);
}
void Game::locateMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    float windowWidth  = static_cast<float>(globalType::windowPtr->getSize().x);
    float windowHeight = static_cast<float>(globalType::windowPtr->getSize().y);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonsSpace =  50.0f;
    float allButtosHeight = 4.0f * buttonHeight + 3.0f * buttonsSpace;
    float buttonXPosition = windowWidth / 2.0f - buttonWidth / 2.0f;
    float allButtosYPosition = windowHeight / 2.0f - allButtosHeight / 2.0f;
    float buttonXScale = buttonWidth  / buttonTexture[0].getSize().x * static_cast<float>(globalType::windowWidth)  / windowWidth;
    float buttonYScale = buttonHeight / buttonTexture[0].getSize().y * static_cast<float>(globalType::windowHeight) / windowHeight;

    for(int i=0; i<4; i++)
    {
        button[i].setPosition(buttonXPosition, allButtosYPosition + i * (buttonHeight + buttonsSpace));
        button[i].setScale(buttonXScale, buttonYScale);
    }
}
void Game::checkWindowSize()
{
    sf::Vector2u windowSize = globalType::windowPtr->getSize();
    if (windowSize.x != globalType::windowWidth || windowSize.y != globalType::windowHeight) {
        globalType::windowPtr->setSize({globalType::windowWidth, globalType::windowHeight});
    }
}
void Game::updateMainMenuButtons(sf::Sprite button[], sf::Color originalColor, sf::Color darkColor)
{
    for (int i = 0; i < 4; i++) {
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y)) {
            button[i].setColor(darkColor);
        } else {
            button[i].setColor(originalColor);
        }
    }
}
void Game::drawMainMenu(sf::Sprite button[])
{
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    for (int i = 0; i < 4; i++) {
        globalType::windowPtr->draw(button[i]);
    }
    globalType::windowPtr->display();
}
int Game::randomColor()noexcept
{
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % 2;
}
