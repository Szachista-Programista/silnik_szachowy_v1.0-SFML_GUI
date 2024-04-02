#include "Chessboard.h"

Chessboard::Chessboard(bool k): color{k}
{
    chessboard = reversePiecesArrangement(loadPiecesArrangement());
    windowWidth  = static_cast<float>(globalType::windowPtr->getSize().x);
    windowHeight = static_cast<float>(globalType::windowPtr->getSize().y);
    boardSize    = windowHeight * 0.88f;
    marginSize   = windowHeight * 0.05f;
    squareSize   = windowHeight * 0.11f;
    squareScale  = squareSize / 150.0f;
    readTextures();
}
    void Chessboard::readTextures()
{
    readBackgroundTexture();
    readBoardTexture();
    readPieceTextures();
    readUnderlightTextures();
}
        void Chessboard::readBackgroundTexture()
{
    if (!backgroundTexture.loadFromFile("img/other/background.png"))
        std::cerr << "Failed to load texture!" << std::endl;
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);
    background.setScale(windowWidth / background.getLocalBounds().width, windowHeight / background.getLocalBounds().height);
}
        void Chessboard::readBoardTexture()
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
        void Chessboard::readPieceTextures()
{
    for (int i = 0; i < 12; i++)
        if (!pieceTextures[i].loadFromFile("img/pieces/" + std::to_string(i+1) + ".png"))
            std::cerr << "Failed to load piece texture " << i << "!" << std::endl;
    piece.setScale(squareScale, squareScale);
}
        void Chessboard::readUnderlightTextures()
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
    delete[]chessboard;
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
int Chessboard::drawChessboard(bool underlightedCursor)
{
    globalType::windowPtr->clear();
    globalType::windowPtr->draw(background);
    globalType::windowPtr->draw(board);
    drawUnderlight();
    if(underlightedCursor)
        underlightCursorSquare();
    drawPieces();
    globalType::windowPtr->display();
    return getCursorCoords();
}
    void Chessboard::drawUnderlight()
{
    redUnderlight.setScale(squareScale, squareScale);
    redUnderlight.setColor(sf::Color(255, 255, 255, 128));
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(underlightArray[i][j] == 1)
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
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
                piece.setPosition(marginSize + j*squareSize, marginSize + i*squareSize);
                switch(chessboard[i][j])
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
                }
                globalType::windowPtr->draw(piece);
        }
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
        case no:     chessboard[squareCoordY][squareCoordX] = ' ';                        break;
        case pawn:   chessboard[squareCoordY][squareCoordX] = (pieceColor^color)?'P':'p'; break;
        case knight: chessboard[squareCoordY][squareCoordX] = (pieceColor^color)?'N':'n'; break;
        case bishop: chessboard[squareCoordY][squareCoordX] = (pieceColor^color)?'B':'b'; break;
        case rook:   chessboard[squareCoordY][squareCoordX] = (pieceColor^color)?'R':'r'; break;
        case queen:  chessboard[squareCoordY][squareCoordX] = (pieceColor^color)?'Q':'q'; break;
        case king:   chessboard[squareCoordY][squareCoordX] = (pieceColor^color)?'K':'k'; break;
    }
}
    void Chessboard::updateUnderlightArray(int squareCoordX, int squareCoordY, bool underlight)
{
    underlightArray[squareCoordY][squareCoordX] = underlight;
}
void Chessboard::checkWindowSize()
{
    sf::Vector2u windowSize = globalType::windowPtr->getSize();
    if (windowSize.x != globalType::windowWidth || windowSize.y != globalType::windowHeight) {
        globalType::windowPtr->setSize({globalType::windowWidth, globalType::windowHeight});
    }
}



