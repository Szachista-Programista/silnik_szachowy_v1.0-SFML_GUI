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
int Chessboard::loadCoordinates()
{
    while (globalType::windowPtr->isOpen())
    {
        checkWindowSize();
        sf::Event event;
        drawChessboard(1);
        while (globalType::windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
                return drawChessboard(1);
        }
    }
}
int Chessboard::drawChessboard(bool underlightedCursor, int positionNumber)
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
    return getCursorCoords();
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
    int  Chessboard::getCursorCoords()
{
    sf::Vector2f cursorPosition = globalType::windowPtr->mapPixelToCoords(sf::Mouse::getPosition(*(globalType::windowPtr)));
    if(marginSize < cursorPosition.x && cursorPosition.x < marginSize + boardSize && marginSize < cursorPosition.y && cursorPosition.y < marginSize + boardSize)
    {
        int cursorSquareCoordX = 7 - int((cursorPosition.x - marginSize)/squareSize);
        int cursorSquareCoordY = 7 - int((cursorPosition.y - marginSize)/squareSize);
        return cursorSquareCoordX *10 + cursorSquareCoordY;
    }
    else
        return 99;
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
    if (windowSize.x != globalType::windowWidth || windowSize.y != globalType::windowHeight) {
        globalType::windowPtr->setSize({globalType::windowWidth, globalType::windowHeight});
    }
}
int Chessboard::promotionMenu()
{
    sf::Sprite buttons[4];
    loadPromotionMenuTextures(buttons);
    locatePromotionMenuTextures(buttons);
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
                updatePromotionMenuButtons(buttons);
            if (event.type == sf::Event::MouseButtonPressed)
            {
                for (int i = 0; i < 4; i++)
                {
                    sf::FloatRect buttonBounds = buttons[i].getGlobalBounds();
                    if (buttonBounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        return i+1;
                }
            }
        }
        drawPromotionMenu(buttons);
    }
}
    void Chessboard::loadPromotionMenuTextures(sf::Sprite buttons[])
{
    for (int i = 0; i < 4; i++)
        buttons[i].setTexture(color? pieceTextures[i+1]: pieceTextures[i+7]);
}
    void Chessboard::locatePromotionMenuTextures(sf::Sprite buttons[])
{
    for (int i = 0; i < 4; i++)
        buttons[i].setOrigin(buttons[i].getGlobalBounds().width / 2.0f, buttons[i].getGlobalBounds().height / 2.0f);
    float buttonSize  = squareSize * 1.5f;
    float buttonsSpace =  squareSize * 0.2f;
    float allButtosWidth = 3.0f * buttonSize + 3.0f * buttonsSpace;
    float allButtosXPosition = windowWidth / 2.0f - allButtosWidth / 2.0f;
    float buttonYPosition = windowHeight / 2.0f;
    buttonScale = buttonSize  / pieceTextures[0].getSize().x * static_cast<float>(globalType::windowWidth)  / windowWidth;

    for(int i=0; i<4; i++)
    {
        buttons[i].setPosition(allButtosXPosition + i * (buttonSize + buttonsSpace), buttonYPosition);
        buttons[i].setScale(buttonScale, buttonScale);
    }
}
    void Chessboard::updatePromotionMenuButtons(sf::Sprite buttons[])
{
    for (int i = 0; i < 4; i++) {
        sf::FloatRect buttonBounds = buttons[i].getGlobalBounds();
        if (buttonBounds.contains(sf::Mouse::getPosition(*(globalType::windowPtr)).x, sf::Mouse::getPosition(*(globalType::windowPtr)).y))
            buttons[i].setScale(buttonScale * 1.15f, buttonScale * 1.15f);
        else
            buttons[i].setScale(buttonScale, buttonScale);

    }
}
    void Chessboard::drawPromotionMenu(sf::Sprite buttons[])
{
    showingPositionNumber = 0;
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    globalType::windowPtr->draw(board);
    drawPieces();
    drawNotation();
    drawOverlay();
    for (int i = 0; i < 4; i++)
        globalType::windowPtr->draw(buttons[i]);
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



