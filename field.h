#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    int width;
    int height;
    int matrix[20][10];
} Field;

void drawField(SDL_Renderer *renderer, Field field);
int checkLines(Field *field, int lines);