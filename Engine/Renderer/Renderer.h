#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Model.h"
#include "math/Transform.h"
#include <Math/Rect.h>

namespace nu
{
	class Texture;   
	class Renderer
	{
	public:
		friend class Texture;
		bool Initialize(const char* name, int width, int height);
		void ShutDown();

		void Clear();
		void Present();
		

		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;

		void SetColor(float r, float g, float b, float a = 1.0f) const;
		
		void DrawPoint(float x, float y) const;
		void DrawFillRect(float x, float y, float w, float h) const;
		void DrawRect(float x, float y, float w, float h) const;
		void DrawLine(float x1, float y1, float x2, float y2) const;
		void DrawCircle(float x, float y, float radius, int segments = 24) const;
		void DrawModel(const Model& model, const Transform transform) const;
		void DrawTexture(Texture* texture, float x, float y, float rot, float scale, bool flipH = false) const;
		void DrawTexture(Texture* texture, float x, float y, float rot, float scale, const Color& tint) const;

		void DrawTexture(Texture* texture,const Rect& source, float x, float y, float rot, float scale, bool flipH) const;
		// reference overload (forwards to the pointer version) so callers holding a Texture& can draw a sub-rect
		void DrawTexture(Texture& texture, const Rect& source, float x, float y, float rot, float scale, bool flipH) const;

		SDL_Renderer* GetRenderer() const { return m_renderer; }

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}
