#ifndef ADDITIONALTYPE_H_
#define ADDITIONALTYPE_H_

namespace AdditionalType
{
	typedef struct Point2d
	{
		int x;
		int y;
	} POINT2;

	typedef struct Point3d
	{
		int x;
		int y;
		int z;
	} POINT3;

	typedef	struct Rect
	{
		POINT2 beginRect;
		int height;
		int width;
	} RECT2;
}

#endif