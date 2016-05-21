#include "NumberAnimation.h"
#include "GameObject.h"

NumberAnimation::NumberAnimation(const std::string & animationID) : Animation(animationID)
{
	m_params.insert(std::make_pair("scale", 0.0));
	m_params.insert(std::make_pair("alpha", 0.0));
	m_params.insert(std::make_pair("angle", 0.0));
	m_params.insert(std::make_pair("width", 0.0));
	m_params.insert(std::make_pair("height", 0.0));
}

void NumberAnimation::setParametr(const std::string & _param, double _value)
{
	m_currentParam = _param;
	if (_param == "scale")
	{
		m_params[_param] = _value;
		setScale();
	}
	else if (_param == "angle")
	{
		m_params[_param] = _value;
		setAngle();
	}
	else if (_param == "alpha")
	{
		m_params[_param] = _value;
		setAlpha();
	}
	else if (_param == "width")
	{
		m_params[_param] = _value;
		setWidth();
	}
	else if (_param == "height")
	{
		m_params[_param] = _value;
		setHeight();
	}
	else
	{
		m_currentParam = "";
	}
}

void NumberAnimation::setDuration(int _seconds)
{
	m_duration = _seconds;
}

double NumberAnimation::getValue(const std::string & _param)
{
	std::map<std::string, double>::iterator it = m_params.find(_param);
	return it->second;
}

void NumberAnimation::update()
{
	if (m_bRunning)
	{
		if (m_currentParam != "")
		{
			if (m_currentParam == "scale")
			{
				updateScale();
			}
			if (m_currentParam == "alpha")
			{
				updateAlpha();
			}
			if (m_currentParam == "angle")
			{
				updateAngle();
			}
			if (m_currentParam == "width")
			{
				updateWidth();
			}
		}
	}
}

// Private methods.
// Methods are install params.
void NumberAnimation::setScale()
{
	std::map<std::string, double>::iterator it = m_params.find("scale");
	m_velocity = (it->second/* - 1*/) / (m_duration * 1000);
	m_currentValue = 1.0;
}

void NumberAnimation::setAngle()
{
	std::map<std::string, double>::iterator it = m_params.find("angle");
	m_velocity = (it->second / (m_duration * 1000));
	m_currentValue = 0.0;
}

void NumberAnimation::setAlpha()
{
	std::map<std::string, double>::iterator it = m_params.find("alpha");
	m_velocity = (it->second - m_objectAnimation->getAlpha()) / (m_duration * 1000);
	m_currentValue = m_objectAnimation->getAlpha();
}

void NumberAnimation::setWidth()
{
	std::map<std::string, double>::iterator it = m_params.find("width");
	m_velocity = (it->second - m_objectAnimation->getWidth()) / (m_duration * 1000);
	m_currentValue = m_objectAnimation->getWidth();
}

void NumberAnimation::setHeight()
{
	std::map<std::string, double>::iterator it = m_params.find("height");
	m_velocity = (it->second - m_objectAnimation->getHeight()) / (m_duration * 1000);
	m_currentValue = m_objectAnimation->getHeight();
}

// Methods are update params.

void NumberAnimation::updateScale()
{
	std::map<std::string, double>::iterator it = m_params.find("scale");
	if (m_bReverse)
	{
		if (m_velocity > 0)
		{
			if (it->second <= m_currentValue)
			{
				m_velocity = -m_velocity;
			}
		}
		else
		{
			if (m_currentValue <= 1)
			{
				m_velocity = -m_velocity;
			}
		}
		m_currentValue += m_velocity;
	}
	else
	{
		if (it->second <= m_currentValue)
		{
			m_currentValue += m_velocity;
		}
	}
	m_objectAnimation->setHeight(100 * m_currentValue);
	m_objectAnimation->setWidth(200 * m_currentValue);
}

void NumberAnimation::updateAlpha()
{
	std::map<std::string, double>::iterator it = m_params.find("alpha");
	if (m_velocity > 0)
	{
		if (it->second >= m_currentValue)
		{
			m_velocity = -m_velocity;
		}
	}
	else
	{
		if (it->second >= m_currentValue)
		{
			m_velocity = -m_velocity;
		}
	}
	m_currentValue += m_velocity;
	m_objectAnimation->setAlpha(m_currentValue);
}

void NumberAnimation::updateAngle()
{
	std::map<std::string, double>::iterator it = m_params.find("angle");
	if (m_bReverse)
	{
		if (m_currentValue >= it->second || m_currentValue < it->second - it->second)
		{
			stop();
			m_velocity = -m_velocity;
			play();
		}
	}
	else
	{
		if (m_currentValue >= it->second)
		{
			stop();
		}
	}
	m_currentValue += m_velocity;
	m_objectAnimation->setAngle(m_currentValue);
}

void NumberAnimation::updateWidth()
{
	std::map<std::string, double>::iterator it = m_params.find("width");
	if (m_bReverse)
	{
		if (m_currentValue >= it->second || m_currentValue < it->second - it->second)
		{
			stop();
			m_velocity = -m_velocity;
			play();
		}
	}
	else
	{
		if (m_currentValue >= it->second)
		{
			stop();
		}
	}
	m_currentValue += m_velocity;
	m_objectAnimation->setWidth(m_currentValue);
}

void NumberAnimation::updateHeight()
{
	std::map<std::string, double>::iterator it = m_params.find("height");
	if (m_bReverse)
	{
		if (m_currentValue >= it->second || m_currentValue < it->second - it->second)
		{
			stop();
			m_velocity = -m_velocity;
			play();
		}
	}
	else
	{
		if (m_currentValue >= it->second)
		{
			stop();
		}
	}
	m_currentValue += m_velocity;
	m_objectAnimation->setHeight(m_currentValue);
}