#include "Engine.h"
#include "pch.h"
#include "SpaceGame/SpaceGame.h"
#include "Renderer/Texture.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Serialization/Json.h"
#include "core/File.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <random>
#include "SpriteGame/SpriteGame.h"
using namespace nu;





int main()
{
    SetWorkingDirectory("Assets");   
    
    nu::Engine& e = nu::Engine::Get();
    e.Initialize();

    std::unique_ptr<nu::Game> game = std::make_unique<SpriteGame>();
    game->Initialize();

    // --- TEMP frame-time diagnostics ---
    float  fpsAccum = 0.0f;    
    int    fpsFrames = 0;     
    float  fpsWorst = 0.0f;  

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

        //// --- TEMP frame-time diagnostics ---
        //float ms = dt * 1000.0f;
        //if (ms > fpsWorst) fpsWorst = ms;
        //fpsAccum += dt;
        //fpsFrames++;
        //if (fpsAccum >= 1.0f) {
        //    //std::cout << "[FPS] " << fpsFrames << "  avg " << (fpsAccum / fpsFrames) * 1000.0f << " ms" << "  worst " << fpsWorst << " ms" << std::endl;
        //    fpsAccum = 0.0f; fpsFrames = 0; fpsWorst = 0.0f;
        //}
        //// TEMP

        e.GetPhysics().Step(dt);
        game->Update(dt);
        game->Draw();
    }

    game.reset();
    e.ShutDown();

    return 0;
}
