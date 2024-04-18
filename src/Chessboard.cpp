#include "../include/Chessboard.h"

Chessboard::Chessboard(bool k): color{k}
{
    loadFonts();
    positions.push_back(reversePiecesArrangement(loadPiecesArrangement()));
    positions.push_back(copyChessboard(positions[0]));
    underlights.push_back(new bool[8][8]{});
    underlights.push_back(copyChessboardUnderlight(underlights[0]));
    boardSize    = globalType::windowHeight * 0.88f;
    marginSize   = globalType::windowHeight * 0.05f;
    squareSize   = globalType::windowHeight * 0.11f;
    squareScale  = squareSize / 150.0f;
    setNotationParameters();
    loadTextures();
}
    void Chessboard::loadFonts()
{
    try
    {
    if (!normalFont.loadFromFile("fonts/arial.ttf"))
        throw std::runtime_error("Cannot load arial.ttf");
    if (!boldFont.loadFromFile("fonts/arial_bold.ttf"))
        throw std::runtime_error("Cannot load arial_bold.ttf");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    void Chessboard::setNotationParameters()
{
    notationWidth = globalType::windowWidth - boardSize - 3 * marginSize;
    notationHeight = 2 * notationWidth;
    notationBackground.setFillColor(sf::Color(138, 138, 138, 150));
    notationBackground.setPosition(boardSize + 2 * marginSize, marginSize);
    notationBackground.setSize(sf::Vector2f(notationWidth, notationHeight));
    normalText.setFont(normalFont);
    boldText.setFont(boldFont);
    normalText.setFillColor(sf::Color::Black);
    boldText.setFillColor(sf::Color::Black);
    normalText.setCharacterSize((int)(globalType::windowHeight/40));
    boldText.setCharacterSize((int)(globalType::windowHeight/40));
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
    try
    {
        if (!backgroundTexture.loadFromFile("img/background/1.png"))
            throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);
    background.setScale(globalType::windowWidth / background.getLocalBounds().width, globalType::windowHeight / background.getLocalBounds().height);
}
        void Chessboard::loadBoardTexture()
{
    try
    {
        if (!boardTexture.loadFromFile("img/board/" + std::to_string(globalType::numberOfBoardTexture) + (color? "/whiteSide.png": "/blackSide.png")))
            throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    board.setTexture(boardTexture);
    board.setPosition(marginSize, marginSize);
    board.setScale(boardSize / boardTexture.getSize().x,  boardSize / boardTexture.getSize().y);
}
        void Chessboard::loadPieceTextures()
{
    try
    {
        for (int i = 0; i < 12; i++)
            if (!pieceTextures[i].loadFromFile("img/pieces/" + std::to_string(i+1) + ".png"))
                throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    piece.setScale(squareScale, squareScale);
}
        void Chessboard::loadUnderlightTextures()
{
    try
    {
    if (!redUnderlightTexture.loadFromFile("img/pieces/red.png"))
        throw std::runtime_error("Cannot read texture.");
    if (!blueUnderlightTexture.loadFromFile("img/pieces/blue.png"))
        throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    redUnderlight.setTexture(redUnderlightTexture);
    blueUnderlight.setTexture(blueUnderlightTexture);
    redUnderlight.setScale(squareScale, squareScale);
    blueUnderlight.setScale(squareScale, squareScale);
}
        void Chessboard::loadButtonsTextures()
{
    try
    {
        if((!arrowButtonTextures[0].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/endLeftArrow.png"))
        || (!arrowButtonTextures[1].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/leftArrow.png"))
        || (!arrowButtonTextures[2].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/rightArrow.png"))
        || (!arrowButtonTextures[3].loadFromFile("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/endRightArrow.png"))
        || (!menuButtonTexture.loadFromFile     ("img/buttons/" + std::to_string(globalType::numberOfButtonTexture) + "/menu.png")))
            throw std::runtime_error("Cannot read texture.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }

    arrowButtonScale = notationWidth * 0.2f / arrowButtonTextures[0].getSize().x;
    for(int i = 0; i < 4; i++)
    {
        arrowButton[i].setTexture(arrowButtonTextures[i]);
        arrowButton[i].setScale(arrowButtonScale, arrowButtonScale);
        arrowButton[i].setOrigin(50.0f, 50.0f);
        float arrowButtonPositionX = notationBackground.getPosition().x + notationWidth * (0.125f + 0.25f * (float)i);
        float arrowButtonPositionY = notationBackground.getPosition().y + notationHeight + notationWidth * 0.2f;
        arrowButton[i].setPosition(arrowButtonPositionX, arrowButtonPositionY);
    }
    menuButton.setTexture(menuButtonTexture);
    menuButtonScaleX = notationWidth / menuButtonTexture.getSize().x;
    menuButtonScaleY = notationWidth * 0.2f / menuButtonTexture.getSize().y;
    menuButton.setScale(menuButtonScaleX, menuButtonScaleY);
    menuButton.setOrigin(300.0f, 62.0f);
    float menuButtonPositionX = notationBackground.getPosition().x + notationWidth * 0.5f;
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
        reading.open("resources/chessboard.txt");
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
    }
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
void Chessboard::saveGameInNotebook()
{
    auto now = std::chrono::system_clock::now();
    time_t moment_t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream streamOut;
    streamOut << std::put_time(localtime(&moment_t), " %Y-%m-%d %H;%M;%S");
    std::string fileName = "game notation" + streamOut.str();
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
bool Chessboard::displayPastMovements(int numberOfMove, bool afterGame)
{
    int action;
    while(true)
    {
        action = getUserAction(numberOfMove);
        if(action == -1)
            return true;
        else if(action == 80)
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
            return false;
        }
        else if(action == 84 && afterGame)
            return false;
        if(numberOfMove == positions.size() -1 && !afterGame)
            return false;
    }
}

