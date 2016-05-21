#ifndef NUMBER_ANIMATION_H_
#define NUMBER_ANIMATION_H_

#include "Animation.h"
#include "stdafx.h"

class NumberAnimation : public Animation
{
public:
	// Constructor.
	NumberAnimation(const std::string & animationID);
	
	// Methods for set params.
	void setParametr(const std::string & _param, double _value);
	void setReverse(bool _reverse) { m_bReverse = _reverse; }
	void setDuration(int _seconds);
	// Set duration animation in seconds.

	// Public methods for get params.
	std::string getID() { return m_animationID; }
	double getValue(const std::string & _param);
	std::string getCurrentParam() { return m_currentParam; }
	std::string getTextureIDObjectParent() 
	{	
		return m_objectAnimation->getTextureID();
	}
	
	// Public methods for playing animation.
	virtual void update();

private:
	// Private property.
	std::map<std::string, double> m_params;
	int m_duration;
	float m_velocity;
	double m_currentValue;
	std::string m_currentParam;
	bool m_bReverse;

	// Private methods for install params.
	void setScale();
	void setAlpha();
	void setAngle();
	void setWidth();
	void setHeight();

	// Private methods for update params.
	void updateScale();
	void updateAlpha();
	void updateAngle();
	void updateWidth();
	void updateHeight();
};

#endif // NUMBER_ANIMATION_H_