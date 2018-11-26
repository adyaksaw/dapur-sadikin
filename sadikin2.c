#include "lib/handler/core/session.h"
#include <string.h>

void destroy_win(WINDOW *local_win);
void drawWindow();
void drawStaticItems();

WINDOW *m_pWin;

int m_nXCoord = 0,
    m_nYCoord = 0,
    m_nWidth = 100,
    m_nHeight = 28,
    m_nPageSize = 20,
    m_nTopLine = 5,
    m_nScrWidth,
    m_nScrHeight,
    m_cTitleColor = (int)(COLOR_YELLOW),
    m_cCurrColor = (int)(COLOR_YELLOW),
    m_cStatusColor = (int)(COLOR_YELLOW);

char m_strTitle[20],
    m_strHeaders[100],
    m_strStatus[20];

int main()
{
    char input[10];
    int nRows, nCols;

    getmaxyx(stdscr, nRows, nCols);

    initNcurses();

    Initialize_Session();

    gameState = MAIN_MENU;
    MainScreen();

    erase();
    refresh();

    strcpy(m_strTitle, "DAPUR SADIKIN");
    strcpy(m_strHeaders, " Name:             |   Money:                    |  Life:                 |  Time:     ");
    strcpy(m_strStatus, "Command: ");

    m_pWin = newwin(m_nHeight, m_nWidth, m_nYCoord, m_nXCoord);
    box(m_pWin, 0, 0);

    drawWindow();

    getstr(input);
    printw("%s", input);

    //MainGame();

    // gameState = CREDITS;
    // Credits();

    attroff(COLOR_PAIR(1));
    getch();
    endwin();
}

void initNcurses()
{
    initscr();
    //curs_set(0); // hide the cursor
    clear();
    if (has_colors() == FALSE)
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();

    checkScreenSize();

    // center window on screen
    m_nXCoord = (COLS - m_nWidth) / 2;
    m_nYCoord = (LINES - m_nHeight) / 2;
}

void checkScreenSize()
{
    int nRows, nCols;

    getmaxyx(stdscr, nRows, nCols);

    m_nScrHeight = nRows;
    m_nScrWidth = nCols;

    if (m_nScrHeight < m_nHeight)
    {
        endwin();

        printf("Screen/terminal is not tall enough.");
        getch();
        exit;
    }

    if (m_nScrWidth < m_nWidth)
    {
        endwin();

        printf("Screen/terminal is not wide enough.");
        getch();
        exit;
    }
}

void drawWindow()
{
    // update the screen width/height variables and make sure that the window will
    // still fit in case the user happens to resize their terminal (e.g., xterm);
    // throws an exception if screen too small in either direction
    checkScreenSize();

    drawStaticItems();
    drawDynamicItems();

    refresh();
    wrefresh(m_pWin);
}

void drawDynamicItems(){
    // headers ("Char", "Binary", "Octal", "Decimal", "Hexadecimal")
    int i = 1;
    while(i<Name(player).Length && Name(player).TabKata[i] != '\0'){
        mvwprintw(m_pWin, 3, 10+i, "%c", Name(player).TabKata[i]);
        i++;
    }
    //mvwprintw(m_pWin, 3, 10, "%s", Name(player));
    mvwprintw(m_pWin, 3, 45, "%d", Money(player));
    mvwprintw(m_pWin, 3, 70, "%d", Life(player));
    mvwprintw(m_pWin, 3, 95, "%d", GameTime);
//    mvwprintw(m_pWin, 6, 2, "&d", );
}

void drawStaticItems()
{
    
    // title, centered
    wattron(m_pWin, A_BOLD);
    mvwprintw(m_pWin, 1, (m_nWidth / 2) - strlen(m_strTitle)/2, "%s", m_strTitle);
    wattroff(m_pWin, A_BOLD);

    // line underneath the title
    mvwhline(m_pWin, 2, 1, 0, m_nWidth - 2);
    mvwhline(m_pWin, 14, 1, 0, 20);
    mvwhline(m_pWin, 14, 76, 0, 23);
    mvwaddch(m_pWin, 2, 0, ACS_LTEE);
    mvwaddch(m_pWin, 2, 20, ACS_TTEE);
    mvwaddch(m_pWin, 2, 50, ACS_TTEE);
    mvwaddch(m_pWin, 2, 75, ACS_TTEE);

    // headers ("Char", "Binary", "Octal", "Decimal", "Hexadecimal")
    mvwprintw(m_pWin, 3, 1, "%s", m_strHeaders);
    mvwprintw(m_pWin, 5, 2, "Waiting customer:");
    mvwprintw(m_pWin, 5, 77, "Food stack:");
    mvwprintw(m_pWin, 15, 2, "Orders:");
    mvwprintw(m_pWin, 15, 77, "Hand:");

    // separators between the headers
    mvwaddch(m_pWin, 3, 20, ACS_VLINE);
    mvwaddch(m_pWin, 3, 50, ACS_VLINE);
    mvwaddch(m_pWin, 3, 75, ACS_VLINE);

    // line underneath the headers
    mvwhline(m_pWin, 4, 1, 0, m_nWidth - 2);
    mvwhline(m_pWin, 4, 1, 0, m_nWidth - 2);
    mvwaddch(m_pWin, 4, 0, ACS_LTEE);
    mvwaddch(m_pWin, 4, 20, ACS_PLUS);
    mvwaddch(m_pWin, 4, 50, ACS_BTEE);
    mvwaddch(m_pWin, 4, 75, ACS_PLUS);

    // column separators in the ASCII list view
    for (int iii = 0; iii < m_nPageSize; iii++)
    {
        mvwaddch(m_pWin, m_nTopLine + iii, 20, ACS_VLINE);
        mvwaddch(m_pWin, m_nTopLine + iii, 75, ACS_VLINE);
    }

    // line above the status text
    mvwhline(m_pWin, 25, 1, 0, m_nWidth - 2);
    mvwhline(m_pWin, 25, 1, 0, m_nWidth - 2);
    mvwaddch(m_pWin, 25, 0, ACS_LTEE);
    mvwaddch(m_pWin, 25, 20, ACS_BTEE);
    mvwaddch(m_pWin, 25, 75, ACS_BTEE);

    // status text
    wattron(m_pWin, A_BOLD);
    mvwprintw(m_pWin, 26, 3, "%s", m_strStatus);
    wattroff(m_pWin, A_BOLD);
}

void destroy_win(WINDOW *local_win)
{
    /* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    /* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
    wrefresh(local_win);
    delwin(local_win);
}
