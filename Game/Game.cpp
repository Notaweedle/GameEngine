#include "Engine.h"
#include "pch.h"
#include "SpaceGame/SpaceGame.h"
#include "SpriteGame/SpriteGame.h"
#include "Renderer/Texture.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Serialization/Json.h"
#include "core/File.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <random>
#include "FinalGame/FinalGame.h"
using namespace nu;





int main()
{
    SetWorkingDirectory("Assets");   
    
    nu::Engine& e = nu::Engine::Get();
    e.Initialize();

    
    std::unique_ptr<nu::Game> game = std::make_unique<FinalGame>();
    game->Initialize();

  

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


        e.GetPhysics().Step(dt);
        game->Update(dt);
        game->Draw();
    }

    game.reset();
    e.ShutDown();

    return 0;
}
