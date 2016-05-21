#ifndef PRINTIMAGE_H_
#define PRINTIMAGE_H_

#include "EGameObject.h"

class PrintImage : public EGameObject
{
public:
	PrintImage(const LoaderParams * pPararms);

	void update();

};

#endif // PRINTIMAGE_H_