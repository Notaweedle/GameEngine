#include "Engine.h"

#include "SDL3/SDL.h"
#include <iostream>

int main()
{
    int height = 1280;
    int width = 1024;
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", height, width);
    
    

    // handle events
    SDL_Event e;
    bool quit = false;

    while (!quit) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
        }
                
        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        renderer.SetColor(255, 255, 255, 1);
        renderer.DrawFillRect(0, 0, height, width);
        // background 


        for (int i = 0; i < 1250; i++)
        {
            renderer.SetColor(rand() % 255, rand() % 255, rand() % 255, rand() % 26);
            renderer.DrawFillRect(rand() % height, rand() % width, rand() % 50, rand() % 50);
        }

        for (int i = 0; i < 10000; i++) 
        {
            renderer.SetColor(rand() % 255,rand() % 256,rand() % 256, 1);
            renderer.DrawPoint(rand() % 1280, rand() % 1024);
        }

        

        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}

