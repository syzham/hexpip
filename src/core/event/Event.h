#ifndef HEXPIP_EVENT_H
#define HEXPIP_EVENT_H

enum class EventType
{
	None = 0,
	KeyPressed, KeyReleased, KeyHold,
	MouseButtonPressed, MouseButtonReleased, MouseMoved
};

class Event
{
public:
	virtual ~Event() = default;

	bool Handled = false;

	[[nodiscard]] virtual EventType GetEventType() const = 0;

	[[nodiscard]] bool IsInCategory(const EventType category) const
	{
		return GetEventType() == category;
	}
};

class EventDispatcher
{
public:
	explicit EventDispatcher(Event& event)
	: m_Event(event)
	{
	}

	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.Handled |= func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};

#endif //HEXPIP_EVENT_H