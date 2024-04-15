#include "GlobalDefinitions.h"

namespace globalType{
    double(*userKingBehaviorPoints1)   (double,double);
    double(*engineKnightBehaviorPoints)(double,double);
    double(*engineBishopBehaviorPoints)(double,double);
    double(*engineRookBehaviorPoints1) (double,double);
    double(*engineRookBehaviorPoints2) (double,double);
    double(*engineQueenBehaviorPoints1)(double,double);
    double(*engineQueenBehaviorPoints2)(double,double);
    double(*engineKingBehaviorPoints)  (double,double);

    double *userKingBehaviorPriority1;
    double *engineKnightBehaviorPriority;
    double *engineBishopBehaviorPriority;
    double *engineRookBehaviorPriority1;
    double *engineRookBehaviorPriority2;
    double *engineQueenBehaviorPriority1;
    double *engineQueenBehaviorPriority2;
    double *engineKingBehaviorPriority;

    double userKingX;
    double userKingY;

    sf::RenderWindow *windowPtr;

    bool windowResized;
    float windowWidth;
    float windowHeight;

    MenuAction menuAction;

    int numberOfButtonTexture;
    int numberOfBackgroundTexture;
    int numberOfBoardTexture;
    Languages setLanguage;
    GameStage gameStage;
    KindOfEndgame choosenEndgame;
    UserKingSideLocation userKingSideLocation;
    UserKingCornerLocation userKingCornerLocation;
//********************************************************************************
    void readConfigFile()
    {
        std::ifstream reading;
        std::string data;
        try
        {
            reading.open("config.txt");
            if (!reading.is_open())
                throw std::ifstream::failure("The file 'config.txt' cannot be opened .");
            if (!getline(reading, data))
                throw std::ifstream::failure("Error reading character from 'config.txt' file .");
        }
        catch(const std::ifstream::failure &e)
        {
            errorType x;
            x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
            throw x;
        }
        reading.close();

        numberOfButtonTexture     = static_cast<int>(data[0] - '0');
        numberOfBackgroundTexture = static_cast<int>(data[1] - '0');
        numberOfBoardTexture      = static_cast<int>(data[2] - '0');
    }
    void writeConfigFile()
    {
        std::string data{};
        data += static_cast<char>(numberOfButtonTexture     + '0');
        data += static_cast<char>(numberOfBackgroundTexture + '0');
        data += static_cast<char>(numberOfBoardTexture      + '0');

        std::ofstream file("config.txt");
        try
        {
            if (!file.is_open())
                throw std::ofstream::failure("The file could not be opened for writing.");
        }
        catch(const std::ofstream::failure &e)
        {
            errorType x;
            x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
            throw x;
        }
        file << data;
        file.close();
    }
}

