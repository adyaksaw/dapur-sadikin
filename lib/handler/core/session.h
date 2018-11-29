/* File : session-handler.h */
/* Dapur SADIKIN Game Session Manager & Handler */

#ifndef SESSION_HANDLER_H
#define SESSION_HANDLER_H

#include "../../data_structure/data_type.h"
#include "../../data_structure/gdt/game_data_type.h"
#include "../handler_include.h"
#include <ncurses.h>
#include <menu.h>

#define initialX 4
#define initialY 4
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define LINE_BREAK print_line_break()

typedef enum {
  MAIN_MENU,
  IN_GAME,
  CREDITS
} GameState;

extern GameState gameState;
extern Player player;
extern Queue CustomerQueue;
extern BinTree resep;

extern Second GameTime;

extern Object *ArrayOfMeja[13];

extern Item ArrayOfItem[30];

extern Matrix Map1, Map2, Map3, Kitchen;
extern Graph BIG_MAP;
extern adrNode Pn;
extern adrSuccNode Pt;

/* Semuanya masih bisa diubah sesuai kebutuhan */
WINDOW *m_pWin, *g_win;

GameState gameState;
Player player;
Queue CustomerQueue;
BinTree resep;

Second GameTime;

Object *ArrayOfMeja[13];

Item ArrayOfItem[30];

Matrix Map1, Map2, Map3, Kitchen;
Graph BIG_MAP;
adrNode Pn;
adrSuccNode Pt;

extern int m_nXCoord,
    m_nYCoord,
    m_nWidth,
    m_nHeight,
    m_nPageSize,
    m_nTopLine,
    m_nScrWidth,
    m_nScrHeight,
    m_cTitleColor,
    m_cCurrColor,
    m_cStatusColor,
    m_cCurrX,
    m_cCurrY,
    m_gOver;

void print_line_break();

/* GAME FUNCTION */
void SaveToFile(char *FileName);
void LoadFromFile(char *FileName);
void PrintOrder();
void PrintAllOrder();
void PrintTableStatus(Object Meja);
void PrintAllMemory(Matrix *M);
void PrintAllTable();
void Dealokasi_All_Meja();
void Initialize_Session();
void CustomerGenerator();
void reduceAllCustPatience();
void CheckTransitiontoGraph(Matrix *M1, Matrix *M2, Direction dir);
void InputProcessor(char input[], int input_length);

/* SESSION */
void MainScreen();
void MainGame();
void Credits();

/* DUMMY */
void printCustomerW(Customer customer);


/* INTERFACE */
void Draw_Window();
void Draw_Static_Items();
void Draw_Dynamic_Items();
void Draw_Panel();

void SaveToFile(char *FileName);

void LoadFromFile(char *FileName);

void PrintAllOrder();

void PrintTableStatus(Object Meja);

void PrintAllMemory(Matrix *M);

void PrintAllTable();

void Dealokasi_All_Meja();

void Init();

void CustomerGenerator();

void reduceAllCustPatience();

void CheckTransitiontoGraph(Matrix *M1, Matrix *M2, Direction dir);

void InputProcessor(char input[], int input_length);

void PrintNotif(char *s);

void EnableRawInput();

void DisableRawInput();

void Menu(int height, int width, int offX, int offY, char *choices[], char *choices2[], char *ret);

void MainScreen();

void MainGame();

void Credits();

void Draw_Window();
void Draw_Static_Items();
void Draw_Dynamic_Items();

//possible problems
void PrtStk(Stack S, int row, int col);
void PrintTreee(BinTree P, int h);
void PrintTreeWithIndentt(BinTree P, int h, int idt);

void Print_RoomW(Matrix M);

#endif
