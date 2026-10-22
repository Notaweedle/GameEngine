#include "pch.h"
#include "Renderer.h"
#include "Texture.h"

#include <iostream>
#include <rapidjson/document.h>

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

        SDL_SetDefaultTextureScaleMode(m_renderer, SDL_SCALEMODE_PIXELART);
        SDL_SetRenderVSync(m_renderer, 1);

        
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
    void Renderer::DrawTexture(Texture* texture, float x, float y, float rot, float scale, bool flipH) const
    {
        if (texture == nullptr || texture->m_texture == nullptr) return;

        Vector2 size = texture->GetSize();
        float cameraX = (m_cameraEnabled) ? (m_camera.x - m_width * 0.5f) : 0.0f;
        float cameraY = (m_cameraEnabled) ? (m_camera.y - m_height * 0.5f ): 0.0f;
       
        SDL_FRect dst;
        dst.w = size.x * scale;
        dst.h = size.y * scale;

        dst.x = (x - cameraX) - (dst.w * 0.5);
        dst.y = (y - cameraY) - (dst.h * 0.5);
        
        double angleDeg = static_cast<double>(rot) * (180.0 / 3.14159265358979);
        SDL_RenderTextureRotated(m_renderer, texture->m_texture, nullptr, &dst, angleDeg, nullptr, flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    void Renderer::DrawTexture(Texture* texture, float x, float y, float rot, float scale, const Color& tint) const
    {
        if (texture == nullptr || texture->m_texture == nullptr) return;

        
        SDL_SetTextureBlendMode(texture->m_texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorModFloat(texture->m_texture, tint.r, tint.g, tint.b);
        SDL_SetTextureAlphaModFloat(texture->m_texture, tint.a);

        DrawTexture(texture, x, y, rot, scale,false);

       
        SDL_SetTextureColorModFloat(texture->m_texture, 1.0f, 1.0f, 1.0f);
        SDL_SetTextureAlphaModFloat(texture->m_texture, 1.0f);
    }
    void Renderer::DrawTexture(Texture* texture, const Rect& source, float x, float y, float rot, float scale, bool flipH) const
    {
        if (texture == nullptr || texture->m_texture == nullptr) return;

        Vector2 size = texture->GetSize();
        float cameraX = (m_cameraEnabled) ? (m_camera.x - m_width * 0.5f) : 0.0f;
        float cameraY = (m_cameraEnabled) ? (m_camera.y - m_height * 0.5f) : 0.0f;

        SDL_FRect sourceRect;
        sourceRect.x = source.x;
        sourceRect.y = source.y;
        sourceRect.w = source.w;
        sourceRect.h = source.h;

        SDL_FRect destRect;
        destRect.w = source.w * scale;
        destRect.h = source.h * scale;

        destRect.x = (x - cameraX) - (destRect.w * 0.5f);
        destRect.y = (y - cameraY )-(destRect.h * 0.5f);

        
        double angleDeg = static_cast<double>(rot) * (180.0 / 3.14159265358979);

        SDL_RenderTextureRotated(
            m_renderer,
            texture->m_texture,
            &sourceRect,
            &destRect,
            angleDeg,
            nullptr,
            flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        );
    }

    void Renderer::DrawTexture(Texture& texture, const Rect& source, float x, float y, float rot, float scale, bool flipH) const
    {
        DrawTexture(&texture, source, x, y, rot, scale, flipH);
    }
}