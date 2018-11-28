#include "lib/handler/core/session.h"

int main()
{
    Initialize_Session();

    gameState = MAIN_MENU;
    MainScreen();

    MainGame();

    gameState = CREDITS;
    Credits();
}