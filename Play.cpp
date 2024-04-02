#include "Play.h"

Play::Play(bool k)noexcept:
color{k}, chessboard{k}, engine{k}, notebook{k}
{
    chessboard.drawChessboard(0);
}
void Play::playWithUser()
{
    if(color == false) //engine starts the game
        engineMoveServive(10000);
    while(userMoveServive() && engineMoveServive(userMoveCode)){}
    notationSavingMenu();
}
    bool Play::userMoveServive()
{
    while(true)
    {
        userMoveCode = userSquareChosenCoordinates = chessboard.loadCoordinates();
        currentChessboardUpdateCode = SquareUpdateCode = generateSquareUpdateCode();
        offPreviousEngineMoveUnderlight();
        correcSquareChosen = isChosenUserPiece();

        
        updateChessboard(SquareUpdateCode, true);
        if(!correcSquareChosen)
        {
            updateChessboard(SquareUpdateCode, false);
            continue;
        }
        if(correcSquareChosen)
        {
            userSquareChosenCoordinates = chessboard.loadCoordinates();
            userMoveCode = userMoveCode*100 + userSquareChosenCoordinates;
            currentChessboardUpdateCode += SquareUpdateCode = generateSquareUpdateCode();
            correctMovementMade = engine.canUserMakeSuchMove(userMoveCode);
            updateChessboard(SquareUpdateCode, true);
            if(!correctMovementMade)
            {
                updateChessboard(currentChessboardUpdateCode, false);
                continue;
            }
            if(correctMovementMade)
            {
                if(isUserMakesPromotion())
                {
                    std::vector<std::string> promotionOptions = globalType::getCommuniqueCotent({30,31,32,33});
                    //promotionCode = notice.checkbox(promotionOptions)*10000;
                    //chessboard.deleteCheckbox(220, 60);
                    userMoveCode += promotionCode;
                }
                notebook.generateAndWriteNotation(userMoveCode);
                currentChessboardUpdateCode = notebook.getChessboardUpdateCode();
                updateChessboard(currentChessboardUpdateCode, true);
                previousChessboardUpdateCode = currentChessboardUpdateCode;
                return true;
            }
        }
    }
}
        std::string Play::generateSquareUpdateCode()noexcept
{
    int x     = userSquareChosenCoordinates / 10;
    int y     = userSquareChosenCoordinates % 10;
    char cHar = notebook.currentChessboard[y][x];
    return std::to_string(x) + std::to_string(y) + cHar;
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
        void Play::offPreviousEngineMoveUnderlight()
{
    if(engineMoveUnderlighted == true)
    {
        updateChessboard(previousChessboardUpdateCode, false);
        engineMoveUnderlighted = false;
    }
}
        bool Play::isChosenUserPiece()
{
    int x      = userSquareChosenCoordinates / 10;
    int y      = userSquareChosenCoordinates % 10;
    char piece = notebook.currentChessboard[y][x];
    return (getPieceColor(piece) == color);
}
        bool Play::isUserMakesPromotion()noexcept
{
    int fromX =  userMoveCode/1000;
    int fromY = (userMoveCode/ 100)%10;
    int toY   =  userMoveCode      %10;
    return (notebook.currentChessboard[fromY][fromX] == 'p' && toY == 7);
}
    bool Play::engineMoveServive(int moveCode)
{
    engineMoveCode = engine.makeMove(moveCode);
    notebook.generateAndWriteNotation(engineMoveCode);
    currentChessboardUpdateCode = notebook.getChessboardUpdateCode();
    updateChessboard(previousChessboardUpdateCode, false);
    updateChessboard(currentChessboardUpdateCode, true);
    engineMoveUnderlighted = true;
    previousChessboardUpdateCode = currentChessboardUpdateCode;
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
                //notice.communique(globalType::getCommuniqueCotent({22})[0]);
                break;
            case 2:
                //notice.communique(globalType::getCommuniqueCotent({23})[0]);
                break;
            case 3:
                //notice.communique(globalType::getCommuniqueCotent({24})[0]);
                break;
            case 4:
                //notice.communique(globalType::getCommuniqueCotent({23})[0]);
                break;
            default: throw std::runtime_error("Wrong gameOverParameter.");
        }

    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    //chessboard.deleteCommunique(300);
    return true;
}
    void Play::notationSavingMenu()
{
    //notice.communique(globalType::getCommuniqueCotent({26})[0]);
    //chessboard.deleteCommunique(415);
    try
    {
        switch(notice.checkbox(globalType::getCommuniqueCotent({27,28})))
        {
           case 1:
               //chessboard.deleteCheckbox(210, 33, true);
               //notice.communique(globalType::getCommuniqueCotent({43})[0], 700);
               //notice.communique(notebook.saveGameInNotebook(), 1400);
               //chessboard.deleteCommunique(320);
               break;
           case 2:  break;
           default: throw std::runtime_error("Option selection error.");
        }

    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    //chessboard.deleteCheckbox(210, 33);
}
