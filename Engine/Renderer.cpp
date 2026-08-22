#include "pch.h"
#include "Renderer.h"
#include "Texture.h"

#include <iostream>

namespace nu
{
    bool Renderer::Initialize(const char* name, int width, int height)
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(name, width, height, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        // cap the frame rate to the monitor refresh so frame timing is stable
        SDL_SetRenderVSync(m_renderer, 1);

        // Render at a fixed logical size (the world size) but present into whatever
        // the actual window size is. This lets us use a smaller physical window
        // (far fewer pixels to push each frame) while keeping all world coordinates.
        SDL_SetRenderLogicalPresentation(m_renderer, 2560, 1600, SDL_LOGICAL_PRESENTATION_LETTERBOX);

        return true;
    }

    void Renderer::ShutDown()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    }

    void Renderer::SetColor(float r, float g, float b, float a) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
    }

    void Renderer::Clear()
    {
        SetColor(0.0f, 0.0f, 0.0f, 1.0f);
        SDL_RenderClear(m_renderer);
    }

    void Renderer::Present()
    {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::DrawPoint(float x, float y) const
    {
        SDL_RenderPoint(m_renderer, x, y);
    }

    void Renderer::DrawFillRect(float x, float y, float w, float h) const
    {
        SDL_FRect rect{ x, y, w, h };
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void Renderer::DrawRect(float x, float y, float w, float h) const
    {
        SDL_FRect rect{ x, y, w, h };
        SDL_RenderRect(m_renderer, &rect);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) const
    {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2); 
        
    } 

    
    void Renderer::DrawCircle(float x, float y, float radius, int segments) const
    {
        if (segments < 3) segments = 3;

        const float fullTurn = 6.28318530718f;
        float step = fullTurn / segments;

        float prevX = x + radius;
        float prevY = y;

        for (int i = 1; i <= segments; i++)
        {
            float angle = step * i;
            float nextX = x + std::cos(angle) * radius;
            float nextY = y + std::sin(angle) * radius;

            DrawLine(prevX, prevY, nextX, nextY);

            prevX = nextX;
            prevY = nextY;
        }
    }

    void Renderer::DrawModel(const Model& model , const Transform transform )const
    {
        for (auto mesh : model.GetMeshes()) 
        {
            SetColor(mesh.GetColor().r, mesh.GetColor().g, mesh.GetColor().b, 1.0f);
            auto& points = mesh.GetPoints();
            for( size_t i = 0; i + 1 < points.size(); i++ )
            {
                Vector2 v1 = points[i].Rotate(transform.rotation);
                Vector2 v2 = points[i + 1].Rotate(transform.rotation);

                v1 *= transform.scale;
                v2 *= transform.scale;


                v1 += transform.position;
                v2 += transform.position;

                DrawLine(v1.x,v1.y,v2.x,v2.y);
            }
        }
    }
    void Renderer::DrawTexture(Texture* texture, float x, float y, float rot, float scale) const
    {
        if (texture == nullptr || texture->m_texture == nullptr) return;

        // native size, scaled
        float w = 0.0f, h = 0.0f;
        SDL_GetTextureSize(texture->m_texture, &w, &h);
        w *= scale;
        h *= scale;

        // (x, y) is the CENTER of the sprite
        SDL_FRect dst{ x - w * 0.5f, y - h * 0.5f, w, h };

        // engine rotation is radians; SDL wants degrees. center = null -> rotate about dst center.
        double angleDeg = static_cast<double>(rot) * (180.0 / 3.14159265358979);
        SDL_RenderTextureRotated(m_renderer, texture->m_texture, nullptr, &dst, angleDeg, nullptr, SDL_FLIP_NONE);
    }

    void Renderer::DrawTexture(Texture* texture, float x, float y, float rot, float scale, const Color& tint) const
    {
        if (texture == nullptr || texture->m_texture == nullptr) return;

        // tint the sprite by the given color (0..1). Needs alpha blending on for the alpha to show.
        SDL_SetTextureBlendMode(texture->m_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorModFloat(texture->m_texture, tint.r, tint.g, tint.b);
        SDL_SetTextureAlphaModFloat(texture->m_texture, tint.a);

        DrawTexture(texture, x, y, rot, scale);

        // reset so other draws of the same texture aren't left tinted
        SDL_SetTextureColorModFloat(texture->m_texture, 1.0f, 1.0f, 1.0f);
        SDL_SetTextureAlphaModFloat(texture->m_texture, 1.0f);
    }
}