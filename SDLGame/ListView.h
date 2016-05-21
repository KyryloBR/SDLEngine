#ifndef LISTVIEW_H_
#define LISTVIEW_H_

#include "EGameObject.h"
#include <list>

enum RESULT_LIST_VIEW { LV_OK = 0x001, LV_INCREASE_INVALID, LV_DECREASE_INVALID};

class ListView : public EGameObject
{
public:
	ListView() : m_nCurrentIndex(0) {}
	~ListView() {}

	virtual void update();
	virtual void draw();
	virtual void load(LoaderParams * pParams);
	virtual void clean();

	void push_back(GameObject * pObj);
	void pop_back();

	RESULT_LIST_VIEW increase();
	RESULT_LIST_VIEW decrease();

	GameObject * operator[](int index);

private:
	std::vector<GameObject*> m_Objects;
	int m_nCurrentIndex;
};

#endif // LISTVIEW_H_