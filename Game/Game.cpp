#include "Engine.h"
#include "pch.h"
#include <iostream>
#include <Actor.h>
#include "Player.h"
#include <fmod.hpp>
#include <fmod_errors.h>

using namespace nu;




FMOD::System* audio;

int main()
{
    engine.Initialize();
    FMOD::System_Create(&audio);

    FMOD_RESULT fmodResult = audio->init(512, FMOD_INIT_NORMAL, nullptr);
    if (fmodResult != FMOD_OK)
        std::cerr << "FMOD init failed: " << FMOD_ErrorString(fmodResult) << std::endl;

    Mesh hull({
        Vector2( 4.0f,  0.0f),   // nose (far right)
        Vector2( 1.0f, -1.2f),   // upper shoulder
        Vector2(-2.0f, -0.8f),   // upper rear
        Vector2(-2.0f,  0.8f),   // lower rear
        Vector2( 1.0f,  1.2f),   // lower shoulder
        Vector2( 4.0f,  0.0f)    // close back to nose
    }, Color(0.494f, 0.549f, 0.329f));

    Mesh cockpit({
        Vector2( 1.8f, -0.2f),
        Vector2( 0.4f, -1.0f),
        Vector2(-0.5f, -0.3f),
        Vector2( 1.8f, -0.2f)    // close
    }, Color(0.35f, 0.80f, 1.0f));

    Mesh wing({
        Vector2( 0.0f,  1.07f),  // leading attach - on the hull belly edge
        Vector2(-2.5f,  2.4f),   // wing tip, swept down and back
        Vector2(-2.0f,  0.8f),   // trailing attach - hull lower-rear corner
        Vector2( 0.0f,  1.07f)   // close
    }, Color(0.55f, 0.55f, 0.60f));

    Mesh flame({
        Vector2(-2.0f, -0.5f),
        Vector2(-3.6f,  0.0f),
        Vector2(-2.0f,  0.5f),
        Vector2(-2.0f, -0.5f)    // close
    }, Color(1.0f, 0.5f, 0.1f));

    nu::Model model;
    model.AddMesh(hull);
    model.AddMesh(cockpit);
    model.AddMesh(wing);
    model.AddMesh(flame);

    Player player{ 2000.0f, Tranform{Vector2{640.0f,512.0f},0.0f,15.0f}, model };
    
    PlayerDesc playerDesc;
    playerDesc.name = "Player";


    Scene secne;

    void* extradriverdata = nullptr;

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    fmodResult = audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
    if (fmodResult != FMOD_OK)
        std::cerr << "FMOD createSound failed: " << FMOD_ErrorString(fmodResult) << std::endl;
    sounds.push_back(sound);


    
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
        engine.GetInput().Update();
        player.Update(engine.GetTime().GetDeltaTime());

        audio->update();

        

        engine.GetRenderer().Clear();
        
        player.Draw(engine.GetRenderer());
        std::cout << player.getVelocity().x << std::endl;
        std::cout << player.getVelocity().y << std::endl;
        engine.GetRenderer().Present();


        if (engine.GetInput().GetKeyDown(SDL_SCANCODE_1))
        {
            std::cout << "Sound played." << std::endl;
            audio->playSound(sounds[0], nullptr, false, nullptr);
            
        }

       

    }

    return 0;
}

