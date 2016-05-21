#ifndef LAYER_H_
#define LAYER_H_

#include "stdafx.h"

class Layer
{
public:
	
	virtual void render() = 0;
	virtual void update() = 0;
	void setNameLayer(const std::string & layer) { m_layerName = layer; }

	std::string getNameLayer() { return m_layerName; }

protected:
	std::string m_layerName;
	virtual ~Layer() {}
};

#endif // LAYER_H_