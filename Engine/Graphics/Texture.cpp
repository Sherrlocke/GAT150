#include "Texture.h"
#include "Graphics/Renderer.h"
#include <SDL_image.h>
#include <iostream>
#include <cassert>

namespace nc {
	
	Texture::Texture(Renderer* renderer)
	{
		this->renderer = renderer->renderer;
	}

	bool Texture::Create(SDL_Surface* surface)
	{
		// create texture
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr)
		{
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}

	bool Texture::Load(const std::string& name, void* data)
	{
		assert(data);

		renderer = static_cast<Renderer*>(data)->renderer;

		SDL_Surface* surface = IMG_Load(name.c_str());

		if (surface == nullptr) {
			std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
			return false;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		if (texture == nullptr) {
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			return false;


			return true;

		}

	}

	Vector2 Texture::GetSize() const
	{
		SDL_Point point;
		SDL_QueryTexture(texture, nullptr, nullptr, &point.x, &point.y);

		return Vector2{ point.x, point.y };
	}

}