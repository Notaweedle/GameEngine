#include "Engine.h"
#include "pch.h"
#include "GameManager.h"
#include <SDL3_ttf/SDL_ttf.h>

int main()
{
    nu::Engine& e = nu::Engine::Get();
    e.Initialize();
    TTF_Init();

    GameManager game;
    game.Initialize();

    while (!game.IsQuit())
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) return 0;
        }

        e.GetTime().Tick();
        e.GetInput().Update();
        e.GetAudio().Update();

        game.Update(e.GetTime().GetDeltaTime());
        game.Draw();
    }

    TTF_Quit();
    return 0;
}
