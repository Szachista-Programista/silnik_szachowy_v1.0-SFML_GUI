#include "Game.h"

Game::Game()
{
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
        {
            std::cout<<"y";
            Play(1).playWithUser();

        }
        if(menuAction == playBlackColor)
        {
            std::cout<<"x";
            Play(0).playWithUser();

        }
        if(menuAction == playRandomColor)
            Play(randomColor()).playWithUser();
        if(menuAction == quit)
            break;
    }
}

void Game::checkWindowSize()
{
    sf::Vector2u windowSize = globalType::windowPtr->getSize();
    if (windowSize.x != globalType::windowWidth || windowSize.y != globalType::windowHeight) {
        globalType::windowPtr->setSize({globalType::windowWidth, globalType::windowHeight});
    }
}





Game::MenuAction Game::mainMenu()
{
    sf::Texture buttonTexture[3];
    sf::Sprite button[3];
    loadMainMenuButtons(buttonTexture, button);
    locateMainMenuButtons(buttonTexture, button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                exit(0);
            }
            if (event.type == sf::Event::MouseMoved)
                updateMainMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < 3; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0:
                                    std::cout<<i;
                                    return playBlackColor;
 std::cout<<i;

/*

                                menuAction = playMenu();
                                if(menuAction == back)
                                    break;
                                else
                                    return menuAction;*/
                            //case 1: return settingsMenu();
                            case 2: exit(0);
                        }
                }
            }//std::cout<<
        }
        drawMainMenu(button);
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
void Game::locateMainMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    for (int i = 0; i < 3; i++)
        button[i].setOrigin(button[i].getGlobalBounds().width / 2.0f, button[i].getGlobalBounds().height / 2.0f);
    float windowWidth  = static_cast<float>(globalType::windowPtr->getSize().x);
    float windowHeight = static_cast<float>(globalType::windowPtr->getSize().y);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonsSpace =  50.0f;
    float allButtosHeight = 2.0f * buttonHeight + 2.0f * buttonsSpace;
    float buttonXPosition = windowWidth / 2.0f;
    float allButtosYPosition = windowHeight / 2.0f - allButtosHeight / 2.0f;
    buttonScaleX = buttonWidth  / buttonTexture[0].getSize().x /** static_cast<float>(globalType::windowWidth)  / windowWidth*/;
    buttonScaleY = buttonHeight / buttonTexture[0].getSize().y /** static_cast<float>(globalType::windowHeight) / windowHeight*/;
    for(int i=0; i<3; i++)
    {
        button[i].setPosition(buttonXPosition, allButtosYPosition + i * (buttonHeight + buttonsSpace));
        button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::updateMainMenuButtons(sf::Sprite button[])
{
    for (int i = 0; i < 4; i++) {
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            button[i].setScale(buttonScaleX * 1.15f, buttonScaleY * 1.15f);
        else
            button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::drawMainMenu(sf::Sprite button[])
{
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    for (int i = 0; i < 3; i++)
        globalType::windowPtr->draw(button[i]);
    globalType::windowPtr->display();
}

/*
Game::MenuAction Game::playMenu()
{
    sf::Texture buttonTexture[4];
    sf::Sprite button[4];
    loadPlayMenuButtons(buttonTexture, button);
    locatePlayMenuButtons(buttonTexture, button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                exit(0);
            }
            if (event.type == sf::Event::MouseMoved)
                updatePlayMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < 4; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return playWhiteColor;
                            case 1: return playBlackColor;
                            case 2: return playRandomColor;
                            case 3: return back;
                        }
                }
            }
        }
        drawPlayMenu(button);
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
void Game::locatePlayMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    for (int i = 0; i < 4; i++)
        button[i].setOrigin(button[i].getGlobalBounds().width / 2.0f, button[i].getGlobalBounds().height / 2.0f);
    float windowWidth  = static_cast<float>(globalType::windowPtr->getSize().x);
    float windowHeight = static_cast<float>(globalType::windowPtr->getSize().y);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonsSpace =  50.0f;
    float allButtosHeight = 3.0f * buttonHeight + 3.0f * buttonsSpace;
    float buttonXPosition = windowWidth / 2.0f;
    float allButtosYPosition = windowHeight / 2.0f - allButtosHeight / 2.0f;
    buttonScaleX = buttonWidth  / buttonTexture[0].getSize().x;// static_cast<float>(globalType::windowWidth)  / windowWidth;
    buttonScaleY = buttonHeight / buttonTexture[0].getSize().y;// static_cast<float>(globalType::windowHeight) / windowHeight;
    for(int i=0; i<4; i++)
    {
        button[i].setPosition(buttonXPosition, allButtosYPosition + i * (buttonHeight + buttonsSpace));
        button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::updatePlayMenuButtons(sf::Sprite button[])
{
    for (int i = 0; i < 4; i++) {
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            button[i].setScale(buttonScaleX * 1.15f, buttonScaleY * 1.15f);
        else
            button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::drawPlayMenu(sf::Sprite button[])
{
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    for (int i = 0; i < 4; i++)
        globalType::windowPtr->draw(button[i]);
    globalType::windowPtr->display();
}


Game::MenuAction Game::settingsMenu()
{
    sf::Texture buttonTexture[3];
    sf::Sprite button[3];
    loadSettingsMenuButtons(buttonTexture, button);
    locateSettingsMenuButtons(buttonTexture, button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                exit(0);
            }
            if (event.type == sf::Event::MouseMoved)
                updateSettingsMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < 3; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return playMenu();
                            case 1: return settingsMenu();
                            case 2: exit(0);
                        }
                }
            }
        }
        drawSettingsMenu(button);
    }
}
void Game::loadSettingsMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    if (!buttonTexture[0].loadFromFile("img/buttons/playButton.png"))
        {}//return EXIT_FAILURE;
    button[0].setTexture(buttonTexture[0]);
    if (!buttonTexture[1].loadFromFile("img/buttons/settingsButton.png"))
        {}//return EXIT_FAILURE;
    button[1].setTexture(buttonTexture[1]);
    if (!buttonTexture[2].loadFromFile("img/buttons/exitButton.png"))
        {}//return EXIT_FAILURE;
    button[2].setTexture(buttonTexture[3]);
}
void Game::locateSettingsMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    for (int i = 0; i < 3; i++)
        button[i].setOrigin(button[i].getGlobalBounds().width / 2.0f, button[i].getGlobalBounds().height / 2.0f);
    float windowWidth  = static_cast<float>(globalType::windowPtr->getSize().x);
    float windowHeight = static_cast<float>(globalType::windowPtr->getSize().y);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonsSpace =  50.0f;
    float allButtosHeight = 2.0f * buttonHeight + 2.0f * buttonsSpace;
    float buttonXPosition = windowWidth / 2.0f;
    float allButtosYPosition = windowHeight / 2.0f - allButtosHeight / 2.0f;
    buttonScaleX = buttonWidth  / buttonTexture[0].getSize().x;// static_cast<float>(globalType::windowWidth)  / windowWidth;
    buttonScaleY = buttonHeight / buttonTexture[0].getSize().y;// static_cast<float>(globalType::windowHeight) / windowHeight;
    for(int i=0; i<3; i++)
    {
        button[i].setPosition(buttonXPosition, allButtosYPosition + i * (buttonHeight + buttonsSpace));
        button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::updateSettingsMenuButtons(sf::Sprite button[])
{
    for (int i = 0; i < 4; i++) {
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            button[i].setScale(buttonScaleX * 1.15f, buttonScaleY * 1.15f);
        else
            button[i].setScale(buttonScaleX, buttonScaleY);
    }
}
void Game::drawSettingsMenu(sf::Sprite button[])
{
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    for (int i = 0; i < 4; i++)
        globalType::windowPtr->draw(button[i]);
    globalType::windowPtr->display();
}

*/


int  Game::randomColor()noexcept
{
    srand(static_cast<unsigned int>(time(nullptr)));
    return rand() % 2;
}
