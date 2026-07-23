#include "Engine.h"
#include "pch.h"
#include "Player.h"
#include "Assets.h"

#include <iostream>
#include <Actor.h>
#include <fmod.hpp>
#include <fmod_errors.h>

using namespace nu;




FMOD::System* audio;

int main()
{
    Engine& e = Engine::Get();
    e.Initialize();

    FMOD::System_Create(&audio);

    FMOD_RESULT fmodResult = audio->init(512, FMOD_INIT_NORMAL, nullptr);
    if (fmodResult != FMOD_OK)
        std::cerr << "FMOD init failed: " << FMOD_ErrorString(fmodResult) << std::endl;
    

    Player player{ 2000.0f, Tranform{Vector2{640.0f,512.0f},0.0f,15.0f}, Assets::model_player };

    
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




    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }
    
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        e.GetTime().Tick();
        e.GetInput().Update();
        player.Update(e.GetTime().GetDeltaTime());

        audio->update();



        e.GetRenderer().Clear();

        player.Draw(e.GetRenderer());
        e.GetRenderer().Present();


        if (e.GetInput().GetKeyDown(SDL_SCANCODE_1))
        {
            std::cout << "Sound played." << std::endl;
            audio->playSound(sounds[0], nullptr, false, nullptr);
            
        }

    

       

    }


    return 0;
}

