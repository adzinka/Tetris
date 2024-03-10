#include "field.h"

void drawField(SDL_Renderer *renderer, Field field) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 253, 255);
    for (int x = 0; x < field.width; x++) {
        for (int y = 0; y < field.height; y++) {
            if (field.matrix[y][x] == 1) {
                SDL_Rect rect;
                rect.x = x * 800 / 2 / 10;
                rect.y = y * 800 / 2 / 10;
                rect.h = 800 / 2 / 10;
                rect.w = 800 / 2 / 10;
                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                SDL_RenderDrawPoint(renderer, x * 800 / 2 / 10 + 800 / 2 / 10 / 2,
                                    y * 800 / 2 / 10 + 800 / 2 / 10 / 2);
            }
        }
    }
}

int checkLines(Field *field, int lines) {
    for (int i = 0; i < field->height; i++) {
        int count = 0;
        for (int j = 0; j < field->width; j++) {
            if (field->matrix[i][j] == 1) count++;       
        }
        if (count == field->width) {
            lines++;
            int row = i;
            for (int j = 0; j < field->width; j++) {
                field->matrix[i][j] = 0;
            }

            for (int k = row; k >= 0; k--) {
                for (int t = 0; t < field->width; t++) {
                    if (k == 0) {
                        field->matrix[k][t] = 0;
                    } else {
                        field->matrix[k][t] = field->matrix[k-1][t];
                    }
                }
            }
        }
    }
    return lines;
}