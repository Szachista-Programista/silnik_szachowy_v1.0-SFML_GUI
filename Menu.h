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
        setWindowSize,
        setBoardTexture,
        whiteKnight,
        whiteBishop,
        whiteRook,
        whiteQueen,
        blackKnight,
        blackBishop,
        blackRook,
        blackQueen,
        boardMiniature1,
        boardMiniature2,
        boardMiniature3,
        boardMiniature4,
        set1,
        set2,
        set3,
        set4,
        set5,
        set6
    };

    enum Values{
        buttonNumbers = 38
    };

    bool color;
    bool isNotationSaved;

    float buttonScaleX;
    float buttonScaleY;
    float promotionButtonScale;
    float boardMiniatureButtonScale;

    sf::Texture gameBackgroundTexture;
    sf::Sprite  gameBackgroundSprite;
    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Texture boardTexture;
    sf::Sprite  boardSprite;
    sf::Texture movedPieceUnderlightTexture;
    sf::Sprite  movedPieceUnderlightSprite;
    sf::Texture coveredSquareUnderlightTexture;
    sf::Sprite  coveredSquareUnderlightSprite;
    sf::Texture buttonTexture[buttonNumbers];
    sf::Sprite  buttonSprite[buttonNumbers];

    sf::Font font;
    sf::Text text;

    Menu(bool k = false);
        void loadFont();
        void loadTextures();
            void loadButtonTextures();
            void setButtonSprites();
            void loadBoardTextures();
            void setBoardSprites();
            void loadbackgroundTexture();
            void setbackgroundSprites();
    void setGameBackground();

    globalType::MenuAction displayMainMenu();
        globalType::MenuAction displayPlayMenu();
        globalType::MenuAction displaySettingsMenu();
            globalType::MenuAction displayButtonSettings();
            globalType::MenuAction displayWindowSizeSettings();
            globalType::MenuAction displayBoardsSettings();
            void locateBoardsSettingsButtons(std::vector<Button> button);
    globalType::MenuAction displayGameOverMenu(bool notation, globalType::GameResult gameResult);
        std::string setNoteContent(globalType::GameResult gameResult);
    globalType::MenuAction displayGameMenu(bool notation);
    globalType::MenuAction displayPromotionMenuMenu();
    void locatePromotionMenuButtons(std::vector<Button> button);

    void locateMenuButtons(std::vector<Button> button);

    void updateMenuButtons(std::vector<Button> button, float scaleX, float scaleY);

    void drawMenu(std::vector<Button> button, bool gameBackground = false, std::string note = "");
        void drawNote(std::string note);

    void checkWindowSize();

    void drawOverlay();

};
#endif//MENU_H
