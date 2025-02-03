#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define GRID_SIZE 5 //size of grid
#define CELL_SIZE (SCREEN_WIDTH / GRID_SIZE) //size of cell

void drawGrid(SDL_Renderer *renderer, int centerX, int centerY)
{
    //color backgroud
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //Draw cell
    for(int row = 0; row < GRID_SIZE; row++)
    {
        for(int col = 0; col < GRID_SIZE; col++)
        {
          SDL_Rect cell = {col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE};

          //central cell in red
          if(row == centerY && col == centerX)
             SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
          // Moore neighborn in blue
          else if((row == centerY && (col == centerX-1 || col == centerX+1 || col == centerX-2 
                                     || col == centerX+2) ||
                                     (col == centerX && (row == centerY-1 || row == centerY+1 ||
                                      row == centerY-2 || row == centerY+2))))
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                //CONTINUE MODIFIED THE MATRIX
          //Moore neighborns
          else 
             SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
          
          SDL_RenderFillRect(renderer, &cell);

          //draw border of cells 
          
          SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
          SDL_RenderDrawRect(renderer, &cell);


        }
    }
    SDL_RenderPresent(renderer);
}

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error in start SDL %s \n", SDL_GetError());
        return -1;
    }

    //create window and renderer 

    SDL_Window *window = SDL_CreateWindow("Moore neighborn", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
                                
    if(!window)
    {
        printf("Error initializating window %s \n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        printf("Error initializating renderer: %s \n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    //coordinates of center in the grid
    int centerX = GRID_SIZE / 2;
    int centerY = GRID_SIZE / 2;

    //draw initial grid
    drawGrid(renderer, centerX, centerY);

    //event of bucle
    int running = 1;
    SDL_Event event;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
    }
    //clean resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    //end main
}

