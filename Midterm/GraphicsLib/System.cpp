#include "System.h"
#include "allegro5\allegro.h"

const std::string FONT_FILE = "cour.ttf";

System::System()
{
	mGraphicsSystem = NULL;
}

System::System(GraphicsSystem *graphicsSystem)
{
	mGraphicsSystem = graphicsSystem;
}

System::~System()
{
	//mGraphicsSystem->~GraphicsSystem();
	delete(mGraphicsSystem);
	delete(mInputSystem);
	mGraphicsSystem = NULL;
	mInputSystem = NULL;
}

void System::init(float width, float height)
{
	al_init();
	mGraphicsSystem = new GraphicsSystem();
	mGraphicsSystem->initGraphicsSystem(width, height);
	mInputSystem = new InputSystem();
	al_install_mouse();
	al_install_keyboard();
	al_init_ttf_addon();
	assert(mGraphicsSystem);

	mFont = Font(FONT_FILE, 24);
}

void System::cleanup()
{
	mGraphicsSystem->cleanupGraphicsSystem();
	delete(mGraphicsSystem);
	mGraphicsSystem = NULL;
}

KEYS System::getKeyState()
{
	ALLEGRO_KEYBOARD_STATE state;
	al_get_keyboard_state(&state);
	if (al_key_down(&state, ALLEGRO_KEY_F))
	{
		return F;
	}
	else if (al_key_down(&state, ALLEGRO_KEY_S))
	{
		return S;
	}

	else if (al_key_down(&state, ALLEGRO_KEY_ENTER))
	{
		return ENTER;
	}

	else if (al_key_down(&state, ALLEGRO_KEY_ESCAPE))
	{
		return ESC;
	}

	else if (al_key_down(&state, ALLEGRO_KEY_SPACE))
	{
		return SPACE;
	}

	else
	{
		return INVALID_KEY;
	}
}

void System::getMouseState(Vector2D origLoc, bool &leftClick, bool &rightClick)
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	if (state.buttons & 1)
	{
		//return Vector2D(state.x, state.y);
		leftClick = true;
	}

	else if (state.buttons & 2)
	{
		//destroy a sprite
		rightClick = true;
	}

	else
	{
		return;
	}

}

void System::update()
{
	mInputSystem->update();
}

Vector2D System::getMouseLoc()
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);

	return Vector2D(state.x, state.y);
}

void System::flip()
{
	mGraphicsSystem->flip();
}

void System::doHud(int fps, int score)
{
	std::string text = "FPS: " + to_string(fps);
	std::string text2 = "Score: " + to_string(score);
	GraphicsSystem::writeText(Vector2D(100, 0), mFont, Color(0, 0, 0), text);
	GraphicsSystem::writeText(Vector2D(100, 25), mFont, Color(0, 0, 0), text2);
}