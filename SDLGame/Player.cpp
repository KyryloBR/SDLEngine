#include "Player.h"
#include "InputHandler.h"
#include "Game.h"
#include "LoopAnimation.h"
#include "AnimationParser.h"
#include "CollisionManager.h"
#include "BulletHandler.h"
#include "AnimationHandler.h"

Player::Player() : EGameObject()
{
	m_bDying = false;
	m_nEndurance = 100;
	m_bDead = false;
	m_bAttack = false;
	m_nHealth = 100;
	m_nDamage = 33;
	m_bRendering = true;
	AnimationParser parser;
	parser.parseAnimation(m_animations, "../Data/animations.xml","Player");
	m_animations["Walking"]->setLoopAlways(true);
	m_animations["Punching"]->setLoopAlways(true);
	m_animations["Combos"]->setLoopAlways(true);
	m_pCurrentAnimation = m_animations["Idle"];
	m_pCurrentAnimation->play();
	m_nFlip = SDL_FLIP_HORIZONTAL;
	m_nCountBullet = 0;
}

void Player::load(const LoaderParams * pParams)
{
	EGameObject::load(pParams);
}

void Player::draw()
{
	TextureManager::Instance()->draw(m_pCurrentAnimation->getCurrentId(), (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_alpha, m_angle,
		Game::Instance()->getRenderer(),m_nFlip);
}

void Player::update()
{
	if (!m_bDead)
	{
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_acceleration.setX(0);
		m_acceleration.setY(0);

		handleMovement();
		handleInput();

		m_pCurrentAnimation->update();

		CollisionManager::Instance()->checkPlayerEnemyCollision();

		EGameObject::update();
		m_position += m_acceleration;
		if (m_nHealth <= 0)
		{
			m_bDead = true;
			Game::Instance()->setPlayerLives(Game::Instance()->getPlayerLives() - 1);
		}
		m_nCountBullet = BulletHandler::Instance()->getBulletPlayer().size();
		if (m_nEndurance < 100)
		{
			m_nEndurance += _ENDURANCE_ROLLBACK_;
		}
	}
}

void Player::clean()
{

}

void Player::handleInput()
{
	InputHandler::Instance()->update();
	if (InputHandler::Instance()->isJoystickInitialised())
	{
		if (InputHandler::Instance()->xvalue(0, 1) > 0 || InputHandler::Instance()->xvalue(0, 1) < 0)
		{
			m_velocity.setX(1 * InputHandler::Instance()->xvalue(0, 1));
		}
		if (InputHandler::Instance()->yvalue(0, 1) > 0 || InputHandler::Instance()->yvalue(0, 1) < 0)
		{
			m_velocity.setY(1 * InputHandler::Instance()->yvalue(0,1));
		}
		if (InputHandler::Instance()->xvalue(0, 2) > 0 || InputHandler::Instance()->xvalue(0, 2) < 0)
		{
			m_velocity.setX(1 * InputHandler::Instance()->xvalue(0, 2));
		}
		if (InputHandler::Instance()->yvalue(0, 2) > 0 || InputHandler::Instance()->yvalue(0, 2) < 0)
		{
			m_velocity.setY(1 * InputHandler::Instance()->yvalue(0, 2));
		}
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && m_bForward && !m_bAttack)
		{
			m_velocity.setX(10);
			m_pCurrentAnimation = m_animations["Walking"];
			m_animations["Walking"]->play();
			m_nFlip = SDL_FLIP_HORIZONTAL;
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_bBack && !m_bAttack)
		{
			m_nFlip = SDL_FLIP_NONE;
			m_velocity.setX(-10);
			m_pCurrentAnimation = m_animations["Walking"];
			m_pCurrentAnimation->play();
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_bUp && !m_bAttack)
		{
			m_velocity.setY(-10);
			m_pCurrentAnimation = m_animations["Walking"];
			m_pCurrentAnimation->play();
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) && m_bDown && !m_bAttack)
		{
			m_velocity.setY(10);
			m_pCurrentAnimation = m_animations["Walking"];
			m_pCurrentAnimation->play();
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && m_nCountBullet <= 2)
		{
			if (m_nFlip == SDL_FLIP_HORIZONTAL)
			{
				BulletHandler::Instance()->addPlayerBullet(m_position.getX() - 30, m_position.getY() + (m_height / 2), 40, 10, m_button, Vector2D(-20, 0));
			}
			else
			{
				BulletHandler::Instance()->addPlayerBullet(m_position.getX() + m_width, m_position.getY() + (m_height / 2), 40, 10, m_button, Vector2D(20, 0));
			}
		}
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) && !m_bAttack && m_nEndurance > _ENDURANCE_ON_HIT_)
		{
			m_pCurrentAnimation = m_animations["Punching"];
			m_pCurrentAnimation->play();
			m_bAttack = true;
			m_nEndurance -= _ENDURANCE_ON_HIT_;
		}
		else if (m_pCurrentAnimation->getID() == std::string("Punching") && m_pCurrentAnimation->getCurrentIndex() > m_pCurrentAnimation->getCountFrames() - 2)
		{
			m_bAttack = false;
			m_pCurrentAnimation = m_animations["Idle"];
			m_pCurrentAnimation->play();
		}
	//http://www.spriters-resource.com/snes/mortalkombat3/
}

void Player::ressurect()
{
	Game::Instance()->setPlayerLives(Game::Instance()->getPlayerLives() - 1);
	m_position.setX(10);
	m_position.setY(240);
	m_bDying = false;

	m_textureID = "player";

	m_width = 101;
	m_height = 46;

}

void Player::handleAnimation()
{
	//if (m_invulnerable)
	//{
	//	if (m_invulnerableCounter == m_invulnerableTime)
	//	{
	//		m_invulnerable = false;
	//		m_invulnerableCounter = 0;
	//		m_alpha = 255;
	//	}
	//	else
	//	{
	//		if (m_alpha == 255)
	//		{
	//			m_alpha = 0;
	//		}
	//		else
	//		{
	//			m_alpha = 255;
	//		}
	//	}
	//	m_invulnerableCounter++;
	//}

	//if (!m_bDead)
	//{
	//	if (m_velocity.getX() < 0)
	//	{
	//		m_angle = 10.0;
	//	}
	//	else
	//	{
	//		m_angle = 0.0;
	//	}
	//}
	//m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}


void Player::handleMovement()
{
	if (m_position.getY() + m_height <= m_nEarthBorder - 10)
	{
		m_bUp = false;
	}
	else
	{
		m_bUp = true;
	}

	if (m_position.getY() + m_height >= 470)
	{
		m_bDown = false;
	}
	else
	{
		m_bDown = true;
	}

	if (m_position.getX() <= 0)
	{
		m_bBack = false;
	}
	else
	{
		m_bBack = true;
	}

	if (m_position.getX() >= 590)
	{
		m_bForward = false;
	}
	else
	{
		m_bForward = true;
	}
}