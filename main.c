#include "field.h"
#include "tetromino.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-L.ttf", 32);
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *surfaceMessage;
  SDL_Texture *message;
  SDL_Color white = {255, 255, 255, 255};
  Field field = {BOARD_WIDTH, BOARD_HEIGHT, {0}};
  SDL_Event event;
  bool quit = false;
  Tetromino tetromino = spawnNewTetromino();
  int lines = 0;          
  SDL_Rect message_rect = {400, 5, 60, 20};

  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);
  SDL_SetWindowTitle(window, "Tetris");
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);

  drawField(renderer, field);
  drawTetromino(renderer, &tetromino);

  SDL_RenderPresent(renderer);

  while (!quit) {
      SDL_Event event;
      if (SDL_WaitEventTimeout(&event, 250)) {
        switch (event.type) {
          case SDL_KEYDOWN: {
            switch (event.key.keysym.sym){
              case SDLK_RIGHT: {
                move(1, 0, &tetromino);
                if (isCollision(field, &tetromino)) {
                  move(-1, 0, &tetromino);
                }
              }
              break;
              case SDLK_LEFT: {
                move(-1, 0, &tetromino);
                if (isCollision(field, &tetromino)) {
                  move(1, 0, &tetromino);
                }
              }
              break;
              case SDLK_UP: {
                Tetromino old = tetromino;
                Tetromino rotated = rotate(&tetromino);
                if (isCollision(field, &rotated)) tetromino = old;
              }
              break;
              case SDLK_DOWN: {
                move(0, 1, &tetromino);
                if (isCollision(field, &tetromino)) {
                  move(0, -1, &tetromino);
                }
              }
              break;
            }
          }
          break;
          case SDL_QUIT:
            quit = true;
          }
        }
        Uint32 tick;
        drawField(renderer, field);
        drawTetromino(renderer, &tetromino);

        if (SDL_GetTicks() - tick > 300) {
          tick = SDL_GetTicks();
          move(0, 1, &tetromino); 
           
          if (isCollision(field, &tetromino)) {
            join(&field, tetromino);
            lines = checkLines(&field, lines);
            tetromino = spawnNewTetromino();
            if (isCollision(field, &tetromino)) {
              quit = true;
            }
          }
          
          printf("%d\n", lines);
          char str[16];
          char input[16] = " lines";
          sprintf(str, "%d", lines);
          strcat(str,input);

          surfaceMessage = TTF_RenderText_Blended(font, str, white);
          message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
          SDL_RenderCopy(renderer, message, NULL, &message_rect);      
          SDL_RenderPresent(renderer);
        } 
    }   
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(message);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
