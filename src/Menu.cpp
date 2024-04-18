#include "../include/Menu.h"

Menu::Menu(bool k): color{k}
{
    globalType::readConfigFile();
    loadFont();
    loadTextures();
}
    void Menu::loadFont()
{
    try
    {
    if (!font.loadFromFile("fonts/arial.ttf"))
        throw std::runtime_error("Cannot load arial.ttf");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    text.setFont(font);
    text.setCharacterSize((int)(globalType::windowHeight/14));
}
    void Menu::loadTextures()
{
    loadButtonTextures();
    setButtonSprites();
    loadBoardTextures();
    setBoardSprites();
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
        || (!buttonTexture[setWindowSize  ].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/setWindowSize.png"))
        || (!buttonTexture[setBoardTexture].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/setBoardTexture.png"))
        || (!buttonTexture[whiteKnight    ].loadFromFile("img/pieces/2.png"))
        || (!buttonTexture[whiteBishop    ].loadFromFile("img/pieces/3.png"))
        || (!buttonTexture[whiteRook      ].loadFromFile("img/pieces/4.png"))
        || (!buttonTexture[whiteQueen     ].loadFromFile("img/pieces/5.png"))
        || (!buttonTexture[blackKnight    ].loadFromFile("img/pieces/8.png"))
        || (!buttonTexture[blackBishop    ].loadFromFile("img/pieces/9.png"))
        || (!buttonTexture[blackRook      ].loadFromFile("img/pieces/10.png"))
        || (!buttonTexture[blackQueen     ].loadFromFile("img/pieces/11.png"))
        || (!buttonTexture[boardMiniature1].loadFromFile("img/board/1/miniature.png"))
        || (!buttonTexture[boardMiniature2].loadFromFile("img/board/2/miniature.png"))
        || (!buttonTexture[boardMiniature3].loadFromFile("img/board/3/miniature.png"))
        || (!buttonTexture[boardMiniature4].loadFromFile("img/board/4/miniature.png"))
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
        void Menu::loadbackgroundTexture()
{
    try
    {
        if(!backgroundTexture.loadFromFile("img/background/1.png"))
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
                updateMenuButtons(button, buttonScaleX, buttonScaleY);
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
                updateMenuButtons(button, buttonScaleX, buttonScaleY);
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
    std::vector<Button> button = {setButtons, setWindowSize, setBoardTexture, goBack};
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
                updateMenuButtons(button, buttonScaleX, buttonScaleY);
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
                                text.setFillColor(sf::Color::White);
                                globalType::menuAction = displayWindowSizeSettings();
                                if(globalType::menuAction == globalType::goBack)
                                    break;
                                else
                                    return globalType::menuAction;
                            case 2:
                                globalType::menuAction = displayBoardsSettings();
                                if(globalType::menuAction == globalType::goBack)
                                    break;
                                else
                                    return globalType::menuAction;
                            case 3:
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
                updateMenuButtons(button, buttonScaleX, buttonScaleY);
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
            }
        }
        drawMenu(button);
    }

}
            globalType::MenuAction Menu::displayWindowSizeSettings()
{
    std::vector<Button> button = {goBack};
    float width;
    float height;
    locateMenuButtons(button);
    while (globalType::windowPtr->isOpen())
    {
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::Resized)
            {
                globalType::windowResized = true;
                width  = event.size.width;
                height = event.size.height;
                if(width < 500 || height < 375)
                {
                    globalType::windowWidth  = 500;
                    globalType::windowHeight = 375;
                }
                else if(height == globalType::windowHeight)
                {
                    globalType::windowWidth  = width;
                    globalType::windowHeight = width * 0.75;
                }
                else if(width == globalType::windowWidth)
                {
                    globalType::windowWidth  = height / 0.75;
                    globalType::windowHeight = height;
                }
                else if(height / width > 0.75)
                {
                    globalType::windowWidth  = width;
                    globalType::windowHeight = width * 0.75;
                }
                else if(height / width < 0.75)
                {
                    globalType::windowWidth  = height / 0.75;
                    globalType::windowHeight = height;
                }
                globalType::windowPtr->close();
                return globalType::quit;
            }
            if (event.type == sf::Event::MouseMoved)
                updateMenuButtons(button, buttonScaleX, buttonScaleY);
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        return globalType::goBack;
                }
                locateMenuButtons(button);
            }
        }
        drawMenu(button, false, "Set window size.");
    }

}
            globalType::MenuAction Menu::displayBoardsSettings()
{
    std::vector<Button> button = {boardMiniature1, boardMiniature2, boardMiniature3, boardMiniature4};
    locateBoardsSettingsButtons(button);
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
                updateMenuButtons(button, boardMiniatureButtonScale, boardMiniatureButtonScale);
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        globalType::numberOfBoardTexture = i + 1;
                        globalType::writeConfigFile();
                        loadBoardTextures();
                        setBoardSprites();
                        return globalType::goBack;
                    }
                }
            }
        }
        drawMenu(button);
    }
}
                void Menu::locateBoardsSettingsButtons(std::vector<Button> button)
{
    for (int i = 0; i < button.size(); i++)
        buttonSprite[button[i]].setOrigin(100.0f, 100.0f);
    float buttonSize  = globalType::windowHeight * 0.15f;
    float buttonSpace =  globalType::windowHeight * 0.08f;
    float allButtosWidth = 3.0f * buttonSize + 3.0f * buttonSpace;
    float allButtosXPosition = globalType::windowWidth / 2.0f - allButtosWidth / 2.0f;
    float buttonYPosition = globalType::windowHeight / 2.0f;
    boardMiniatureButtonScale = buttonSize  / buttonTexture[whiteKnight].getSize().x;
    for(int i=0; i < button.size(); i++)
    {
        buttonSprite[button[i]].setPosition(allButtosXPosition + i * (buttonSize + buttonSpace), buttonYPosition);
        buttonSprite[button[i]].setScale(boardMiniatureButtonScale, boardMiniatureButtonScale);
    }
}
    globalType::MenuAction Menu::displayGameOverMenu(bool notation, globalType::GameResult gameResult)
{
    isNotationSaved = notation;
    std::vector<Button> button = {mainMenu, (isNotationSaved? notationSaved: saveNotation), watchPlayedGame};
    std::string gameOverCause = setNoteContent(gameResult);

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
                updateMenuButtons(button, buttonScaleX, buttonScaleY);
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
        drawMenu(button, true, gameOverCause);
    }
}
        std::string Menu::setNoteContent(globalType::GameResult gameResult)
{
    switch (gameResult)
    {
        case globalType::engineWin: text.setFillColor(sf::Color(80, 0, 0)); return "Game Over - engine win!";
        case globalType::stalemate: text.setFillColor(sf::Color(80, 0, 0)); return "Game Over - stalemate.";
        case globalType::userWin:   text.setFillColor(sf::Color(0, 80, 0)); return "Game Over - You win!";
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
                updateMenuButtons(button, buttonScaleX, buttonScaleY);
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
    globalType::MenuAction Menu::displayPromotionMenuMenu()
{
    std::vector<Button> button = (color ? std::vector<Button>{whiteKnight, whiteBishop, whiteRook, whiteQueen} : std::vector<Button>{blackKnight, blackBishop, blackRook, blackQueen});
    locatePromotionMenuButtons(button);
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
                updateMenuButtons(button, promotionButtonScale, promotionButtonScale);
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < button.size(); i++)
                {
                    sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return globalType::knight;
                            case 1: return globalType::bishop;
                            case 2: return globalType::rook;
                            case 3: return globalType::queen;
                        }
                }
            }
        }
        drawMenu(button, true);
    }
}
        void Menu::locatePromotionMenuButtons(std::vector<Button> button)
{
    for (int i = 0; i < button.size(); i++)
        buttonSprite[button[i]].setOrigin(50.0f, 50.0f);
    float buttonSize  = globalType::windowHeight * 0.16f;
    float buttonSpace =  globalType::windowHeight * 0.02f;
    float allButtosWidth = 3.0f * buttonSize + 3.0f * buttonSpace;
    float allButtosXPosition = globalType::windowWidth / 2.0f - allButtosWidth / 2.0f;
    float buttonYPosition = globalType::windowHeight / 2.0f;
    promotionButtonScale = buttonSize  / buttonTexture[whiteKnight].getSize().x;
    for(int i=0; i < button.size(); i++)
    {
        buttonSprite[button[i]].setPosition(allButtosXPosition + i * (buttonSize + buttonSpace), buttonYPosition);
        buttonSprite[button[i]].setScale(promotionButtonScale, promotionButtonScale);
    }
}

void Menu::locateMenuButtons(std::vector<Button> button)
{
    for (int i = 0; i < button.size(); i++)
        buttonSprite[button[i]].setOrigin(300.0f, 62.0f);
    float buttonWidth  = globalType::windowHeight / 3;
    float buttonHeight =  buttonWidth / 5;
    float buttonsSpace =  buttonHeight;
    float allButtosHeight = (button.size() - 1) * (buttonHeight + buttonsSpace);
    float buttonXPosition = globalType::windowWidth / 2.0f;
    float allButtosYPosition = globalType::windowHeight / 2.0f - allButtosHeight / 2.0f;
    buttonScaleX = buttonWidth  / buttonTexture[goBack].getSize().x;
    buttonScaleY = buttonHeight / buttonTexture[goBack].getSize().y;
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
void Menu::updateMenuButtons(std::vector<Button> button, float scaleX, float scaleY)
{
    for (int i = 0; i < button.size(); i++)
    {
        if(button[i] == notationSaved && isNotationSaved)
            continue;
        sf::FloatRect buttonBounds = buttonSprite[button[i]].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            buttonSprite[button[i]].setScale(scaleX * 1.15f, scaleY * 1.15f);
        else
            buttonSprite[button[i]].setScale(scaleX, scaleY);
    }
}
void Menu::drawMenu(std::vector<Button> button, bool gameBackground, std::string note)
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
    if(note != "")
        drawNote(note);
    globalType::windowPtr->display();
}
    void Menu::drawNote(std::string note)
{
        text.setString(note);
        sf::FloatRect textBounds = text.getGlobalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(globalType::windowWidth / 2, globalType::windowHeight / 6);
        globalType::windowPtr->draw(text);

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



