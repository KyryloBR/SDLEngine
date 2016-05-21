#ifndef LOADERPARAMS_H_
#define LOADERPARAMS_H_

#include "stdafx.h"

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, const std::string & textureID) : m_x(x), m_y(y),
		m_width(width), m_height(height), m_textureID(textureID)
	{
	}
	~LoaderParams() {};

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }

	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }
	void setWidth(int width) { m_width = width; }
	void setHeight(int height) { m_height = height; }

private:
	int m_x;
	int m_y;

	int m_width;
	int m_height;
	
	std::string m_textureID;
};
#endif // LOADERPARAMS_H_