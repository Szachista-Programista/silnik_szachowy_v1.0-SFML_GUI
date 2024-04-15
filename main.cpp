#include "Game.h"

int main() {
    globalType::windowHeight = 750;
    globalType::windowWidth  = 1000;
    do
    {
        globalType::windowResized = false;
        Game game;
        try
        { 
            game.run();
        }
        catch(globalType::errorType &e)
        {
            std::cout<<e.errorMessage;
        }        
    }
    while(globalType::windowResized);
    return 0;
}
