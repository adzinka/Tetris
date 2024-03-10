#pragma once
#include "field.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>

typedef enum {I = 0, J, L, O, S, T, Z} Type;
typedef int TetrominoShape[4][4];

typedef struct {
    Type type;
    int shape[4][4];
    int x;
    int y;
} Tetromino;

void drawTetromino(SDL_Renderer *renderer, Tetromino *tetromino);
void move(int x, int y, Tetromino *tetromino);
Tetromino rotate(Tetromino *tetromino);
Tetromino spawnNewTetromino();
void join(Field *field, Tetromino tetromino);
bool isCollision(Field field, Tetromino *tetromino);