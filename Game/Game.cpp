#include "Engine.h"
#include "pch.h"
#include "GameManager.h"
#include "Texture.h"
#include "Text.h"
#include "Font.h"
#include "Json.h"    
#include "File.h"   
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <random>
#include "Player.h"
using namespace nu;

GameManager game;


int main()
{
    
    // load the json data from a file
    
   // std::string buffer;
   // if (ReadTextFile("Assets/data/data.json", buffer))
    {
        /* show the contents of the json file (debug)*/
       // std::cout << buffer << std::endl;

        /* create json document from the json file contents*/
        //rapidjson::Document document;
        //if (json::Load("Assets/data/data.json", document))
        {
            // read the age data (int) from the json
           /* int age;
            float speed;
            bool isAwake;
            std::string name;
            nu::Vector2 v2;
            nu::Color color;
            json::Read(document, "age", age);
            json::Read(document, "speed", speed);
            json::Read(document, "isAwake", isAwake);
            json::Read(document, "name", name);
            json::Read(document, "color", color);
            json::Read(document, "position", v2);*/

            // show the age data
         /*   std::cout << name << std::endl;
            std::cout << age << std::endl;
            std::cout << speed << std::endl;
            std::cout << isAwake << std::endl;
            std::cout << v2.x << " , " << v2.y << std::endl;
            std::cout << color.r <<" " << color.g <<" " << color.b << " " << color.a << std::endl;*/
        }
    }
    //return 0;


    Factory::Instance().Register<Actor>("actor");
    Factory::Instance().Register<Player>("player");
    Factory::Instance().Register<Enemy>("enemy");

    auto actor = Factory::Instance().Create("actor");
    auto player = Factory::Instance().Create("player");
    auto enemy = Factory::Instance().Create("enemy");

    std::cout << actor->IsActive()  << std::endl;
    std::cout << actor->GetName() << std::endl;

    std::cout << player->IsActive()  << std::endl;
    std::cout << player->GetName()  << std::endl;

    std::cout << enemy->IsActive()  << std::endl;
    std::cout << enemy->GetName()  << std::endl;



    return 0;

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
