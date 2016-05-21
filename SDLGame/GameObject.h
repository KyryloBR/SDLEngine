#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "stdafx.h"
#include "TextureManager.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual std::string getType() = 0;
	std::string getTextureID() { return m_textureID; }
	Vector2D * getPosition() { return &m_position; }
	void setPosition(Vector2D _position) { m_position = _position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	void setHeight(int _height) { m_height = _height; }
	void setWidth(int _width) { m_width = _width; }
	void scroll(float scrollSpeed) { m_position.setX(m_position.getX() - scrollSpeed); }
	bool isDead() { return m_bDead; }
	bool dying() { return m_bDying; }
	void setAlpha(int alpha) { m_alpha = alpha; }
	int getAlpha() { return m_alpha; }
	void setAngle(double _angle) { m_angle = _angle; }
	double getAngle() { return m_angle; }

	void setRendeering(bool bRendering) { m_bRendering = bRendering; }
	bool isRendering() { return m_bRendering; }

	virtual void load(const LoaderParams * pParams) = 0;

protected:

	SDL_RendererFlip m_nFlip;
	Vector2D  m_position;
	Vector2D  m_velocity;
	Vector2D  m_acceleration;
	int m_width;
	int m_height;
	std::string m_textureID;
	bool m_bDead;
	bool m_bDying;
	double m_angle;
	int m_alpha;
	bool m_bRendering;

	GameObject() : m_position(0, 0), m_acceleration(0, 0), m_velocity(0, 0),
		m_width(0), m_height(0), m_angle(0.0), m_bDead(false), m_bDying(false), m_alpha(255),m_bRendering(false) {}
	virtual ~GameObject() {}
};

#endif //GAMEOBJECT_H_