/* File : session-handler.h */
/* Dapur SADIKIN Game Session Manager & Handler */

#ifndef SESSION_HANDLER_H
#define SESSION_HANDLER_H

typedef enum {
  MAIN_MENU,
  IN_GAME,
  CREDITS
} GameState;

/* Semuanya masih bisa diubah sesuai kebutuhan */

void ChangeGameState(GameState *gameState);
/*
    Mengubah status game di gameState.
*/

#endif
