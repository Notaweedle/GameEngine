#include "Engine.h"
#include "pch.h"
#include "GameManager.h"
#include "Renderer/Texture.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Serialization/Json.h"    
#include "core/File.h"   
#include "Player.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <random>
using namespace nu;

GameManager game;








int main()
{
   


    nu::Engine& e = nu::Engine::Get();
    e.Initialize();
    
    game.Initialize(); 

    // --- TEMP frame-time diagnostics ---
    float  fpsAccum = 0.0f;   // seconds accumulated this reporting window
    int    fpsFrames = 0;     // frames this window
    float  fpsWorst = 0.0f;   // worst (largest) frame time this window, in ms

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) quit = true;
        }

        e.GetTime().Tick();
        e.GetInput().Update();

        float dt = e.GetTime().GetDeltaTime();

        // --- TEMP frame-time diagnostics ---
        float ms = dt * 1000.0f;
        if (ms > fpsWorst) fpsWorst = ms;
        fpsAccum += dt;
        fpsFrames++;
        if (fpsAccum >= 1.0f) {
            std::cout << "[FPS] " << fpsFrames
                      << "  avg " << (fpsAccum / fpsFrames) * 1000.0f << " ms"
                      << "  worst " << fpsWorst << " ms" << std::endl;
            fpsAccum = 0.0f; fpsFrames = 0; fpsWorst = 0.0f;
        }
        // TEMP

        game.Update(dt);
        game.Draw();

    }

    return 0;
}
