#include "Engine.h"
#include "pch.h"
#include <iostream>
#include <Actor.h>
#include "Player.h"

using namespace nu;





int main()
{
    Engine engine;
    engine.Initialize();
   
    std::vector<Vector2> meshPoints = {
        Vector2(1,0),
        Vector2(1,1),
        Vector2(2,2),
        Vector2(2,3),
        Vector2(3,1),
        Vector2(3,0),
        Vector2(2,.5)
    };
    Color meshColor{1.0f, 1.0f, 1.0f};

    Mesh mesh{meshPoints, meshColor};
    nu::Model model({ mesh });
    Player player{ 20.0f, Tranform{Vector2{640.0f,512.0f},0.0f,15.0f}, model };

    Scene secne;

   // secne.AddActor(player);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        engine.GetTime().Tick();
        player.Update(engine.GetTime().GetDeltaTime());

        engine.GetRenderer().Clear();
        player.Draw(engine.GetRenderer());
        engine.GetRenderer().Present();
    }

    return 0;
}

