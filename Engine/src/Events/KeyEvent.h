#pragma once
#include "Core.h"
#include "Event.h"

namespace Engine
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(int keycode, bool isRepeat = false)
			: keycode(keycode), isRepeat(isRepeat) {}

		int GetKeyCode() const { return keycode; }
		bool GetIsRepeat() const { return isRepeat; }

		EVENT_CLASS_TYPE(KeyPressed);
		EVENT_CLASS_CATEGORY(EventCategory_Input | EventCategory_Keyboard);
	private:
		int keycode;
		bool isRepeat;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int keycode) : keycode(keycode) {}
		int GetKeyCode() const { return keycode; }

		EVENT_CLASS_TYPE(KeyReleased);
		EVENT_CLASS_CATEGORY(EventCategory_Input | EventCategory_Keyboard);

	private:
		int keycode;
	};
}