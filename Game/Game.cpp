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
using namespace nu;

GameManager game;


int main()
{
    
    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("Assets/data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("Assets/data/data.json", document))
        {
            // read the age data (int) from the json
            int age;
            json::Read(document, "age", age);
            // show the age data
            std::cout << age << std::endl;
        }
    }
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
