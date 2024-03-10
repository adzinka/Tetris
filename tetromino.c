#include "tetromino.h"

const int _x = 10 / 2 - 4 / 2;
const int _y = -1;

void drawTetromino(SDL_Renderer *renderer, Tetromino *tetromino) {

    switch (tetromino->type)
    {
    case I:
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        break;
    case J:
        SDL_SetRenderDrawColor(renderer, 102, 102, 255, 255);
        break;
    case L:
        SDL_SetRenderDrawColor(renderer, 255, 153, 0, 255);
        break;
    case O:
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        break;
    case S:
        SDL_SetRenderDrawColor(renderer, 0, 153, 51, 255);
        break;
    case T:
        SDL_SetRenderDrawColor(renderer, 153, 51, 153, 255);
        break;
    case Z:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break;
    }

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {  
            if (tetromino->shape[y][x] == 1) {
                SDL_Rect rect;
                int fx = x + tetromino->x;
                int fy = y + tetromino->y;
                rect.x = (fx) * 800 / 2 / 10 + 1;
                rect.y = (fy) * 800 / 2 / 10 + 1;
                rect.h = 800 / 2 / 10 - 2;
                rect.w = 800 / 2 / 10 - 2;
                SDL_RenderFillRect(renderer, &rect);
            } 
        }
   }    
}

Tetromino spawnNewTetromino() {
    int shapes[7][4][4] = {
        {{0, 0, 0, 0},
         {1, 1, 1, 1},
         {0, 0, 0, 0},
         {0, 0, 0, 0}},

        {{0, 0, 0, 0},
         {1, 0, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0}},

        {{0, 0, 0, 0},
         {0, 0, 0, 1},
         {0, 1, 1, 1},
         {0, 0, 0, 0}},

        {{0, 0, 0, 0},
         {0, 1, 1, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}},

        {{0, 0, 0, 0},
         {0, 0, 1, 1},
         {0, 1, 1, 0},
         {0, 0, 0, 0}},

        {{0, 0, 0, 0},
         {0, 1, 0, 0},
         {1, 1, 1, 0},
         {0, 0, 0, 0}},

        {{0, 0, 0, 0},
         {1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}}
    };

  Tetromino tetrominoes[7] = {{I, {0}, _x, _y},
                              {J, {0}, _x, _y},
                              {L, {0}, _x, _y},
                              {O, {0}, _x, _y},
                              {S, {0}, _x, _y},
                              {T, {0}, _x, _y},
                              {Z, {0}, _x, _y}};

  srand(time(0));
  int num = (rand() % 7);
  Tetromino tetromino = tetrominoes[num];

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {     
        tetromino.shape[i][j] = shapes[tetromino.type][i][j];     
      }
    }
  return tetromino;
}

void move(int _x, int _y, Tetromino *tetromino) {
    tetromino->x += _x;
    tetromino->y += _y;
}

Tetromino rotate(Tetromino *tetromino) {
  int temp[4][4];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp[i][j] = tetromino->shape[3 - j][i];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetromino->shape[i][j] = temp[i][j];
    }
  }
    return *tetromino;
}

void join(Field *field, Tetromino tetromino) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (tetromino.shape[x][y] == 1) {
                int fx = tetromino.x + y;
                int fy = tetromino.y + x - 1;
                field->matrix[fy][fx] = tetromino.shape[x][y];
            }
        }
    }
}

bool isCollision(Field field, Tetromino *tetromino) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (tetromino->shape[y][x] == 1) {
                if (tetromino->x + x < 0 || tetromino->x + x >= field.width || tetromino->y + y < 0 || tetromino->y + y >= field.height) {
                    return true;
                }
                else if (field.matrix[tetromino->y + y][tetromino->x + x] == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}
