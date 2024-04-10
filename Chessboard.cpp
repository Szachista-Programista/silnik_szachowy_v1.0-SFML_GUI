#include "Chessboard.h"

Chessboard::Chessboard(bool k): color{k}
{
    loadFonts();
    positions.push_back(reversePiecesArrangement(loadPiecesArrangement()));
    positions.push_back(copyChessboard(positions[0]));
    underlights.push_back(new bool[8][8]{});
    underlights.push_back(copyChessboardUnderlight(underlights[0]));
    windowWidth  = static_cast<float>(globalType::windowPtr->getSize().x);
    windowHeight = static_cast<float>(globalType::windowPtr->getSize().y);
    boardSize    = windowHeight * 0.88f;
    marginSize   = windowHeight * 0.05f;
    squareSize   = windowHeight * 0.11f;
    squareScale  = squareSize / 150.0f;
    setNotationParameters();
    loadTextures();
}
    void Chessboard::loadFonts()
{
    if (!normalFont.loadFromFile("fonts/arial.ttf"))
        std::cerr << "Cannot load arial.ttf" << std::endl;
    if (!boldFont.loadFromFile("fonts/arial_bold.ttf"))
        std::cerr << "Cannot load arial_bold.ttf" << std::endl;
}
    void Chessboard::setNotationParameters()
{
    notationWidth = windowWidth - boardSize - 3 * marginSize;
    notationHeight = 2 * notationWidth;
    notationBackground.setFillColor(sf::Color(138, 138, 138, 150));
    notationBackground.setPosition(boardSize + 2 * marginSize, marginSize);
    notationBackground.setSize(sf::Vector2f(notationWidth, notationHeight));
    normalText.setFont(normalFont);
    boldText.setFont(boldFont);
    normalText.setFillColor(sf::Color::Black);
    boldText.setFillColor(sf::Color::Black);
    normalText.setCharacterSize((int)(windowHeight/40));
    boldText.setCharacterSize((int)(windowHeight/40));
}
    void Chessboard::loadTextures()
{
    loadBackgroundTexture();
    loadBoardTexture();
    loadPieceTextures();
    loadUnderlightTextures();
    loadButtonsTextures();
}
        void Chessboard::loadBackgroundTexture()
{
    if (!backgroundTexture.loadFromFile("img/other/background.png"))
        std::cerr << "Failed to load texture!" << std::endl;
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);
    background.setScale(windowWidth / background.getLocalBounds().width, windowHeight / background.getLocalBounds().height);
}
        void Chessboard::loadBoardTexture()
{
    if(color)
    {
        if (!boardTexture.loadFromFile("img/other/whiteSideBoard.png"))
            std::cerr << "Failed to load chessboard texture!" << std::endl;
    }
    else
    {
        if (!boardTexture.loadFromFile("img/other/blackSideBoard.png"))
            std::cerr << "Failed to load chessboard texture!" << std::endl;
    }
    board.setTexture(boardTexture);
    board.setPosition(marginSize, marginSize);
    board.setScale(boardSize / boardTexture.getSize().x,  boardSize / boardTexture.getSize().y);
}
        void Chessboard::loadPieceTextures()
{
    for (int i = 0; i < 12; i++)
        if (!pieceTextures[i].loadFromFile("img/pieces/" + std::to_string(i+1) + ".png"))
            std::cerr << "Failed to load piece texture " << i << "!" << std::endl;
    piece.setScale(squareScale, squareScale);
}
        void Chessboard::loadUnderlightTextures()
{
    if (!redUnderlightTexture.loadFromFile("img/pieces/red.png"))
        std::cerr << "Failed to load chessboard texture!" << std::endl;
    if (!blueUnderlightTexture.loadFromFile("img/pieces/blue.png"))
        std::cerr << "Failed to load chessboard texture!" << std::endl;
    redUnderlight.setTexture(redUnderlightTexture);
    blueUnderlight.setTexture(blueUnderlightTexture);
    redUnderlight.setScale(squareScale, squareScale);
    blueUnderlight.setScale(squareScale, squareScale);
}
        void Chessboard::loadButtonsTextures()
{
    if (!arrowButtonTextures[0].loadFromFile("img/buttons/endLeftArrowButton.png"))
        std::cerr << "Failed to load texture!" << std::endl;
    if (!arrowButtonTextures[1].loadFromFile("img/buttons/leftArrowButton.png"))
        std::cerr << "Failed to load texture!" << std::endl;
    if (!arrowButtonTextures[2].loadFromFile("img/buttons/rightArrowButton.png"))
        std::cerr << "Failed to load texture!" << std::endl;
    if (!arrowButtonTextures[3].loadFromFile("img/buttons/endRightArrowButton.png"))
        std::cerr << "Failed to load texture!" << std::endl;
    if (!menuButtonTexture.loadFromFile("img/buttons/menuButton.png"))
        std::cerr << "Failed to load texture!" << std::endl;

    arrowButtonScale = notationWidth * 0.2f / arrowButtonTextures[0].getSize().x;
    for(int i = 0; i < 4; i++)
    {
        arrowButton[i].setTexture(arrowButtonTextures[i]);
        arrowButton[i].setScale(arrowButtonScale, arrowButtonScale);
        arrowButton[i].setOrigin(arrowButton[i].getGlobalBounds().width / 2.0f, arrowButton[i].getGlobalBounds().height / 2.0f);
        float arrowButtonPositionX = notationBackground.getPosition().x + notationWidth * (0.125f + 0.25f * (float)i);
        float arrowButtonPositionY = notationBackground.getPosition().y + notationHeight + notationWidth * 0.125f;
        arrowButton[i].setPosition(arrowButtonPositionX, arrowButtonPositionY);
    }
    menuButton.setTexture(menuButtonTexture);
    menuButtonScaleX = notationWidth * 0.95f / menuButtonTexture.getSize().x;
    menuButtonScaleY = notationWidth * 0.2f / menuButtonTexture.getSize().y;
    menuButton.setScale(menuButtonScaleX, menuButtonScaleY);
    menuButton.setOrigin(menuButton.getGlobalBounds().width / 2.0f, menuButton.getGlobalBounds().height / 2.0f);
    float menuButtonPositionX = notationBackground.getPosition().x + notationWidth * 0.625f;
    float menuButtonPositionY = notationBackground.getPosition().y + notationHeight + notationWidth * 0.500f;
    menuButton.setPosition(menuButtonPositionX, menuButtonPositionY);
}
    globalType::chessboardPointer Chessboard::loadPiecesArrangement()
{
    std::ifstream reading;
    std::string line;
    globalType::chessboardPointer chessboard;
    try
    {
        chessboard = new char[8][8];
    }
    catch(const std::bad_alloc &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    try
    {
        reading.open("chessboard.txt");
        if (!reading.is_open())
            throw std::ifstream::failure("The file 'chessboard.txt' cannot be opened .");

        for(int i=0; i<8; i++)
        {
            if (!getline(reading, line))
                throw std::ifstream::failure("Error reading character from 'chessboard.txt' file .");
            for(int j=0; j<8; j++)
                if(line[j] == '*')
                    chessboard[i][j] = ' ';
                else if(line[j] == '.')
                {
                    if(i==0)
                    {
                        if(j==3)
                            chessboard[i][j] = color?'k':'q';
                        if(j==4)
                            chessboard[i][j] = color?'q':'k';
                    }
                    if(i==7)
                    {
                        if(j==3)
                            chessboard[i][j] = color?'K':'Q';
                        if(j==4)
                            chessboard[i][j] = color?'Q':'K';
                    }
                }
                else
                    chessboard[i][j] = line[j];
        }

    }
    catch(const std::ifstream::failure &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    reading.close();
    return chessboard;
}
    globalType::chessboardPointer Chessboard::reversePiecesArrangement(globalType::chessboardPointer chessboard)
{
    globalType::chessboardPointer reversedChessboard;
    try
    {
        reversedChessboard = new char[8][8];
    }
    catch(const std::bad_alloc &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    for(int i = 0, m = 7; i < 8; i++, m--)
        for(int j = 0, n = 7; j < 8; j++, n--)
            reversedChessboard[i][j] = chessboard[m][n];
    delete[]chessboard;
    return reversedChessboard;
}
Chessboard::~Chessboard()
{
    deletePositions();
    deleteUnderlights();
}
    void Chessboard::deletePositions()
{
    for(auto element: positions)
        delete[]element;
}
    void Chessboard::deleteUnderlights()
{
    for(auto element: underlights)
        delete[]element;
}


int Chessboard::getUserAction(int positionNumber)
{
    while (globalType::windowPtr->isOpen())
    {
        updateButtons();
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return -1;
            }
            if (event.type == sf::Event::MouseMoved)
                updateButtons();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int action = getMousePressActionCode();
                if(action == 99)
                    continue;
                else
                    return action;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return 84;
        }
        drawChessboard(positionNumber? false: true, positionNumber);
    }
}
    void Chessboard::updateButtons()
{
    sf::FloatRect buttonBounds;
    for (int i = 0; i < 4; i++)
    {
        buttonBounds = arrowButton[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            arrowButton[i].setScale(arrowButtonScale * 1.15f, arrowButtonScale * 1.15f);
        else
            arrowButton[i].setScale(arrowButtonScale, arrowButtonScale);
    }
    buttonBounds = menuButton.getGlobalBounds();
    if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
        menuButton.setScale(menuButtonScaleX * 1.15f, arrowButtonScale * 1.15f);
    else
        menuButton.setScale(menuButtonScaleX, menuButtonScaleY);
}
    int  Chessboard::getMousePressActionCode()
{
    sf::FloatRect buttonBounds;
    buttonBounds =  board.getGlobalBounds();
    if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
        return getPressedSquareCoords();
    buttonBounds =  menuButton.getGlobalBounds();
    if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
        return 84;
    for(int i = 0; i < 4; i++)
    {
        buttonBounds = arrowButton[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            return 80 + i;
    }
    return 99;
}
        int  Chessboard::getPressedSquareCoords()
{
    sf::Vector2f cursorPosition = globalType::windowPtr->mapPixelToCoords(sf::Mouse::getPosition(*(globalType::windowPtr)));
    if(marginSize < cursorPosition.x && cursorPosition.x < marginSize + boardSize && marginSize < cursorPosition.y && cursorPosition.y < marginSize + boardSize)
    {
        int cursorSquareCoordX = 7 - int((cursorPosition.x - marginSize)/squareSize);
        int cursorSquareCoordY = 7 - int((cursorPosition.y - marginSize)/squareSize);
        return cursorSquareCoordX *10 + cursorSquareCoordY;
    }
}


void Chessboard::drawChessboard(bool underlightedCursor, int positionNumber)
{
    showingPositionNumber = positionNumber;
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    globalType::windowPtr->draw(board);
    drawUnderlight();
    if(underlightedCursor)
        underlightCursorSquare();
    drawPieces();
    drawNotation();
    globalType::windowPtr->display();
}
    void Chessboard::drawUnderlight()
{
    redUnderlight.setScale(squareScale, squareScale);
    redUnderlight.setColor(sf::Color(255, 255, 255, 128));
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(underlights[showingPositionNumber][i][j] == 1)
            {
                redUnderlight.setPosition(marginSize + j*squareSize, marginSize + i*squareSize);
                globalType::windowPtr->draw(redUnderlight);
            }
}
    void Chessboard::underlightCursorSquare()
{
    sf::Vector2f cursorPosition = globalType::windowPtr->mapPixelToCoords(sf::Mouse::getPosition(*(globalType::windowPtr)));
    blueUnderlight.setScale(squareScale, squareScale);
    blueUnderlight.setColor(sf::Color(255, 255, 255, 128));
    if(marginSize < cursorPosition.x && cursorPosition.x < marginSize + boardSize && marginSize < cursorPosition.y && cursorPosition.y < marginSize + boardSize)
    {
        int cursorSquareCoordX ((cursorPosition.x - marginSize)/squareSize);
        int cursorSquareCoordY ((cursorPosition.y - marginSize)/squareSize);
        blueUnderlight.setPosition(marginSize + cursorSquareCoordX*squareSize, marginSize + cursorSquareCoordY*squareSize);
        globalType::windowPtr->draw(blueUnderlight);
    }
}
    void Chessboard::drawPieces()
{
    try
    {
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
            {
                    piece.setPosition(marginSize + j*squareSize, marginSize + i*squareSize);
                    switch(positions[showingPositionNumber][i][j])
                    {
                        case ' ': continue;
                        case 'p': piece.setTexture(pieceTextures[color?0: 6]); break;
                        case 'n': piece.setTexture(pieceTextures[color?1: 7]); break;
                        case 'b': piece.setTexture(pieceTextures[color?2: 8]); break;
                        case 'r': piece.setTexture(pieceTextures[color?3: 9]); break;
                        case 'q': piece.setTexture(pieceTextures[color?4:10]); break;
                        case 'k': piece.setTexture(pieceTextures[color?5:11]); break;
                        case 'P': piece.setTexture(pieceTextures[color?6: 0]); break;
                        case 'N': piece.setTexture(pieceTextures[color?7: 1]); break;
                        case 'B': piece.setTexture(pieceTextures[color?8: 2]); break;
                        case 'R': piece.setTexture(pieceTextures[color?9: 3]); break;
                        case 'Q': piece.setTexture(pieceTextures[color?10:4]); break;
                        case 'K': piece.setTexture(pieceTextures[color?11:5]); break;
                        default: throw std::runtime_error("Wrong char.");
                    }
                    globalType::windowPtr->draw(piece);
            }
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    void Chessboard::drawNotation()
{
    globalType::windowPtr->draw(notationBackground);
    for(int i =0; i < 4; i++)
        globalType::windowPtr->draw(arrowButton[i]);
    globalType::windowPtr->draw(menuButton);
    drawNotationContent();
}
        void Chessboard::drawNotationContent()
{
    float firstColumnX  = notationBackground.getPosition().x + notationWidth  * 0.1f;
    float secondColumnX = notationBackground.getPosition().x + notationWidth  * 0.3f;
    float thirdColumnX  = notationBackground.getPosition().x + notationWidth  * 0.6f;

    float contentCoordY = notationBackground.getPosition().y + notationHeight * 0.05f;
    float linesSpace    = notationHeight / 22.0f;

    std::string content;
    int numberOfSemiMoves = (showingPositionNumber == 0)? notation.size(): showingPositionNumber - 1;
    int numberOfLines = (numberOfSemiMoves + 1) / 2;
    int firstDisplaiedLine = (20 < numberOfLines)? (numberOfLines - 20): (0);

    for(int x = 0, i = firstDisplaiedLine;  i < numberOfLines; x++, i++)
    {
        normalText.setPosition(firstColumnX, contentCoordY + linesSpace*x);
        normalText.setString(((i<9)? "  ": "") + std::to_string(i+1) + '.');
        globalType::windowPtr->draw(normalText);

        if(i*2 + 1 != numberOfSemiMoves)
        {
            normalText.setPosition(secondColumnX, contentCoordY + linesSpace*x);
            normalText.setString(notation[i*2]);
            globalType::windowPtr->draw(normalText);
        }
        else
        {
            boldText.setPosition(secondColumnX, contentCoordY + linesSpace*x);
            boldText.setString(notation[i*2]);
            globalType::windowPtr->draw(boldText);
        }
        if(i*2 + 2 != numberOfSemiMoves)
        {
            normalText.setPosition(thirdColumnX, contentCoordY + linesSpace*x);
            normalText.setString(((i*2+1 < numberOfSemiMoves)? notation[i*2 + 1]: ""));
            globalType::windowPtr->draw(normalText);
        }
        else
        {
            boldText.setPosition(thirdColumnX, contentCoordY + linesSpace*x);
            boldText.setString(((i*2+1 < numberOfSemiMoves)? notation[i*2 + 1]: ""));
            globalType::windowPtr->draw(boldText);
        }
    }       // content += ((i<9)? "  ": "") + std::to_string(i+1) + ".      " + notation[i * 2] + "      " + ((i*2+1 < numberOfSemiMoves)? notation[i*2+1]: "") + '\n';

}


void Chessboard::updateSquare(int squareCoordX, int squareCoordY, int piece, bool pieceColor, bool underlight)
{
    try
    {
        if(squareCoordX<0 || 7<squareCoordX || squareCoordY<0 || 7<squareCoordY)
            throw std::invalid_argument("Wrong coordinates.");
        if(piece<0 || 6<piece || squareCoordY<0 || 7<squareCoordY)
            throw std::invalid_argument("Wrong piece.");
    }
    catch(const std::invalid_argument &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    updateChessboard(squareCoordX, squareCoordY, piece, pieceColor);
    updateUnderlightArray(squareCoordX, squareCoordY, underlight);
}
    void Chessboard::updateChessboard(int squareCoordX, int squareCoordY, int piece, bool pieceColor)
{
    switch(piece)
    {
        case no:     positions[0][squareCoordY][squareCoordX] = ' ';                        break;
        case pawn:   positions[0][squareCoordY][squareCoordX] = (pieceColor^color)?'P':'p'; break;
        case knight: positions[0][squareCoordY][squareCoordX] = (pieceColor^color)?'N':'n'; break;
        case bishop: positions[0][squareCoordY][squareCoordX] = (pieceColor^color)?'B':'b'; break;
        case rook:   positions[0][squareCoordY][squareCoordX] = (pieceColor^color)?'R':'r'; break;
        case queen:  positions[0][squareCoordY][squareCoordX] = (pieceColor^color)?'Q':'q'; break;
        case king:   positions[0][squareCoordY][squareCoordX] = (pieceColor^color)?'K':'k'; break;
    }
}
    void Chessboard::updateUnderlightArray(int squareCoordX, int squareCoordY, bool underlight)
{
    underlights[0][squareCoordY][squareCoordX] = underlight;
}
void Chessboard::offUnderlights()
{
    delete[]underlights[0];
    underlights[0] = new bool[8][8]{};
}
void Chessboard::underlight(int coordonates)
{
    int x = 7 - coordonates / 10;
    int y = 7 - coordonates % 10;
    underlights[0][y][x] = true;
}
void Chessboard::checkWindowSize()
{
    sf::Vector2u windowSize = globalType::windowPtr->getSize();
    if (windowSize.x != globalType::currentWindowWidth || windowSize.y != globalType::currentWindowHeight) {
        globalType::windowPtr->setSize({globalType::currentWindowWidth, globalType::currentWindowHeight});
    }
}


int Chessboard::promotionMenu()
{
    sf::Sprite button[promotionMenuButtons];
    loadPromotionMenuTextures(button);
    locatePromotionMenuTextures(button);
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
                updatePromotionMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed)
                for (int i = 0; i < promotionMenuButtons; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        return i+1;
                }
        }
        drawPromotionMenu(button);
    }
}
    void Chessboard::loadPromotionMenuTextures(sf::Sprite button[])
{
    for (int i = 0; i < promotionMenuButtons; i++)
        button[i].setTexture(color? pieceTextures[i+1]: pieceTextures[i+7]);
}
    void Chessboard::locatePromotionMenuTextures(sf::Sprite button[])
{
    for (int i = 0; i < promotionMenuButtons; i++)
        button[i].setOrigin(button[i].getGlobalBounds().width / 2.0f, button[i].getGlobalBounds().height / 2.0f);
    float buttonSize  = squareSize * 1.5f;
    float buttonSpace =  squareSize * 0.2f;
    float allButtosWidth = 3.0f * buttonSize + 3.0f * buttonSpace;
    float allButtosXPosition = windowWidth / 2.0f - allButtosWidth / 2.0f;
    float buttonYPosition = windowHeight / 2.0f;
    promotionMenuButtonScale = buttonSize  / pieceTextures[0].getSize().x /** static_cast<float>(globalType::windowWidth)  / windowWidth*/;

    for(int i=0; i<promotionMenuButtons; i++)
    {
        button[i].setPosition(allButtosXPosition + i * (buttonSize + buttonSpace), buttonYPosition);
        button[i].setScale(promotionMenuButtonScale, promotionMenuButtonScale);
    }
}
    void Chessboard::updatePromotionMenuButtons(sf::Sprite button[])
{
    for (int i = 0; i < promotionMenuButtons; i++) {
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            button[i].setScale(promotionMenuButtonScale * 1.15f, promotionMenuButtonScale * 1.15f);
        else
            button[i].setScale(promotionMenuButtonScale, promotionMenuButtonScale);

    }
}
    void Chessboard::drawPromotionMenu(sf::Sprite button[])
{
    showingPositionNumber = 0;
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    globalType::windowPtr->draw(board);
    drawPieces();
    drawNotation();
    drawOverlay();
    for (int i = 0; i < promotionMenuButtons; i++)
        globalType::windowPtr->draw(button[i]);
    globalType::windowPtr->display();
}
        void Chessboard::drawOverlay()
{
    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setFillColor(sf::Color(160, 130, 100, 150));
    globalType::windowPtr->draw(overlay);
}


void Chessboard::savePosition()
{
    positions.push_back(copyChessboard(positions[0]));
    underlights.push_back(copyChessboardUnderlight(underlights[0]));
}
globalType::chessboardPointer Chessboard::copyChessboard(const globalType::chessboardPointer oryginal)
{
    try
    {
        if (oryginal == nullptr)
            throw std::invalid_argument("Attempting to copy the nullptr address of the chessboard.");
    }
    catch(const std::invalid_argument &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    globalType::chessboardPointer cOpy;
    try
    {
        cOpy = new char[8][8];
    }
    catch(const std::bad_alloc &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            cOpy[i][j] = oryginal[i][j];
    return cOpy;
}
globalType::chessboardUnderlightPointer Chessboard::copyChessboardUnderlight(const globalType::chessboardUnderlightPointer oryginal)
{
    try
    {
        if (oryginal == nullptr)
            throw std::invalid_argument("Attempting to copy the nullptr address of the chessboardUnderlight.");
    }
    catch(const std::invalid_argument &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    globalType::chessboardUnderlightPointer cOpy;
    try
    {
        cOpy = new bool[8][8];
    }
    catch(const std::bad_alloc &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            cOpy[i][j] = oryginal[i][j];
    return cOpy;
}


void Chessboard::gameOverMenu(globalType::GameResult gameResult)
{
    sf::Texture buttonTexture[gameOverMenuButtons+1];
    sf::Sprite button[gameOverMenuButtons+1];
    loadGameOverMenuButtons(buttonTexture, button);
    locateGameOverMenuButtons(buttonTexture, button);
    while (globalType::windowPtr->isOpen())
    {
        updateGameOverMenuButtons(button);
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return;
            }
            if (event.type == sf::Event::MouseMoved)
                updateGameOverMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed)
                for (int i = 0; i < gameOverMenuButtons; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return;
                            case 1:
                                if( ! notationSaved)
                                {
                                    button[1].setTexture(buttonTexture[4]);
                                    button[1].setScale(menuButtonsScaleX, menuButtonsScaleY);
                                    button[1].setColor(sf::Color(0,255,0,255));
                                    saveGameInNotebook();
                                    notationSaved = true;
                                }
                                break;
                            case 2:
                                displayPastMovements(positions.size()-1, true);
                                break;
                            case 3:
                                globalType::windowPtr->close();
                                return;
                        }
                }
        }
        drawGameOverMenu(button);
    }
}
    void Chessboard::loadGameOverMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    if (!buttonTexture[0].loadFromFile("img/buttons/mainMenuButton.png"))
        {}//return EXIT_FAILURE;
    button[0].setTexture(buttonTexture[0]);
    if (!buttonTexture[1].loadFromFile("img/buttons/saveNotationButton.png"))
        {}//return EXIT_FAILURE;
    button[1].setTexture(buttonTexture[1]);
    if (!buttonTexture[2].loadFromFile("img/buttons/watchPlayedGameButton.png"))
        {}//return EXIT_FAILURE;
    button[2].setTexture(buttonTexture[2]);
    if (!buttonTexture[3].loadFromFile("img/buttons/exitButton.png"))
        {}//return EXIT_FAILURE;
    button[3].setTexture(buttonTexture[3]);
    if (!buttonTexture[4].loadFromFile("img/buttons/notationSavedButton.png"))
        {}//return EXIT_FAILURE;
    //button[4].setTexture(buttonTexture[4]);
}
    void Chessboard::locateGameOverMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    for (int i = 0; i < gameOverMenuButtons; i++)
        button[i].setOrigin(button[i].getGlobalBounds().width / 2.0f, button[i].getGlobalBounds().height / 2.0f);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonSpace =  50.0f;
    float allButtosHeight = 3.0f * buttonHeight + 3.0f * buttonSpace;
    float buttonXPosition = windowWidth / 2.0f;
    float allButtosYPosition = windowHeight / 2.0f - allButtosHeight / 2.0f;
    menuButtonsScaleX = buttonWidth  / buttonTexture[0].getSize().x;
    menuButtonsScaleY = buttonHeight / buttonTexture[0].getSize().y;
    for(int i=0; i<gameOverMenuButtons; i++)
    {
        button[i].setPosition(buttonXPosition, allButtosYPosition + i * (buttonHeight + buttonSpace));
        button[i].setScale(menuButtonsScaleX, menuButtonsScaleY);
    }
}
    void Chessboard::updateGameOverMenuButtons(sf::Sprite button[])
{
    for (int i = 0; i < gameOverMenuButtons; i++)
    {
        if(i == 1 && notationSaved)
            continue;
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            button[i].setScale(menuButtonsScaleX * 1.15f, menuButtonsScaleY * 1.15f);
        else
            button[i].setScale(menuButtonsScaleX, menuButtonsScaleY);
    }
}
    void Chessboard::drawGameOverMenu(sf::Sprite button[])
{
    showingPositionNumber = 0;
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    globalType::windowPtr->draw(board);
    drawPieces();
    drawNotation();
    drawOverlay();
    for (int i = 0; i < gameOverMenuButtons; i++)
        globalType::windowPtr->draw(button[i]);
    globalType::windowPtr->display();
}
    void Chessboard::saveGameInNotebook()
{
    auto now = std::chrono::system_clock::now();
    time_t moment_t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream streamOut;
    streamOut << std::put_time(localtime(&moment_t), " %Y-%m-%d %H;%M;%S");
    std::string fileName = globalType::getCommuniqueCotent({44})[0] + streamOut.str();
    std::ofstream file("saved notations/" + fileName + ".txt");
    try
    {
        if (!file.is_open())
            throw std::ofstream::failure("The file could not be opened for writing.");
    }
    catch(const std::ofstream::failure &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    file<<std::put_time(localtime(&moment_t), ">>> %Y-%m-%d %H:%M:%S <<<")<<std::endl;
    file<<"==========================="<<std::endl;
    for(int i = 1, x = 0;; i++)
    {
        file<<((i < 10)? " ": "")<<i<<".    ";
        if(x < notation.size())
        {
            file<<notation[x]<<"    ";
            x++;
        }
        else
            break;
        if(x < notation.size())
        {
            file<<notation[x]<<std::endl;
            x++;
        }
        else
            break;
    }
    file.close();
}

bool Chessboard::gameMenu()
{
    sf::Texture buttonTexture[gameMenuButtons+1];
    sf::Sprite button[gameMenuButtons+1];
    loadGameMenuButtons(buttonTexture, button);
    locateGameMenuButtons(buttonTexture, button);
    while (globalType::windowPtr->isOpen())
    {
        updateGameMenuButtons(button);
        checkWindowSize();
        sf::Event event;
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                globalType::windowPtr->close();
                return true;
            }
            if (event.type == sf::Event::MouseMoved)
                updateGameMenuButtons(button);
            if (event.type == sf::Event::MouseButtonPressed)
                for (int i = 0; i < gameMenuButtons; i++)
                {
                    sf::FloatRect buttonBounds = button[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        switch(i)
                        {
                            case 0: return false;
                            case 1: return true;
                            case 2:
                                if( ! notationSaved)
                                {
                                    button[2].setTexture(buttonTexture[4]);
                                    button[2].setScale(menuButtonsScaleX, menuButtonsScaleY);
                                    button[2].setColor(sf::Color(0,255,0,255));
                                    saveGameInNotebook();
                                    notationSaved = true;
                                }
                                break;
                            case 3:
                                globalType::windowPtr->close();
                                return true;
                        }
                }
        }
        drawGameMenu(button);
    }
}
    void Chessboard::loadGameMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{

    if (!buttonTexture[0].loadFromFile("img/buttons/backToGameButton.png"))
        {}//return EXIT_FAILURE;
    button[0].setTexture(buttonTexture[0]);
    if (!buttonTexture[1].loadFromFile("img/buttons/mainMenuButton.png"))
        {}//return EXIT_FAILURE;
    button[1].setTexture(buttonTexture[1]);
    if (!buttonTexture[2].loadFromFile("img/buttons/saveNotationButton.png"))
        {}//return EXIT_FAILURE;
    button[2].setTexture(buttonTexture[2]);
    if (!buttonTexture[3].loadFromFile("img/buttons/exitButton.png"))
        {}//return EXIT_FAILURE;
    button[3].setTexture(buttonTexture[3]);
    if (!buttonTexture[4].loadFromFile("img/buttons/notationSavedButton.png"))
        {}//return EXIT_FAILURE;
    //button[4].setTexture(buttonTexture[4]);
}
    void Chessboard::locateGameMenuButtons(sf::Texture buttonTexture[], sf::Sprite button[])
{
    for (int i = 0; i < gameMenuButtons; i++)
        button[i].setOrigin(button[i].getGlobalBounds().width / 2.0f, button[i].getGlobalBounds().height / 2.0f);
    float buttonWidth  = 250.0f;
    float buttonHeight =  50.0f;
    float buttonSpace =  50.0f;
    float allButtosHeight = 3.0f * buttonHeight + 3.0f * buttonSpace;
    float buttonXPosition = windowWidth / 2.0f;
    float allButtosYPosition = windowHeight / 2.0f - allButtosHeight / 2.0f;
    menuButtonsScaleX = buttonWidth  / buttonTexture[0].getSize().x;
    menuButtonsScaleY = buttonHeight / buttonTexture[0].getSize().y;
    for(int i=0; i<gameMenuButtons; i++)
    {
        button[i].setPosition(buttonXPosition, allButtosYPosition + i * (buttonHeight + buttonSpace));
        button[i].setScale(menuButtonsScaleX, menuButtonsScaleY);
    }
    if(notationSaved)
    {
        button[2].setTexture(buttonTexture[4]);
        button[2].setScale(menuButtonsScaleX, menuButtonsScaleY);
        button[2].setColor(sf::Color(0,255,0,255));
    }
}
    void Chessboard::updateGameMenuButtons(sf::Sprite button[])
{
    for (int i = 0; i < gameMenuButtons; i++)
    {
        if(i == 2 && notationSaved)
            continue;
        sf::FloatRect buttonBounds = button[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            button[i].setScale(menuButtonsScaleX * 1.15f, menuButtonsScaleY * 1.15f);
        else
            button[i].setScale(menuButtonsScaleX, menuButtonsScaleY);
    }
}
    void Chessboard::drawGameMenu(sf::Sprite button[])
{
    showingPositionNumber = 0;
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    globalType::windowPtr->draw(board);
    drawPieces();
    drawNotation();
    drawOverlay();
    for (int i = 0; i < gameMenuButtons; i++)
        globalType::windowPtr->draw(button[i]);
    globalType::windowPtr->display();
}



void Chessboard::displayPastMovements(int numberOfMove, bool afterGame)
{
    int action;
    while(true)
    {
        action = getUserAction(numberOfMove);
        if(action == 80)
            numberOfMove = 1;
        else if(action == 81 && 1 < numberOfMove)
            numberOfMove--;
        else if(action == 82 && numberOfMove < positions.size() -1)
            numberOfMove++;
        else if(action == 83 && numberOfMove < positions.size() -1)
            numberOfMove = positions.size() -1;
        else if(action == 84 && !afterGame)
        {
            menuButtonPressed = true;
            return;
        }
        else if(action == 84 && afterGame)
            return;
        if(numberOfMove == positions.size() -1 && !afterGame)
            return;
    }
}
