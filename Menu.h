#ifndef MENU_H
#define MENU_H

#include "GlobalDefinitions.h"
#include <SFML/Graphics.hpp>

class Menu{
public://////////////////

    enum Button{
        goBack,
        backToGame,
        black,
        exit,
        mainMenu,
        menu,
        notationSaved,
        play,
        random,
        saveNotation,
        settings,
        watchPlayedGame,
        white,
        LeftArrow,
        endLeftArrow,
        RightArrow,
        endRightArrow,
        setButtons,
        set1,
        set2,
        set3,
        set4,
        set5,
        set6
    };
    enum PromotionPiece{
        whiteKnight,
        whiteBishop,
        whiteRook,
        whiteQueen,
        blackKnight,
        blackBishop,
        blackRook,
        blackQueen
    };
    enum Values{
        promotionPieceNumbers = 8,
        buttonNumbers = 24
    };

    bool color;
    bool isNotationSaved;

    float buttonScaleX;
    float buttonScaleY;

    sf::Texture gameBackgroundTexture;
    sf::Sprite  gameBackgroundSprite;
    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Texture boardTexture;
    sf::Sprite  boardSprite;
    sf::Texture promotionPieceTextures[promotionPieceNumbers];
    sf::Sprite  promotionPieceSprite[promotionPieceNumbers];
    sf::Texture movedPieceUnderlightTexture;
    sf::Sprite  movedPieceUnderlightSprite;
    sf::Texture coveredSquareUnderlightTexture;
    sf::Sprite  coveredSquareUnderlightSprite;
    sf::Texture buttonTexture[buttonNumbers];
    sf::Sprite  buttonSprite[buttonNumbers];


    Menu(bool k = false);

    void loadTextures();
        void loadButtonTextures();
        void setButtonSprites();
        void loadBoardTextures();
        void setBoardSprites();
        void loadPromotionPieceTextures();
        void setPromotionPieceSprites();
        void loadbackgroundTexture();
        void setbackgroundSprites();

        void setGameBackground();

    globalType::MenuAction displayMainMenu();
        globalType::MenuAction displayPlayMenu();
        globalType::MenuAction displaySettingsMenu();
            globalType::MenuAction displayButtonSettings();
    globalType::MenuAction displayGameOverMenu(bool notation, globalType::GameResult gameResult);
    globalType::MenuAction displayGameMenu(bool notation);

    void locateMenuButtons(std::vector<Button> button);

    void updateMenuButtons(std::vector<Button> button);

    void drawMenu(std::vector<Button> button, bool gameBackground = false);

    void checkWindowSize();

    void drawOverlay();

};
#endif//MENU_H
