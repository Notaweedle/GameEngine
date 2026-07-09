#include "Engine.h"
#include <iostream>

using namespace nu;

struct Tranform
{
    Vector2 position;
    float rotation;
    float scale;
};

class Actor {
public:
    Actor() = default;
    Actor(const Tranform& tranform) : m_tranform {tranform} {
    
    }

    void Update(float dt) {
        m_tranform.position += (m_velocity * dt);

        m_tranform.position.x = math::Wrap(0.0f, 1280.0f, m_tranform.position.x);
        m_tranform.position.y = math::Wrap(0.0f, 1024.0f, m_tranform.position.y);
    }

    void Draw(const Renderer& renderer) const
    {
        renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_tranform.position.x - (m_tranform.scale * 0.5f), m_tranform.position.y - ((m_tranform.scale * 0.5f)),40,40);
    }

    const Tranform& getTranform() { return m_tranform; }
    //void getPosistion(const Vector2& pos) { m_tranform.position = pos; };
    void setPosistion(const Vector2& pos) { m_tranform.position = pos; };
    //void getRotation(const float rotaion) { m_tranform.rotation = rotaion; };
    void setRotation(const float rotaion) { m_tranform.rotation = rotaion; };
    //void getScale(const float scale) { m_tranform.scale = scale; };
    void setScale(const float scale) { m_tranform.scale = scale; };

    








private:

protected:
    Tranform m_tranform;
    Vector2 m_velocity;
};



int main()
{
    Actor player{ Tranform {Vector2 {640.0f,512.f},0.0f,50.0f} };


    int height = 1024;
    int width = 512;
    nu::Renderer renderer;
    nu::Input input;
    renderer.Initialize("Game Engine", height, width);
    
    
    std::vector<Vector2> v;

    for (int i = 0; i < 3000; i++) 
    {
        Vector2 vec{ nu::RandomFloat(static_cast<float>(height)), nu::RandomFloat(static_cast<float>(width)) };
        v.push_back(vec);
    }

    Vector2 vel{ 0.5, 10 };
    Vector2 velocity{ 0.0f,0.0f };
    Vector2 force{ 0.0f,0.0f };
    Vector2 pos{ 0.0f,0.0f };

    float speed = 400.0f;
    Vector2 mouse;
    

    // handle events
    SDL_Event e;
    bool quit = false;
    


    while (!quit) 
    {
        input.Update();
        int numkeys;
        const bool* keyState = SDL_GetKeyboardState(&numkeys);

        SDL_GetMouseState(&mouse.x, &mouse.y);

        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        
        if (keyState[SDL_SCANCODE_SPACE]) { std::cout << "press\n";}

       

        if (input.GetKeyDown(SDL_SCANCODE_A))       {force.x  = -speed;}
        else if (input.GetKeyDown(SDL_SCANCODE_D))  {force.x = +speed;}
        else if (input.GetKeyDown(SDL_SCANCODE_W))  {force.y = -speed;}
        else if (input.GetKeyDown(SDL_SCANCODE_D))  {force.y = -speed;}
        
       /* velocity += (force * time.getDealtaTime());
        pos += (velocity * time.getDealtaTime());*/

       
        

        /*if (input.GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty()) {
                points.push_back(input.GetMousePos())
            }
            else {

            }

        }*/


        for (size_t i = 0; i < v.size(); i++) 
        {
            renderer.SetColor (nu::RandomFloat(255), nu::RandomFloat(255), nu::RandomFloat(255), RandomFloat());
            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }

        renderer.SetColor(1.0f, 1.0f, 1.0f, 1.f);
        std::cout << "\033[2J\033[1;1H";
        std::cout <<"(" << mouse.x << " , " << mouse.y << ")" << std::endl;
        std::cout << input.GetButtonDown(Input::MouseButton::Left) << std::endl;

        if (input.GetButtonDown(Input::MouseButton::Left))
        {
            renderer.DrawFillRect(mouse.x, mouse.y - 20, 40, 40);
        }
        



        renderer.Present();
    }
    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}

