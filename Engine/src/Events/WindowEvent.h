#pragma once
#include "Event.h"

namespace Engine
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategory_Window);
	};
	
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: _width(width), _height(height)
		{}
		unsigned int GetWidth() const { return _width; }
		unsigned int GetHeight() const { return _height; }

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategory_Window);
	private:
		unsigned int _width, _height;
	};

	
}