#pragma once
#include "Event.h"

namespace Engine
{
	class MouseButtonPressedEvent : public Event 
	{
	public:
		MouseButtonPressedEvent(unsigned int button)
			: button(button) {}
		EVENT_CLASS_TYPE(MouseButtonPressed);
		EVENT_CLASS_CATEGORY(EventCategory_MouseButton | EventCategory_Mouse | EventCategory_Input);

		unsigned int GetMousButton() const { return button; }

	private:
		unsigned int button;
	};

	class MouseButtonReleasedEvent : public Event 
	{
	public:
		MouseButtonReleasedEvent(unsigned int button)
			: button(button) {}
		EVENT_CLASS_TYPE(MouseButtonReleased);
		EVENT_CLASS_CATEGORY(EventCategory_MouseButton | EventCategory_Mouse | EventCategory_Input);

		unsigned int GetMouseButton() const { return button; }

	private:
		unsigned int button;
	};
}