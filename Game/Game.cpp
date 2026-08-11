#include "Engine.h"
#include "pch.h"
#include "GameManager.h"
#include "Texture.h"
#include "Text.h"
#include "Font.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <random>
using namespace nu;

GameManager game;
uint32_t seed = 1234;

uint32_t RNG() {
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main()
{


    nu::Engine& e = nu::Engine::Get();
    e.Initialize();
    TTF_Init();


    game.Initialize(); 

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) quit = true;
        }

        e.GetTime().Tick();
        e.GetInput().Update();

        game.Update(e.GetTime().GetDeltaTime());
        game.Draw();

    }

    TTF_Quit();
    return 0;
}
