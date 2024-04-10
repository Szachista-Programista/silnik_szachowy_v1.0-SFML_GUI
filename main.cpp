#include "Game.h"

int main() {
    try
    {
        Game game(1000, 750);
        game.run();
    }
    catch(globalType::errorType &e)
    {
        std::cout<<e.errorMessage;
        systemInfo::getChar();
    }
    return 0;
}
