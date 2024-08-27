#ifndef __InputHandler__
#define __InputHandler__

#include <vector>
#include <utility>

#include <SDL.h>
#include "Vector2D.h"


class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	void update();
	void clean();

	bool isKeyDown(SDL_Scancode key);

private:
	InputHandler() {};
	~InputHandler() {}

	static InputHandler* s_pInstance;

	const Uint8* m_keystates;

	void onKeyDown();
	void onKeyUp();

};
typedef InputHandler TheInputHandler;

#endif // __InputHandler__