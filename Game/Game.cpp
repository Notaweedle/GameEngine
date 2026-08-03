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

    std::cout << "object\n";
    {
        Object objectA;
        Object objectB = objectA;
        Object objectC;
        objectC = objectA;
    }
    std::cout << "raw pointers\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;

        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;

        Object* objectC = nullptr;
        std::cout << objectC << std::endl;
        objectC = objectA;
        std::cout << objectC << std::endl;

        delete objectA;
        delete objectB;
        //delete objectC;
    }
    std::cout << "smart pointers\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectA.get() << std::endl;

        objectB.reset();



    }



























    return 0;

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
