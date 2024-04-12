#include "Menu.h"

Menu::Menu(bool k): color{k}
{
    globalType::readConfigFile();
    loadTextures();
}
void Menu::loadTextures()
{
    loadButtonTextures();
    setButtonSprites();
    loadBoardTextures();
    setBoardSprites();
    loadPromotionPieceTextures();
    setPromotionPieceSprites();
    loadbackgroundTexture();
    setbackgroundSprites();
}
    void Menu::loadButtonTextures()
{
    try
    {
        if((!buttonTexture[goBack         ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/back.png"))
        || (!buttonTexture[backToGame     ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/backToGame.png"))
        || (!buttonTexture[black          ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/black.png"))
        || (!buttonTexture[exit           ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/exit.png"))
        || (!buttonTexture[mainMenu       ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/mainMenu.png"))
        || (!buttonTexture[menu           ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/menu.png"))
        || (!buttonTexture[notationSaved  ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/notationSaved.png"))
        || (!buttonTexture[play           ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/play.png"))
        || (!buttonTexture[random         ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/random.png"))
        || (!buttonTexture[saveNotation   ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/saveNotation.png"))
        || (!buttonTexture[settings       ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/settings.png"))
        || (!buttonTexture[watchPlayedGame].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/watchPlayedGame.png"))
        || (!buttonTexture[white          ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/white.png"))
        || (!buttonTexture[LeftArrow      ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/LeftArrow.png"))
        || (!buttonTexture[endLeftArrow   ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/endLeftArrow.png"))
        || (!buttonTexture[RightArrow     ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/RightArrow.png"))
        || (!buttonTexture[endRightArrow  ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/endRightArrow.png"))
        || (!buttonTexture[setButtons     ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/setButtons.png"))
        || (!buttonTexture[set1           ].loadFromFile("img/buttons/1/set.png"))
        || (!buttonTexture[set2           ].loadFromFile("img/buttons/2/set.png"))
        || (!buttonTexture[set3           ].loadFromFile("img/buttons/3/set.png"))
        || (!buttonTexture[set4           ].loadFromFile("img/buttons/4/set.png"))
        || (!buttonTexture[set5           ].loadFromFile("img/buttons/5/set.png"))
        || (!buttonTexture[set6           ].loadFromFile("img/buttons/6/set.png")))
            throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    void Menu::setButtonSprites()
{
    for(int i = 0; i < buttonNumbers; i++)
        buttonSprite[i].setTexture(buttonTexture[i]);
    buttonSprite[notationSaved].setColor(sf::Color(0,255,0,255));
}
    void Menu::loadBoardTextures()
{
    try
    {
        if(!boardTexture.loadFromFile("img/board/" + std::to_string(globalType::numberOfBoardTexture) + "/" + (color? "whiteSide": "blackSide") + ".png"))
            throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    void Menu::setBoardSprites()
{
    boardSprite.setTexture(boardTexture);
}
    void Menu::loadPromotionPieceTextures()
{
    try
    {
            if((!promotionPieceTextures[whiteKnight].loadFromFile("img/pieces/2.png"))
            || (!promotionPieceTextures[whiteBishop].loadFromFile("img/pieces/3.png"))
            || (!promotionPieceTextures[whiteRook  ].loadFromFile("img/pieces/4.png"))
            || (!promotionPieceTextures[whiteQueen ].loadFromFile("img/pieces/5.png"))
            || (!promotionPieceTextures[blackKnight].loadFromFile("img/pieces/8.png"))
            || (!promotionPieceTextures[blackBishop].loadFromFile("img/pieces/9.png"))
            || (!promotionPieceTextures[blackRook  ].loadFromFile("img/pieces/10.png"))
            || (!promotionPieceTextures[blackQueen ].loadFromFile("img/pieces/11.png")))
                throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    void Menu::setPromotionPieceSprites()
{
    for(int i = 0; i < promotionPieceNumbers; i++)
        promotionPieceSprite[i].setTexture(promotionPieceTextures[i]);
}
    void Menu::loadbackgroundTexture()
{
    try
    {
        if(!backgroundTexture.loadFromFile("img/background/" + std::to_string(globalType::numberOfBackgroundTexture) + ".png"))
            throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    void Menu::setbackgroundSprites()
{
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(static_cast<float>(globalType::windowWidth) / backgroundSprite.getLocalBounds().width, static_cast<float>(globalType::windowHeight) / backgroundSprite.getLocalBounds().height);
}

    void Menu::setGameBackground()
{
gameBackgroundTexture.create(globalType::windowWidth, globalType::windowHeight);
gameBackgroundTexture.update(*globalType::windowPtr);
gameBackgroundSprite.setTexture(gameBackgroundTexture);
gameBackgroundSprite.setColor(sf::Color(160, 130, 100, 255));
}

    globalType::MenuAction Menu::displayMainMenu()
{
    std::vector<Button> button = {play, settings, exit};
    locateMenuButtons(button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0:
                                globalType::menuAction = displayPlayMenu();
                                if(globalType::menuAction == globalType::goBack)
                                    break;
                                else
                                    return globalType::menuAction;
                            case 1:
                                globalType::menuAction = displaySettingsMenu();
                                if(globalType::menuAction == globalType::goBack)
                                    break;
                                else
                                    return globalType::menuAction;
                            case 2:
                                return globalType::quit;
                        }
                }
                locateMenuButtons(button);
            }
        }
        drawMenu(button);
    }
}
        globalType::MenuAction Menu::displayPlayMenu()
{
    std::vector<Button> button = {white, black, random, goBack};
    locateMenuButtons(button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return globalType::white;
                            case 1: return globalType::black;
                            case 2: return globalType::random;
                            case 3: return globalType::goBack;
                        }
                }
                locateMenuButtons(button);
            }
        }
        drawMenu(button);
    }
}
        globalType::MenuAction Menu::displaySettingsMenu()
{
    std::vector<Button> button = {setButtons, goBack};
    locateMenuButtons(button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0:
                                globalType::menuAction = displayButtonSettings();
                                if(globalType::menuAction == globalType::goBack)
                                    break;
                                else
                                    return globalType::menuAction;
                            case 1:
                                return globalType::goBack;
                        }
                }
                locateMenuButtons(button);
            }
        }
        drawMenu(button);
    }
}
            globalType::MenuAction Menu::displayButtonSettings()
{
    std::vector<Button> button = {set1, set2, set3, set4, set5, set6};
    locateMenuButtons(button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        globalType::numberOfButtonTexture = i + 1;
                        globalType::writeConfigFile();
                        loadButtonTextures();
                        setButtonSprites();
                        return globalType::goBack;
                    }
                }
                locateMenuButtons(button);
            }
        }
        drawMenu(button);
    }

}
    globalType::MenuAction Menu::displayGameOverMenu(bool notation, globalType::GameResult gameResult)
{
    isNotationSaved = notation;
    std::vector<Button> button = {mainMenu, (isNotationSaved? notationSaved: saveNotation), watchPlayedGame};
    locateMenuButtons(button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0:
                                return globalType::mainMenu;
                            case 1:
                                if( ! isNotationSaved)
                                {
                                    button[1] = notationSaved;
                                    buttonSprite[button[1]].setScale(buttonScaleX, buttonScaleY);
                                    isNotationSaved = true;
                                    return globalType::saveNotation;
                                }
                                break;
                            case 2:
                                return globalType::displayPastMovements;
                        }
                }
                locateMenuButtons(button);
            }
        }
        drawMenu(button, true);
    }
}
    globalType::MenuAction Menu::displayGameMenu(bool notation)
{
    isNotationSaved = notation;
    std::vector<Button> button = {backToGame, mainMenu, (isNotationSaved? notationSaved: saveNotation)};
    locateMenuButtons(button);
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return globalType::backToGame;
                            case 1: return globalType::mainMenu;
                            case 2:
                                if( ! isNotationSaved)
                                {
                                    button[2] = notationSaved;
                                    buttonSprite[button[2]].setScale(buttonScaleX, buttonScaleY);
                                    isNotationSaved = true;
                                    return globalType::saveNotation;
                                }
                                break;
                        }
                }
                locateMenuButtons(button);
            }
        }
        drawMenu(button, true);
    }
}



void Menu::locateMenuButtons(std::vector<Button> button)
{
    for (int i = 0; i < button.size(); i++)
        buttonSprite[button[i]].setOrigin(300.0f, 62.0f);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonsSpace =  50.0f;
    float allButtosHeight = (button.size() - 1) * (buttonHeight + buttonsSpace);
    float buttonXPosition = globalType::windowWidth / 2.0f;
    float allButtosYPosition = globalType::windowHeight / 2.0f - allButtosHeight / 2.0f;
    buttonScaleX = buttonWidth  / buttonTexture[0].getSize().x;
    buttonScaleY = buttonHeight / buttonTexture[0].getSize().y;
    for(int i=0; i < button.size(); i++)
    {
        buttonSprite[button[i]].setPosition(buttonXPosition, allButtosYPosition + i * (buttonHeight + buttonsSpace));
        buttonSprite[button[i]].setScale(buttonScaleX, buttonScaleY);
    }
    if(isNotationSaved)
    {
        buttonSprite[notationSaved].setScale(buttonScaleX, buttonScaleY);
        buttonSprite[notationSaved].setColor(sf::Color(0,255,0,255));
    }
    else
    {
        buttonSprite[notationSaved].setTexture(buttonTexture[notationSaved]);
    }
}
void Menu::updateMenuButtons(std::vector<Button> button)
{
    for (int i = 0; i < button.size(); i++)
    {
        if(button[i] == notationSaved && isNotationSaved)
            continue;
        sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            buttonSprite[button[i]].setScale(buttonScaleX * 1.15f, buttonScaleY * 1.15f);
        else
            buttonSprite[button[i]].setScale(buttonScaleX, buttonScaleY);
    }
}
void Menu::drawMenu(std::vector<Button> button, bool gameBackground)
{
    globalType::windowPtr->clear();
    if(gameBackground)
    {
        globalType::windowPtr->draw(gameBackgroundSprite);
drawOverlay();

    }
    else
        globalType::windowPtr->draw(backgroundSprite);
    for (int i = 0; i < button.size(); i++)
        globalType::windowPtr->draw(buttonSprite[button[i]]);
    globalType::windowPtr->display();
}
void Menu::checkWindowSize()
{
    sf::Vector2u windowSize = globalType::windowPtr->getSize();
    if (windowSize.x != globalType::windowWidth || windowSize.y != globalType::windowHeight)
    {
        globalType::windowPtr->setSize({globalType::windowWidth, globalType::windowHeight});
    }
}


void Menu::drawOverlay()
{
    sf::RectangleShape overlay(sf::Vector2f(globalType::windowWidth, globalType::windowHeight));
    overlay.setFillColor(sf::Color(160, 130, 100, 150));
    globalType::windowPtr->draw(overlay);
}
