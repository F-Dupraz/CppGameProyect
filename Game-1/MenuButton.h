#pragma once

#ifndef __MenuButton__
#define __MenuButton__

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton(const LoaderParams* pParams, void (*callback) ());

	virtual void draw();
	virtual void update();
	virtual void clean();

	bool m_bReleased;

private:

	void (*m_callback) ();

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 0,
		CLICKED = 1,
	};
};

#endif // __MenuButton__