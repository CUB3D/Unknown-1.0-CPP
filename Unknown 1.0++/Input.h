#ifndef INPUT_H
#define INPUT_H

#define MAX_STATES 512

#include <vector>

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

	void postKeyEvent(KeyEvent evnt);
	bool getKeyState(const KeyCode code);
	KeyCode SDLToKeyCode(const int SDLCode);

	extern std::vector < void(*) (const KeyEvent evnt) > keyListeners;
	void registerKeyListener(void(*listener) (const KeyEvent evnt));
	void callKeyListeners(const KeyEvent evnt);

	#define UK_KEY_LISTENER(x) Unknown::registerKeyListener(x);

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
	};

	void postMouseEvent(MouseEvent evnt);
	bool getMouseButtonState(const MouseButton button);
	MouseButton SDLTOMouseButton(const int SDLCode);

	extern std::vector<void(*) (const MouseEvent evnt) > mouseListeners;
	void registerMouseListener(void(*listener) (const MouseEvent evnt));
	void callMouseListeners(const MouseEvent evnt);

	#define UK_MOUSE_LISTENER(x) Unknown::registerMouseListener(x);
}

#endif

