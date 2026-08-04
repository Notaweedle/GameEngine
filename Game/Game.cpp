#include "Engine.h"
#include "pch.h"
#include "GameManager.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>


class Object 
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "deconstructor\n"; }

    Object(const Object&) { std::cout << "copy\n"; }
    Object& operator = (const Object&) { std::cout << "assignment\n"; return *this; }
};

int main()
{




    nu::Engine& e = nu::Engine::Get();
    e.Initialize();
    TTF_Init();

    GameManager game;
    game.Initialize();
    
    
    std::shared_ptr<nu::Texture> texture = std::make_shared<nu::Texture>();
    texture->Load("Assets/889684320422338560.png", e.GetRenderer());

    while (!game.IsQuit())
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) return 0;
        }

        e.GetTime().Tick();
        e.GetInput().Update();
        e.GetAudio().Update();

        e.GetRenderer().Clear();                                  
        e.GetRenderer().DrawTexture(texture.get(), 100, 100);     
        e.GetRenderer().Present();                                

        //game.Update(e.GetTime().GetDeltaTime());
        //game.Draw();
    }

    TTF_Quit();
    return 0;
}
