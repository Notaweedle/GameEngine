#include "pch.h"
#include "Texture.h"
#include "Renderer.h"   



namespace nu
{

Texture::~Texture(){
    
    if (m_texture) SDL_DestroyTexture(m_texture);
}

bool Texture::Load(const std::string& filename, Renderer& renderer){
    
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        std::cerr << "Could not load image: " << filename << " - " << SDL_GetError() << std::endl;
        return false;
    }
    m_texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);

    SDL_DestroySurface(surface);
    if (m_texture == nullptr)
    {
        std::cerr << "Could not create texture: " << filename << " - " << SDL_GetError() << std::endl;
        return false;
    }

    
    SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

    return true;
}

    Vector2 Texture::GetSize(){

    Vector2 v{ 0.0f, 0.0f };
    if (m_texture) SDL_GetTextureSize(m_texture, &v.x, &v.y);
    return v;

    }

}