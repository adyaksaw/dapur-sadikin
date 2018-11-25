/* File : session-handler.h */
/* Dapur SADIKIN Game Session Manager & Handler */

#ifndef SESSION_HANDLER_H
#define SESSION_HANDLER_H

#include "lib/data_structure/data_type.h"
#include "lib/data_structure/gdt/game_data_type.h"
#include "lib/handler/handler_include.h"

#define initialX 4
#define initialY 4

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

void MainScreen();

void MainGame();

#endif
