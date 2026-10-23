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
#include <functional>
#include <string>
#include <vector>
using namespace nu;

// Games selectable with --game <name>. The first entry is the default.
struct GameEntry
{
    std::string name;
    std::function<std::unique_ptr<nu::Game>()> create;
};

static const std::vector<GameEntry> games =
{
    { "spritegame", [] { return std::make_unique<SpriteGame>(); } },
    { "spacegame",  [] { return std::make_unique<SpaceGame>(); } },
};

static void PrintUsage(const char* program)
{
    std::cerr << "Usage: " << program << " [--game <name>]\n";
    std::cerr << "Games:";
    for (const auto& entry : games) std::cerr << " " << entry.name;
    std::cerr << " (default: " << games.front().name << ")\n";
}

// Returns nullptr and prints usage if the arguments are invalid.
static std::unique_ptr<nu::Game> CreateGameFromArgs(int argc, char* argv[])
{
    std::string name = games.front().name;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--game" && i + 1 < argc) {
            name = argv[++i];
        }
        else if (arg.rfind("--game=", 0) == 0) {
            name = arg.substr(7);
        }
        else {
            std::cerr << "Unknown or incomplete argument: " << arg << "\n";
            PrintUsage(argv[0]);
            return nullptr;
        }
    }

    for (const auto& entry : games) {
        if (EqualsIgnoreCase(entry.name, name)) return entry.create();
    }

    std::cerr << "Unknown game: " << name << "\n";
    PrintUsage(argv[0]);
    return nullptr;
}

int main(int argc, char* argv[])
{
    std::unique_ptr<nu::Game> game = CreateGameFromArgs(argc, argv);
    if (!game) return 1;

    SetWorkingDirectory("Assets");   
    
    nu::Engine& e = nu::Engine::Get();
    if (!e.Initialize()) {
        std::cerr << "Failed to initialize engine\n";
        return 1;
    }

    if (!game->Initialize()) {
        std::cerr << "Failed to initialize game\n";
        game.reset();
        e.ShutDown();
        return 1;
    }

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
