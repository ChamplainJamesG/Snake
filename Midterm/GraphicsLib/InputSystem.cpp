#include "InputSystem.h"
#include "EventSystem.h"

InputSystem::InputSystem()
{
	if (!isInit)
	{
		mEventQueue = NULL;
		al_install_mouse();
		al_install_keyboard();
		mEventQueue = al_create_event_queue();

		al_register_event_source(mEventQueue, al_get_keyboard_event_source());
		isInit = true;
	}
}

InputSystem::~InputSystem()
{
	if (isInit)
	{
		al_destroy_event_queue(mEventQueue);
	}
}

void InputSystem::init()
{
	if (!isInit)
	{
		al_install_mouse();
		al_install_keyboard();
		mEventQueue = al_create_event_queue();

		al_register_event_source(mEventQueue, al_get_mouse_event_source());
		isInit = true;
	}
}

void InputSystem::cleanup()
{
	if(isInit)
		al_destroy_event_queue(mEventQueue);
}

void InputSystem::update()
{
	ALLEGRO_KEYBOARD_STATE state;
	al_get_keyboard_state(&state);

	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	//al_wait_for_event(mEventQueue, &mEvent);

	//al_wait_for_event(mEventQueue, &mEvent);
	/*
	if (al_key_down(&state, ALLEGRO_KEY_ENTER)/*mEvent.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (mEvent.keyboard.keycode)
		{
		case ALLEGRO_KEY_ENTER:
			EventSystem::getInstance()->fireEvent(AL_CHANGE_EVENT);
			break;

		case ALLEGRO_KEY_SPACE:
			EventSystem::getInstance()->fireEvent(AL_FREEZE_EVENT);
			break;

		}
	}
	*/
	while (al_get_next_event(mEventQueue, &mEvent))
	{
		if (mEvent.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_W || mEvent.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				//EventSystem::getInstance()->fireEvent(change_up)
				EventSystem::getInstance()->fireEvent(MOVE_UP);
			}

			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_A || mEvent.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				//EventSystem::getInstance()->fireEvent(change_left)
				EventSystem::getInstance()->fireEvent(MOVE_LEFT);

			}

			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_S || mEvent.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				//EventSystem::getInstance()->fireEvent(change_down);
				EventSystem::getInstance()->fireEvent(MOVE_DOWN);

			}

			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_D || mEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				//eventSystem::getInstance()->fireEvent(change_right);
				EventSystem::getInstance()->fireEvent(MOVE_RIGHT);

			}

			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_ENTER)
			{
				EventSystem::getInstance()->fireEvent(TEST_MAKE_PLAYER);
			}

			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_SPACE)
			{
				EventSystem::getInstance()->fireEvent(START_LEVEL);
				EventSystem::getInstance()->fireEvent(START_GAME);
			}

			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				EventSystem::getInstance()->fireEvent(EXIT);
			}

		}

	}

	if (al_key_down(&state, ALLEGRO_KEY_ESCAPE))
	{
		EventSystem::getInstance()->fireEvent(AL_QUIT_EVENT);
	}
	/*
	if (al_key_down(&state, ALLEGRO_KEY_ENTER))
	{
		EventSystem::getInstance()->fireEvent(AL_CHANGE_EVENT);
	}
	*/

	if (al_key_down(&state, ALLEGRO_KEY_SPACE))
	{
		EventSystem::getInstance()->fireEvent(AL_FREEZE_EVENT);
	}

	if (mEvent.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		EventSystem::getInstance()->fireEvent(MOVE_EVENT);
	}

	if (mouseState.buttons & 1)
	{
		EventSystem::getInstance()->fireEvent(AL_ADD_EVENT);
	}

	if (mouseState.buttons & 2)
	{
		EventSystem::getInstance()->fireEvent(AL_DELETE_EVENT);
	}
}