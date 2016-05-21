#include "TextureManager.h"
#include "Tileset.h"

TextureManager * TextureManager::s_pTexure = 0;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

TextureManager::TextureManager()
{
}

TextureManager::TextureManager(const TextureManager & _copyTexture)
{
	m_TextureMap = _copyTexture.m_TextureMap;
}

TextureManager * TextureManager::operator=(TextureManager & _copyTexture)
{
	m_TextureMap = _copyTexture.m_TextureMap;
	return this;
}

TextureManager::~TextureManager()
{
}

TextureManager * TextureManager::Instance()
{
	if (!s_pTexure)
	{
		s_pTexure = new TextureManager();
	}
	return s_pTexure;
}

bool TextureManager::load(std::string id, std::string filename, SDL_Renderer * pRenderer)
{
	SDL_Surface * pTempSurface = IMG_Load(filename.c_str());

	if (!pTempSurface)
	{
		return false;
	}
	SDL_Texture * pTempTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTempTexture != 0)
	{
		m_TextureMap[id] = pTempTexture;
		return true;
	}
	delete pTempTexture;
	return false;
}

void TextureManager::draw(std::string id, RECT2 areaTexture, SDL_Renderer * pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Texture * pTexture = m_TextureMap.at(id);
	SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	srcRect.x = destRect.x = areaTexture.beginRect.x;
	srcRect.y = destRect.y = areaTexture.beginRect.y;
	destRect.w = areaTexture.width;
	destRect.h = areaTexture.height;	
	
	SDL_RenderCopyEx(pRenderer, pTexture, &srcRect, &destRect,0,0,flip);
}

void TextureManager::draw(std::string id,
	int x, int y,
	int width, int height,
	SDL_Renderer * pRenderer,
	SDL_RendererFlip flip)
{
	if (m_TextureMap.find(id) == m_TextureMap.end())
	{
		return;
	}
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Texture * pTexture = m_TextureMap.at(id);
	SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);
	
	destRect.x = x;
	destRect.y = y;
	destRect.h = height;
	destRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;

	SDL_RenderCopyEx(pRenderer, pTexture, &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id,
	int _x,
	int _y,
	int width,
	int height,
	int alpha,
	double angle,
	SDL_Renderer * pRenderer,
	SDL_RendererFlip flip)
{
	Uint32 frameStart, frameTime;
	frameStart = SDL_GetTicks();
	if (m_TextureMap.find(id) == m_TextureMap.end())
	{
		return;
	}
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Texture * pTexture = m_TextureMap.at(id);
	SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	destRect.x = _x;
	destRect.y = _y;
	destRect.h = height;
	destRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;
	SDL_SetTextureAlphaMod(m_TextureMap.at(id), alpha);
	SDL_RenderCopyEx(pRenderer, pTexture, &srcRect, &destRect,angle, 0, flip);

	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < DELAY_TIME)
	{
		SDL_Delay((int)(DELAY_TIME - frameTime));
	}
}

void TextureManager::drawFrame(std::string id, RECT2 areaTexture, int currentRow, int currentFrame,  SDL_Renderer * pRenderer,
	SDL_RendererFlip flip)
{
	if (m_TextureMap.find(id) == m_TextureMap.end())
	{
		return;
	}
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Texture * pTexture = m_TextureMap.at(id);
	SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	destRect.x = areaTexture.width * currentFrame;
	destRect.y = areaTexture.height * currentRow;
	destRect.w = areaTexture.width;
	destRect.h = areaTexture.height;
	srcRect.x = 0;
	srcRect.y = 0;

	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id,
	int _x,
	int _y,
	int width,
	int height,
	int currentRow,
	int currentFrame,
	int alpha,
	double angle,
	SDL_Renderer * pRenderer,
	SDL_RendererFlip flip)
{
	Uint32 frameStart, frameTime;
	frameStart = SDL_GetTicks();
	if (m_TextureMap.find(id) == m_TextureMap.end())
	{
		return;
	}
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Texture * pTexture = m_TextureMap.at(id);
	SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	//destRect.x = width * currentFrame;
	//destRect.y = height * currentRow;
	//destRect.w = width;
	//destRect.h = height;
	//srcRect.x = 0;
	//srcRect.y = 0;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = _x;
	destRect.y = _y;

	//SDL_SetTextureAlphaMod(m_TextureMap.at(id), alpha);
	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, angle, 0, flip);
	SDL_Delay(50);
	//frameTime = SDL_GetTicks() - frameStart;
	//if (frameTime < DELAY_TIME)
	//{
	//	SDL_Delay((int)(DELAY_TIME - frameTime));
	//}
}

void TextureManager::release()
{
	if (s_pTexure)
	{
		delete s_pTexure;
	}
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_TextureMap.erase(id);
}

void TextureManager::drawTile(const std::string & id,
	int margin,
	int spacing,
	int x,
	int y,
	int width,
	int height,
	int row,
	int column,
	int tileHeight,
	int tileWidth,
	SDL_Renderer * pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 2 * margin + (spacing * (column - 1)) + column * tileWidth;
	srcRect.y = 2 * margin + (spacing * (row - 1)) + row * tileHeight;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = abs(x) - tileWidth;
	destRect.y = abs(y) - tileHeight;

	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawTile(const std::string & id,
	int tileID,
	Tileset & tileset,
	int row,
	int column,
	int columnIncr,
	SDL_Renderer * pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	int tilesetX;
	int tilesetY;
	int tileColumn;
	int tileRow = 0;
	tileColumn =tileID - tileset.firstGridID;
	while (tileColumn >= tileset.numColumns)
	{
		tileColumn -= tileset.numColumns;
		tileRow++;
	}
	tilesetX = tileColumn * tileset.tileWidth + 2 * tileset.margin + (tileColumn - 1)*tileset.spacing;
	tilesetY = tileRow * tileset.tileHeight + (tileRow - 1)*tileset.spacing;

	srcRect.x = tilesetX;
	srcRect.y = tilesetY;
	
	srcRect.w = destRect.w = tileset.tileWidth;
	srcRect.h = destRect.h = tileset.tileHeight;

	//destRect.x = 2 * tileset.margin + (tileset.spacing * (column - 1)) + column * tileset.tileWidth;
	//destRect.y = 2 * tileset.margin + (tileset.spacing * (row - 1)) + row * tileset.tileHeight;

	destRect.x = (column - columnIncr) * tileset.tileWidth;
	destRect.y = 2 * tileset.margin + (tileset.spacing * (row - 1)) + row * tileset.tileHeight;

	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
