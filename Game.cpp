#include "Game.h"

Game::Game(int width, int height): window(sf::VideoMode(width, height), "Chess")
{
    globalType::previousWindowWidth  = globalType::currentWindowWidth  = width;
    globalType::previousWindowHeight = globalType::currentWindowHeight = height;
    globalType::windowPtr = &window;

    globalType::readConfigFile();
    globalType::readCommuniqueFile();
    readBackgroundTexture();
    menuAction = playWhiteColor;///////////////////
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
        menuAction = mainMenu();
        if(menuAction == playWhiteColor)
            Play(1).playWithUser();
        else if(menuAction == playBlackColor)
            Play(0).playWithUser();
        else if(menuAction == playRandomColor)
            Play(randomColor()).playWithUser();
        else if(menuAction == quit)
            break;
    }
}

Game::MenuAction Game::mainMenu()
{
    sf::Texture buttonTexture[mainMenuButtons];
    sf::Sprite button[mainMenuButtons];
    loadMainMenuButtons(buttonTexture, button);
    locateMenuButtons(buttonTexture, button, mainMenuButtons);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button, mainMenuButtons);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < mainMenuButtons; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0:
                                menuAction = playMenu();
                                if(menuAction == goBack)
                                    break;
                                else
                                    return menuAction;
                            case 1:
                                menuAction = settingsMenu();
                                if(menuAction == goBack)
                                    break;
                                else
                                    return menuAction;
                            case 2:
                                return quit;
                        }
                }
            }
        }
        drawMenu(button, mainMenuButtons);
    }
}
void Game::loadMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    if (!buttonTexture[0].loadFromFile("img/buttons/playButton.png"))
        {}//return EXIT_FAILURE;
    button[0].setTexture(buttonTexture[0]);
    if (!buttonTexture[1].loadFromFile("img/buttons/settingsButton.png"))
        {}//return EXIT_FAILURE;
    button[1].setTexture(buttonTexture[1]);
    if (!buttonTexture[2].loadFromFile("img/buttons/exitButton.png"))
        {}//return EXIT_FAILURE;
    button[2].setTexture(buttonTexture[2]);
}

Game::MenuAction Game::playMenu()
{
    sf::Texture buttonTexture[playMenuButtons];
    sf::Sprite button[playMenuButtons];
    loadPlayMenuButtons(buttonTexture, button);
    locateMenuButtons(buttonTexture, button, playMenuButtons);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button, playMenuButtons);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < playMenuButtons; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return playWhiteColor;
                            case 1: return playBlackColor;
                            case 2: return playRandomColor;
                            case 3: return goBack;
                        }
                }
            }
        }
        drawMenu(button, playMenuButtons);
    }
}
void Game::loadPlayMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
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
    if (!buttonTexture[3].loadFromFile("img/buttons/backButton.png"))
        {}//return EXIT_FAILURE;
    button[3].setTexture(buttonTexture[3]);
}

Game::MenuAction Game::settingsMenu()
{
    sf::Texture buttonTexture[settingsMenuButtons];
    sf::Sprite button[settingsMenuButtons];
    loadSettingsMenuButtons(buttonTexture, button);
    locateMenuButtons(buttonTexture, button, settingsMenuButtons);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button, settingsMenuButtons);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < settingsMenuButtons; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0:
                                    break;
                            case 1: return goBack;
                        }
                }
            }
        }
        drawMenu(button, settingsMenuButtons);
    }
}
void Game::loadSettingsMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    if (!buttonTexture[0].loadFromFile("img/buttons/setWindowSizeButton.png"))
        {}//return EXIT_FAILURE;
    button[0].setTexture(buttonTexture[0]);
    if (!buttonTexture[1].loadFromFile("img/buttons/backButton.png"))
        {}//return EXIT_FAILURE;
    button[1].setTexture(buttonTexture[1]);
}


void Game::checkWindowSize()
{
    sf::Vector2u windowSize = globalType::windowPtr->getSize();
    if (windowSize.x != globalType::currentWindowWidth || windowSize.y != globalType::currentWindowHeight)
    {
        globalType::windowPtr->setSize({globalType::currentWindowWidth, globalType::currentWindowHeight});
    }
}
void Game::locateMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[], NumberOfButtons x)
{
    for (int i = 0; i < x; i++)
        button[i].setOrigin(button[i].getGlobalBounds().width / 2.0f, button[i].getGlobalBounds().height / 2.0f);
    float windowWidth  = static_cast<float>(globalType::windowPtr->getSize().x);
    float windowHeight = static_cast<float>(globalType::windowPtr->getSize().y);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonsSpace =  50.0f;
    float allButtosHeight = (x - 1) * (buttonHeight + buttonsSpace);
    float buttonXPosition = windowWidth / 2.0f;
    float allButtosYPosition = windowHeight / 2.0f - allButtosHeight / 2.0f;
    buttonScaleX = buttonWidth  / buttonTexture[0].getSize().x;
    buttonScaleY = buttonHeight / buttonTexture[0].getSize().y;
    for(int i=0; i<x; i++)
    {
        button[i].setPosition(static_cast<float>(globalType::windowPtr->getSize().x) / 2.0f, allButtosYPosition + i * (buttonHeight + buttonsSpace));
        button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::updateMenuButtons(sf::Sprite button[], NumberOfButtons x)
{
    for (int i = 0; i < x; i++) {
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            button[i].setScale(buttonScaleX * 1.15f, buttonScaleY * 1.15f);
        else
            button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::drawMenu(sf::Sprite button[], NumberOfButtons x)
{
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    for (int i = 0; i < x; i++)
        globalType::windowPtr->draw(button[i]);
    globalType::windowPtr->display();
}
int  Game::randomColor()noexcept
{
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % 2;
}
