#include "Engine.h"
#include <iostream>

using namespace nu;


int main()
{
    int height = 1024;
    int width = 512;
    nu::Renderer renderer;
    nu::Input input;
    renderer.Initialize("Game Engine", height, width);
    
    std::vector<Vector2> v;

    for (int i = 0; i < 3000; i++) 
    {
        Vector2 vec{ nu::RandomFloat(static_cast<float>(height)), nu::RandomFloat(static_cast<float>(width)) };
        v.push_back(vec);
    }
    Vector2 vel{ 0.5, 10 };

    Vector2 mouse;
    

    // handle events
    SDL_Event e;
    bool quit = false;
    


    while (!quit) 
    {
        input.Update();
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

        int numkeys;
        const bool* keyState = SDL_GetKeyboardState(&numkeys);
        if (keyState[SDL_SCANCODE_SPACE]) { std::cout << "press\n";}




        for (size_t i = 0; i < v.size(); i++) 
        {
            renderer.SetColor (nu::RandomFloat(255), nu::RandomFloat(255), nu::RandomFloat(255), RandomFloat());
            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
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

