#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include "stdafx.h"
#include "Tileset.h"

using namespace AdditionalType;

class TextureManager
{
public:
	// Load texture in game
	// * id - id texture which you can find in container 
	// * filename - name file which need loading
	// * pRenderer - instance SDL_Renderer type for draw texture
	bool load(std::string id, std::string filename, SDL_Renderer * pRenderer);	


	void draw(std::string id,
				RECT2 areaTexture,		
				SDL_Renderer * pRenderer, 
				SDL_RendererFlip flip = SDL_FLIP_NONE);
	// Draw texture for id
	// * id - target texture for drawing
	// * areaTexture - struct RECT2(is rectangle which have x,y,width,height) in this rect. will be draw texture
	// * pRenderer - instance SDL_Renderer type for draw texture
	// * flip - position texture in world (SDL_FLIP_NONE - normal,SDL_FLIP_VERTICAL - vertical,SDL_FLIP_HORIZONTAL - horizontal)

	void draw(std::string id,
		int x, int y,
		int width, int height,
		SDL_Renderer * pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void draw(std::string id,
		int _x,
		int _y,
		int width,
		int height,
		int alpha,
		double angle,
		SDL_Renderer * pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id,
					RECT2 areaTexture,
					int currentRow,
					int currentFrame,
					SDL_Renderer * pRenderer,
					SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, 
					int _x,
					int _y,
					int width,
					int height,
					int currentRow,
					int currentFrame,
					int alpha,
					double angle,
					SDL_Renderer * pRenderer,
					SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawTile(const std::string & id,
				  int margin,
				  int spacing,
				  int x,
				  int y,
				  int width,
		          int height,
				  int currentRow,
				  int currentFrame,
				  int tileHeight, 
				  int tileWidth,
				  SDL_Renderer * pRenderer);

	void drawTile(const std::string & id,
					int tileID,
					Tileset & tileset,
					int row,
					int column,
					int columnIncr,
					SDL_Renderer * pRenderer);



	static TextureManager * Instance();

	void release();

	void clearFromTextureMap(std::string id);

private:
	std::map<std::string, SDL_Texture*> m_TextureMap;

	static TextureManager * s_pTexure;

	TextureManager();
	TextureManager(const TextureManager & _copyTexture);
	TextureManager * operator=(TextureManager & _copyTexture);
	~TextureManager();
};
#endif // TEXTUREMANAGER_H_