#include "Engine.h"
#include "pch.h"
#include "GameManager.h"
#include "Texture.h"
#include "Text.h"
#include "Font.h"
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

    
    nu::res_t<nu::Texture> texture =
        nu::Resources().Get<nu::Texture>("Assets/889684320422338560.png", e.GetRenderer());

    
    nu::res_t<nu::Font> font =
        nu::Resources().Get<nu::Font>("Assets/font.ttf", 48);

    nu::Text text(font);
    text.Create(e.GetRenderer(), "Hello, ResourceManager!", nu::Color(1.0f, 1.0f, 1.0f));

    bool quit = false;
    



    while (!quit)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) quit = true;
        }

       /* e.GetTime().Tick();
        e.GetInput().Update();*/

       
        e.GetRenderer().Clear();
        e.GetRenderer().DrawTexture(texture.get(), 100.0f, 100.0f);   
        text.Draw(e.GetRenderer(), 100.0f, 300.0f);                   
        e.GetRenderer().Present();
    }

    TTF_Quit();
    return 0;
}
