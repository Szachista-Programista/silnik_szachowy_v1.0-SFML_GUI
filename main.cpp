#include "include/Game.h"

int main() {
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
