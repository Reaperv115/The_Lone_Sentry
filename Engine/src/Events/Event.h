#pragma once
#include "Core.h"

namespace Engine
{
	enum EventType
	{
		None = 0,
		WindowClose, WindowResize,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		EventCategory_Window =		BIT(0),
		EventCategory_Input =		BIT(1),
		EventCategory_Keyboard =	BIT(2),
		EventCategory_Mouse =		BIT(3),
		EventCategory_MouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)														\
	static EventType GetStaticType() {return EventType::type;}					\
	virtual EventType GetEventType() const override {return GetStaticType();}		\
	virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category)												\
	virtual int GetCategoryFlags() const override {return category;}

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		bool handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : _event(event)
		{
		}
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (_event.GetEventType() == T::GetStaticType())
			{
				_event.handled |= func(static_cast<T&>(_event));
				return true;
			}
			return false;
		}
	private:
		Event& _event;

	};
}