#include "stdafx.h"
#include "Input.h"

#include <SDL.h>
#include <vector>
#include <functional>
#include <map>

void Unknown::postKeyEvent(KeyEvent evnt)
{
	KeyCode code = SDLToKeyCode(evnt.SDLCode);

	evnt.keyCode = code;

	keyStates[code] = (evnt.keyState == InputState::PRESSED);

	callKeyListeners(evnt);
}

Unknown::KeyCode Unknown::SDLToKeyCode(const int SDLCode)
{
	switch (SDLCode)
	{
	case SDLK_LEFT:
		return KeyCode::KEY_LEFT;
		break;
	case SDLK_RIGHT:
		return KeyCode::KEY_RIGHT;
		break;
	case SDLK_UP:
		return KeyCode::KEY_UP;
		break;
	case SDLK_DOWN:
		return KeyCode::KEY_DOWN;
		break;
	default:
		return KeyCode::KEY_NONE;
		break;
	}
}

bool Unknown::getKeyState(const KeyCode code)
{
	return keyStates[code];
}

bool Unknown::getKeyState(std::string keyname)
{
	return getKeyState(keyBinds[keyname]);
}

std::map<std::string, Unknown::KeyCode> Unknown::keyBinds;

void Unknown::registerKeybind(Unknown::KeyCode keycode, std::string name)
{
	keyBinds[name] = keycode;
}

std::map <std::string, std::function<void(const Unknown::KeyEvent)> > Unknown::keyListeners;

void Unknown::registerKeyListener(std::function<void(const KeyEvent)> listener, std::string listenerID)
{
	keyListeners[listenerID] = listener;
}

void Unknown::removeKeyListener(std::string listnerID)
{
	keyListeners.erase(listnerID);
}

void Unknown::callKeyListeners(const KeyEvent evnt)
{
	std::map <std::string, std::function<void(const Unknown::KeyEvent)> >::iterator listeners;

	for (listeners = keyListeners.begin(); listeners != keyListeners.end(); listeners++)
	{
		listeners->second(evnt);
	}
}

void Unknown::postMouseEvent(MouseEvent evnt)
{
	MouseButton button = SDLTOMouseButton(evnt.SDLButtonCode);

	evnt.mouseButton = button;

	mouseButtonStates[button] = (evnt.buttonState == InputState::PRESSED);

	callMouseListeners(evnt);
}

bool Unknown::getMouseButtonState(const MouseButton button)
{
	return mouseButtonStates[button];
}

Unknown::MouseButton Unknown::SDLTOMouseButton(const int SDLCode)
{
	switch (SDLCode)
	{
	case SDL_BUTTON_LEFT:
		return MouseButton::BUTTON_LEFT;
		break;
	case SDL_BUTTON_RIGHT:
		return MouseButton::BUTTON_RIGHT;
		break;
	case SDL_BUTTON_MIDDLE:
		return MouseButton::BUTTON_MIDDLE;
		break;
	default:
		return MouseButton::BUTTON_NONE;
		break;
	}
}

std::map <std::string, std::function<void(const Unknown::MouseEvent)> > Unknown::mouseListeners;

void Unknown::registerMouseListener(std::function<void(const Unknown::MouseEvent)> listener, std::string listenerID)
{
	mouseListeners[listenerID] = listener;
}

void Unknown::removeMouseListener(std::string listenerID)
{
	mouseListeners.erase(listenerID);
}

void Unknown::callMouseListeners(const MouseEvent evnt)
{
	std::map <std::string, std::function<void(const Unknown::MouseEvent)> >::iterator listeners;

	for (listeners = mouseListeners.begin(); listeners != mouseListeners.end(); listeners++)
	{
		listeners->second(evnt);
	}
}