# Silnik Szachowy

Witaj! Ten projekt jest prostym w obsłudze, ale zaawansowanym silnikiem do gry
w szachy, który pozwoli Ci cieszyć się emocjonującymi rozgrywkami przeciwko komputerowi.

# O Autorze

Jestem Krzysiek, a Silnik Szachowy jest moim pierwszym większym
projektem napisanym w języku C++. Przez pół roku poświęciłem sporo
czasu i wysiłku na samodzielną pracę nad tym projektem, a ostatnio postanowiłem
wzbogacić go o eleganckie GUI z pomocą biblioteki SFML.

W trakcie tworzenia owego projektu postanowiłem postawić przed sobą wyzwanie i wymyślić
wszystkie niezbędne funkcje i mechaniki samodzielnie, zamiast szukać gotowych
rozwiązań w internecie. Zależało mi na tym, aby każdy fragment kodu był moim
własnym dziełem i odzwierciedlał moje indywidualne podejście do rozwiązywania problemów.

# Co to jest za projekt?

Jest to program, który umożliwia grę w szachy z komputerem. Dzięki intuicyjnemu
interfejsowi użytkownika i prostemu menu, możesz łatwo rozpocząć grę i przetestować
swoje umiejętności szachowe.

# Oprawa graficzna

Wcześniejsza wersja tego projektu korzystała z piksel-artowej grafiki w konsoli,
aby stworzyć prosty, ale efektowny wygląd szachownicy. Teraz grafika została ulepszona
i zaimplementowana przy użyciu biblioteki SFML, co pozwoliło na bardziej estetyczne
wizualne doświadczenie dla użytkownika.

Po uruchomieniu partii użytkownik zostanie przywitany przez interfejs graficzny,
który wyświetla elegancką i przejrzystą szachownicę. Nowa grafika dodaje głębi
i atrakcyjności do gry, zapewniając jeszcze lepsze wrażenia podczas rozgrywki.

# Jak zacząć?

1. Pobierz pliki projektu z repozytorium.
2. Skompiluj projekt (np. zgodnie z instrukcjami zawartymi w poniższej sekcji),
   bądź skorzystaj z gotowego pliku wykonywalnego dla systemu Windows.
3. Pamiętaj, aby umieścić swój plik wykonywalny w katalogu wyjściowym projektu.
4. Zagraj.

# Instrukcje kompilacji

## Wymagania wstępne

Upewnij się, że Twoje środowisko deweloperskie spełnia poniższe wymagania:

- **Środowisko C++:** Upewnij się, że masz zainstalowany kompilator obsługujący język C++,
  np. g++ dla systemów Unix lub MinGW dla systemu Windows.
- **SFML:** Pobierz i zainstaluj bibliotekę SFML z oficjalnej strony internetowej:
  [SFML Downloads](https://www.sfml-dev.org/download.php). Wybierz odpowiednią wersję
  dla swojego systemu operacyjnego i kompilatora.
- **CMake:** Jeśli jeszcze nie masz, pobierz i zainstaluj CMake z oficjalnej strony
  internetowej: [CMake Downloads](https://cmake.org/download/).

## Konfiguracja projektu

Po zainstalowaniu SFML, wykonaj poniższe kroki, aby skonfigurować projekt:

1. W pierwszym wierszu pliku CMakeLists.txt projektu umieść ścieżkę dostępu do katalogu
   "SFML/include" za pomocą widniejącej tam instrukcji
   "include_directories("C:/ścieżka/do/katalogu/SFML/include")".
2. Uruchom CMake i wybierz katalog źródłowy jako główny katalog projektu,
   a katalog `build` w katalogu źródłowym jako katalog docelowy.
3. Kliknij przycisk "Configure" i wybierz odpowiedni generator dla Twojego systemu
   operacyjnego (np. "Unix Makefiles" dla systemów Unix lub "MinGW Makefiles" dla Windows).
4. Kliknij przycisk "Generate", aby wygenerować pliki projektu CMake.

## Kompilacja projektu

Po skonfigurowaniu projektu za pomocą CMake, wykonaj następujące kroki, aby skompilować projekt:

1. Otwórz katalog `build` w konsoli.
2. Wykonaj polecenie kompilacji, np.: cmake --build . --config Release
3. Przenieś powstały w katalogu `build` plik wykonywalny do głównego
   katalogu projektu.
4. Uruchom program.

# Jak zagrać?

1. **Menu główne**: Po uruchomieniu programu zostaniesz przywitany menu głównym,
   które zawiera opcje:

   - **Play**: Klikając ten przycisk, przechodzisz do menu wyboru koloru,
     gdzie możesz wybrać, czy chcesz grać białymi, czarnymi lub z losowym wyborem koloru.
   - **Settings**: Tutaj możesz dostosować ustawienia graficzne, takie jak rozmiar okna,
     tekstury szachownicy oraz grafiki przycisków.
   - **Exit**: Klikając ten przycisk, wyjdziesz z gry.

2. **Menu wyboru koloru**: Po wybraniu opcji "Play" przechodzisz do menu wyboru koloru,
   gdzie możesz zdecydować, czy chcesz grać białymi, czarnymi lub z losowym wyborem koloru.

3. **Rozgrywka**: Po wyborze koloru rozpoczyna się rozgrywka. Na ekranie po lewej stronie pojawi się
   szachownica z ustawionymi bierkami. Po prawej stronie widoczne będzie pole,
   w którym będzie pojawiać się notacja do gry. Możesz korzystać z przycisków nawigacyjnych,
   aby przewijać notację do tyłu i oglądać wcześniejsze ruchy.

# Dlaczego warto spróbować?

- **Nowa oprawa graficzna**: Zmieniona grafika przy użyciu biblioteki SFML dostarcza
  bardziej atrakcyjne i estetyczne wizualne doświadczenie. Teraz gra jest bardziej
  przyjemna dla oka.
- **Łatwy w obsłudze interfejs**: Prosty i intuicyjny interfejs użytkownika zapewnia
  płynną nawigację i szybki dostęp do gry. Nawet początkujący gracze będą czuli się swobodnie,
  korzystając z różnorodnych opcji i funkcji gry.
- **Dostosowanie opcji**: Możliwość personalizacji tekstur pozwala dostosować grę
  do swoich preferencji. Teraz można dostosować wygląd gry,
  aby jak najlepiej pasowały do indywidualnych upodobań.
- Ponadto, grając w ten sposób, istnieje możliwość zgłębienia złożoności gry szachy analizując
  jak algorytmy generują ruchy, interpretując ich działanie oraz obserwując jak reagują na nasze
  posunięcia. To ciekawe doświadczenie dla graczy na każdym poziomie zaawansowania.

Ciesz się grą w szachy na nowym poziomie z odświeżoną grafiką i ulepszonym interfejsem użytkownika!

██████████████████████████████████████████████  
██████████████████████████████████████████████  
██████████████████████████████████████████████  
██████████████████████████████████████████████  
███████████████████████▀──████████████████████  
████████████████████▀──────▀▀█████████████████  
██████████████████▀────────────▀▀█████████████  
█████████████████▀────────────────████████████  
█████████████████──────█▄──▄▄██▄▄█████████████  
████████████████────────██████████████████████  
███████████████──────────█████████████████████  
███████████████───────────▀███████████████████  
███████████████─────────────▀█████████████████  
███████████████▄─────────────█████████████████  
████████████████▄───────────██████████████████  
█████████████████──────────███████████████████  
████████████████▀▀────────▀▀██████████████████  
██████████████▀──────────────▀████████████████  
██████████████▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄████████████████

# Chess Engine

Welcome! This project is a simple yet advanced chess engine that allows you to enjoy exciting
games against the computer.

# About the Author

I'm Krzysiek, and the Chess Engine is my first major project written in C++. I spent about six
months dedicating a lot of time and effort to working on this project independently, and recently
decided to enrich it with an elegant GUI using the SFML library.

During the creation of this project, I challenged myself to devise all the necessary features
and mechanics independently, instead of seeking ready-made solutions on the internet. I wanted
every piece of code to be my own work and reflect my individual approach to problem-solving.

# What is This Project About?

It's a program that allows you to play chess against the computer. With an intuitive user interface
and simple menu, you can easily start a game and test your chess skills.

# Graphics Enhancement

The earlier version of this project used pixel-art graphics in the console to create a simple yet
effective chessboard appearance. Now, the graphics have been enhanced and implemented using the SFML
library, allowing for a more aesthetically pleasing visual experience for the user.

Upon starting a game, the user will be greeted by a graphical interface displaying an elegant and
clear chessboard. The new graphics add depth and attractiveness to the game, providing an even better
experience during gameplay.

# How to Get Started?

1. Download the project files from the repository.
2. Compile the project (e.g., following the instructions in the section below), or use the precompiled
   executable file for Windows.
3. Make sure to place your executable file in the project's output directory.
4. Start playing.

# Compilation Instructions

## Prerequisites

Ensure that your development environment meets the following requirements:

- **C++ Environment:** Make sure you have a C++ compiler installed, such as g++ for Unix systems
  or MinGW for Windows.
- **SFML:** Download and install the SFML library from the official website:
  [SFML Downloads](https://www.sfml-dev.org/download.php). Choose the appropriate version for
  your operating system and compiler.
- **CMake:** If you don't already have it, download and install CMake from the official
  website: [CMake Downloads](https://cmake.org/download/).

## Project Configuration

After installing SFML, follow these steps to configure the project:

1. In the first line of the CMakeLists.txt file of the project, specify the path to the "SFML/include"
   directory using the provided instruction.
2. Run CMake and select the source directory as the main project directory, and the `build` directory
   within the source directory as the target directory.
3. Click the "Configure" button and choose the appropriate generator for your operating system
   (e.g., "Unix Makefiles" for Unix systems or "MinGW Makefiles" for Windows).
4. Click the "Generate" button to generate the CMake project files.

## Compiling the Project

After configuring the project with CMake, follow these steps to compile the project:

1. Open the `build` directory in the terminal.
2. Execute the compilation command, e.g.: cmake --build . --config Release
3. Move the resulting executable file from the `build` directory to the main project directory.
4. Run the program.

# How to Play?

1. **Main Menu**: Upon launching the program, you'll be greeted by the main menu, which includes options:

   - **Play**: Clicking this button takes you to the color selection menu, where you can choose whether
     to play as white, black, or with a random color selection.
   - **Settings**: Here, you can adjust graphical settings such as window size, chessboard textures, and
     button graphics.
   - **Exit**: Clicking this button exits the game.

2. **Color Selection Menu**: After selecting the "Play" option, you'll move to the color selection menu,
   where you can decide whether to play as white, black, or with a random color selection.

3. **Gameplay**: Upon choosing a color, the game begins. On the left side of the screen, you'll see the
   chessboard with pieces set up. On the right side, there will be a panel where game notation will appear.
   You can use navigation buttons to scroll through the notation and review previous moves.

# Why Give It a Try?

- **Enhanced Graphics**: The updated graphics using the SFML library provide a more attractive
  and aesthetically pleasing visual experience. The game is now more enjoyable to look at.
- **User-Friendly Interface**: The simple and intuitive user interface ensures smooth navigation
  and quick access to the game. Even novice players will feel comfortable using the various game options
  and features.
- **Customization Options**: The ability to personalize textures allows you to customize the game
  to your preferences. You can now tailor the game's appearance to best suit your individual tastes.
- Moreover, by playing this way, there's an opportunity to delve into the complexity of chess by
  analyzing how algorithms generate moves, interpreting their actions, and observing how they respond
  to our moves. It's an intriguing experience for players at every skill level.

Enjoy playing chess at a new level with refreshed graphics and an improved user interface!
