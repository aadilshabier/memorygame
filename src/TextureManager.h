#pragma once

#include <unordered_map>
#include <string>

#include "SDL.h"

namespace MemoryGame
{
class TextureManager
{
public:
	/* get the singleton */
	static TextureManager* Instance();
	/* load a texture into the manager
	 * returns a non-zero id if successful, -1 if unsuccessful
	 */
	int load(const std::string& filepath, SDL_Renderer *renderer);
	/* get texture by the id
	 * returns
	 */
	SDL_Texture* get(int id);
	/* unload texture if it exists */
	void unload(int id);
	~TextureManager();
private:
	TextureManager();
	TextureManager(const TextureManager&) = delete;
	/* Check whether a texture with the given id exists exists */
	bool exists(int id);
private:
	std::unordered_map<int, SDL_Texture*> mTextures;
	int mCurrentId;
};
}
