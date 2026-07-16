#include "Engine.h"
#include "pch.h"
#include <iostream>
#include <Actor.h>
#include "Player.h"

using namespace nu;




std::vector<Vector2> points;
int main()
{
    Engine engine;
    engine.Initialize();
   
    std::vector<Vector2> meshPoints = {
        Vector2{2, 0},
        Vector2{-2, 2},
        Vector2{-1, 0},
        Vector2{-2, 2}
    };
    Color meshColor{1.0f, 1.0f, 1.0f};

    Mesh mesh{meshPoints, meshColor};
    nu::Model model({ mesh });
    Player player{ 2000.0f, Tranform{Vector2{640.0f,512.0f},0.0f,15.0f}, model };

    bool quit = false;
    while (!quit) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
    }

    return 0;
}

