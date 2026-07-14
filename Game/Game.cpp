#include "Engine.h"
#include "pch.h"
#include <iostream>
#include <Actor.h>

using namespace nu;




std::vector<Vector2> points;
int main()
{
   // Actor player{ Tranform {Vector2 {640.0f,512.f},0.0f,50.0f} };


    int height = 1024;
    int width = 512;
    nu::Renderer renderer;
    nu::Input input;
    renderer.Initialize("Game Engine", height, width);
    
    
    std::vector<Vector2> v;
    float speed = 400.0f;
    Vector2 mouse;
    // handle events
    SDL_Event e;
    bool quit = false;
    


    while (!quit) 
    {
        input.Update();
        int numkeys;
        const bool* keyState = SDL_GetKeyboardState(&numkeys);
        SDL_GetMouseState(&mouse.x, &mouse.y);

        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        renderer.SetColor(1.0f, 1.0f, 1.0f, 1.f);
        std::cout << "\033[2J\033[1;1H";
        std::cout <<"(" << mouse.x << " , " << mouse.y << ")" << std::endl;
        std::cout << input.GetButtonDown(Input::MouseButton::Left) << std::endl;

        if (input.GetButtonDown(Input::MouseButton::Left))
        {
            renderer.DrawFillRect(mouse.x, mouse.y - 20, 40, 40);
        }
        



        renderer.Present();
    }

    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}

