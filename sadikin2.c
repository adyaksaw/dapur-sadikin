#include "lib/handler/core/session.h"
#include <string.h>

#include <ncurses.h>

int main()
{
    //initNcurses();

    Initialize_Session();
    
    gameState = MAIN_MENU;
    MainScreen();

    erase();
    refresh();
    Draw_Window();

    MainGame();

    attroff(COLOR_PAIR(1));
    endwin();
}

void initNcurses()
{
    initscr();
    clear();

    checkScreenSize();
    checkColor();

    // center window on screen
    m_nXCoord = (COLS - m_nWidth) / 2;
    m_nYCoord = (LINES - m_nHeight) / 2;
}

void checkScreenSize()
{
    getmaxyx(stdscr, m_nScrHeight, m_nScrWidth);

    if (m_nScrHeight < m_nHeight + 5)
    {
        endwin();

        printf("WARNING: Screen/terminal is not tall enough.\n\n");
        exit(1);
    }

    if (m_nScrWidth < m_nWidth)
    {
        endwin();

        printf("WARNING: Screen/terminal is not wide enough.\n\n");
        exit(1);
    }
}

void checkColor()
{
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color.\n");
        exit(1);
    }
    start_color();
}