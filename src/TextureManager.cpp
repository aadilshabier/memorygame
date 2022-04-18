#include <iostream>
#include <fstream>

#include "TextureManager.h"
#include "SDL.h"
#include "SDL_image.h"

namespace MemoryGame
{
//static instance
static TextureManager *sTextureManager = nullptr;

TextureManager* TextureManager::Instance()
{
	if(sTextureManager == nullptr)
		sTextureManager = new TextureManager();
	return sTextureManager;
}

int TextureManager::load(const std::string& filepath, SDL_Renderer *renderer)
{
	SDL_Surface *surface = IMG_Load(filepath.c_str());
	if (!surface) {
		std::cerr << "ERROR: Could not load surface from file: " << filepath << '\n';
		return -1;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture) {
		std::cerr << "Could not load texture from surface: " << SDL_GetError() << '\n';
		return -1;
	}

	mTextures[mCurrentId] = texture;
	return mCurrentId++;
}

SDL_Texture* TextureManager::get(int id)
{
	if (auto it = mTextures.find(id); it != mTextures.end()) {
		return it->second;
	} else {
		std::cerr << "Could not get texture with id: " << id << '\n';
		return nullptr;
	}
}

void TextureManager::unload(int id)
{
	if (auto it = mTextures.find(id); it != mTextures.end()) {
		SDL_DestroyTexture(it->second);
	}
}

TextureManager::TextureManager()
	: mCurrentId(0)
{
	int flags = IMG_INIT_PNG;
	int innited = IMG_Init(flags);
	if((innited & flags) != flags) {
		std::cerr << "Could not initialize SDL2_image: " << IMG_GetError() << '\n';
		exit(1);
	}
}

TextureManager::~TextureManager()
{
	IMG_Quit();
	for (const auto &[_, texture] : mTextures)
		SDL_DestroyTexture(texture);
}

bool TextureManager::exists(int id)
{
	return mTextures.find(id) != mTextures.end();
}
} // MemoryGame
