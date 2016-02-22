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
		RELEASED,
		PRESSED
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

	struct KeyEvent
	{
		int SDLCode;
		KeyCode keyCode;
		InputState keyState;
	};

	void initKeySystem();
	void exitKeySystem();

	void postKeyEvent(KeyEvent evnt);
	bool getKeyState(const KeyCode code);
	bool getKeyState(std::string keyname);
	KeyCode SDLToKeyCode(const int SDLCode);

	extern std::map<std::string, KeyCode> keyBinds;
	void registerKeybind(KeyCode keycode, std::string name);

	extern std::map<std::string, std::function<void(const KeyEvent)>> keyListeners;
	void registerKeyListener(std::function<void(const KeyEvent)> listener, std::string listenerID);
	void removeKeyListener(std::string listnerID);
	void callKeyListeners(const KeyEvent evnt);

#define UK_ADD_KEY_LISTENER_INTERNAL(listener, id) ::Unknown::registerKeyListener([this](::Unknown::KeyEvent evnt) { listener(evnt); }, id);
#define UK_ADD_KEY_LISTENER_EXTERNAL(listener, id) ::Unknown::registerKeyListener([](::Unknown::KeyEvent evnt) { listener(evnt); }, id);
#define UK_REMOVE_KEY_LISTENER(id) ::Unknown::removeKeyListener(id);

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

#define UK_ADD_MOUSE_LISTENER_INTERNAL(listener, id) ::Unknown::registerMouseListener([this](::Unknown::MouseEvent evnt) {listener(evnt);}, id);
#define UK_ADD_MOUSE_LISTENER_EXTERNAL(listener, id) ::Unknown::registerMouseListener([](::Unknown::MouseEvent evnt) {listener(evnt);}, id);
#define UK_REMOVE_MOUSE_LISTENER(id) ::Unknown::removeMouseListener(id);
}

#endif