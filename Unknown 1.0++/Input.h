#ifndef INPUT_H
#define INPUT_H

#define MAX_STATES 512

#include "Utils.h"

#include <vector>
#include <functional>
#include <map>

namespace Unknown
{
	// Generic input

	enum InputState
	{
		RELEASED = 0,
		PRESSED = 1
	};

	// Keyboard input

	static bool keyStates[MAX_STATES];

	enum KeyCode
	{
		KEY_NONE,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN
	};


	void initKeySystem();
	void exitKeySystem();

	bool getKeyState(const KeyCode code);
	bool getKeyState(std::string keyname);
	KeyCode SDLToKeyCode(const int SDLCode);

	extern std::map<std::string, KeyCode> keyBinds;
	void registerKeybind(KeyCode keycode, std::string name);

	// Mouse input

	static bool mouseButtonStates[MAX_STATES];

	enum MouseButton
	{
		BUTTON_NONE,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_MIDDLE
	};

	struct MouseEvent
	{
		int SDLButtonCode;
		MouseButton mouseButton;
		InputState buttonState;
		Point<int> location;
	};

	void postMouseEvent(MouseEvent evnt);
	bool getMouseButtonState(const MouseButton button);
	MouseButton SDLTOMouseButton(const int SDLCode);

	extern std::map<std::string, std::function<void(const MouseEvent)>> mouseListeners;
	void registerMouseListener(std::function<void(const MouseEvent)> listener, std::string listenerID);
	void removeMouseListener(std::string listnerID);
	void callMouseListeners(const MouseEvent evnt);

	Point<int> getMouseLocation();

#define UK_ADD_MOUSE_LISTENER_INTERNAL(listener, id) ::Unknown::registerMouseListener([this](::Unknown::MouseEvent evnt) {listener(evnt);}, id)
#define UK_ADD_MOUSE_LISTENER_EXTERNAL(listener, id) ::Unknown::registerMouseListener([](::Unknown::MouseEvent evnt) {listener(evnt);}, id)
#define UK_REMOVE_MOUSE_LISTENER(id) ::Unknown::removeMouseListener(id)
#define UK_GET_MOUSE_POS(point) SDL_GetMouseState(&p.x, &p.y)
}

#endif
