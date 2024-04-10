#include "Play.h"

Play::Play(bool k)noexcept:
color{k}, chessboard{k}, engine{k}, notebook{k}
{
    chessboard.drawChessboard();
}
void Play::playWithUser()
{
    if(color == false) //engine starts the game
        engineMoveService(10000);
    while(userMoveService() && engineMoveService(userMoveCode)){}

}
    bool Play::userMoveService()
{
    firstCoordChoosen = false;
    while(true)
    {
        if(gameOver)
            return false;
        if(!firstCoordChoosen)
        {
            if(userActionService())
                if(isChosenUserPiece())
                    firstCoordService();
        }
        else if(userActionService())
        {
            if(isChosenUserPiece())
                firstCoordService();
            else
            {
                userMoveCode = userMoveCode*100 + chosenCoordinates;
                if(engine.canUserMakeSuchMove(userMoveCode))
                {
                    secondCoordService();
                    return true;
                }
                else
                {
                    chessboard.offUnderlights();
                    firstCoordChoosen = false;
                }
            }
        }
    }
}
        bool Play::userActionService()
{
    userActionCode = chessboard.getUserAction();
    if(0 <= userActionCode && userActionCode <= 77)
    {
        chosenCoordinates = userActionCode;
        return true;
    }
    if(80 == userActionCode)
        chessboard.displayPastMovements(1, false);
    if(81 == userActionCode)
        chessboard.displayPastMovements(chessboard.positions.size()-2, false);
    if(userActionCode == 84 || chessboard.menuButtonPressed)
    {
        chessboard.menuButtonPressed = false;
        gameOver = chessboard.gameMenu();
    }
    return false;
}
        bool Play::isChosenUserPiece()
{
    int x      = chosenCoordinates / 10;
    int y      = chosenCoordinates % 10;
    char piece = notebook.currentChessboard[y][x];
    return (getPieceColor(piece) == color);
}
        void Play::firstCoordService()
{
    chessboard.offUnderlights();
    chessboard.underlight(chosenCoordinates);
    userMoveCode = chosenCoordinates;
    firstCoordChoosen = true;
}
        void Play::secondCoordService()
{
    if(isUserMakesPromotion())
        userMoveCode += chessboard.promotionMenu() * 10000;
    chessboard.notation = notebook.getNotation(userMoveCode);
    chessboard.notationSaved = false;
    updateChessboard(notebook.getChessboardUpdateCode(), true);
    chessboard.drawChessboard();
}
            bool Play::isUserMakesPromotion()noexcept
{
    int fromX =  userMoveCode/1000;
    int fromY = (userMoveCode/ 100)%10;
    int toY   =  userMoveCode      %10;
    return (notebook.currentChessboard[fromY][fromX] == 'p' && toY == 7);
}
            void Play::updateChessboard(std::string updateCode, bool underlight)
{
    try
    {
        if(updateCode.size()%3 != 0)
            throw std::invalid_argument("Wrong updateCode.");
    }
    catch(const std::invalid_argument &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    std::string partialUpdateCode;
    int x,y;
    char cHar;
    int piece;
    bool pieceColor;
    while(updateCode.size())
    {
        partialUpdateCode = updateCode.substr(0, 3);
        updateCode.erase(0, 3);

        x = 7 - (partialUpdateCode[0] - '0');
        y = 7 - (partialUpdateCode[1] - '0');
        cHar = partialUpdateCode[2];
        piece = getPieceCode(cHar);
        pieceColor = getPieceColor(cHar);
        chessboard.updateSquare(x, y, piece, pieceColor, underlight);
    }
    chessboard.savePosition();
    //chessboard.drawChessboard(1);
}
                int Play::getPieceCode  (char cHar)
{
    try
    {
        switch(cHar)
        {
            case ' ':           return 0;
            case 'P': case 'p': return 1;
            case 'N': case 'n': return 2;
            case 'B': case 'b': return 3;
            case 'R': case 'r': return 4;
            case 'Q': case 'q': return 5;
            case 'K': case 'k': return 6;
            default: throw std::runtime_error("Wrong char.");
        }
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
                bool Play::getPieceColor(char cHar)
{
    try
    {
        if(isalpha(cHar))
        {
            if(islower(cHar))
                return color;
            if(isupper(cHar))
                return !color;
        }
        else if(cHar == ' ')
            return !color;
        else
            throw std::invalid_argument("Wrong char.");
    }
    catch(const std::invalid_argument &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    bool Play::engineMoveService(int moveCode)
{
    engineMoveCode = engine.makeMove(moveCode);
    chessboard.notation = notebook.getNotation(engineMoveCode);
    chessboard.offUnderlights();
    updateChessboard(notebook.getChessboardUpdateCode(), true);
    return ( ! isItGameover());
}
        bool Play::isItGameover()
{
    int gameOverParameter = engineMoveCode / 100000;
    if(!gameOverParameter)
        return false;
    try
    {
        switch(gameOverParameter)
        {
            case 1:
                chessboard.gameOverMenu(globalType::userWin);   break;
            case 2:
                chessboard.gameOverMenu(globalType::stalemate); break;
            case 3:
                chessboard.gameOverMenu(globalType::engineWin); break;
            case 4:
                chessboard.gameOverMenu(globalType::stalemate); break;
            default: throw std::runtime_error("Wrong gameOverParameter.");
        }
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    return true;
}
