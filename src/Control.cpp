#include "BorjaLib.h"

namespace ctrl {

	int ToInt(Key key)
	{
		return static_cast<int>(key);
	}

	int ToInt(ButtonMouse button)
	{
		return static_cast<int>(button);
	}

	Key ToKey(int num)
	{
		return static_cast<Key>(num);
	}

	ButtonMouse ToButton(int num)
	{
		return static_cast<ButtonMouse>(num);
	}

	bool IsMouseDown(ButtonMouse mouseButton)
{
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		return IsMouseButtonDown(ToInt(mouseButton));
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		return slGetMouseButton(ToInt(mouseButton));
#endif
		break;
	}
	default:
		break;
	}
	return false;
}

bool IsMousePressed(ButtonMouse mouseButton)
{
	ButtonMouse heldButton = GetMouseButtonDown();

	if (heldButton == lastMouseButton) {
		return false;
	}
	else {
		if (mouseButton == heldButton && heldButton != ButtonMouse::NULL_BUTTON) {
			lastMouseButton = heldButton;
			return true;
		}
		return false;
	}
}

ButtonMouse GetMouseButtonDown()
{
	ButtonMouse button = ButtonMouse::NULL_BUTTON;

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		for (int i = 0; i < ToInt(ButtonMouse::SIZE); i++)
		{
			if (IsMouseButtonDown(i)) {
				button = ToButton(i);
			}
		}
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		for (int i = 0; i < ToInt(ButtonMouse::SIZE); i++)
		{
			if (slGetMouseButton(i)) {
				button = ToButton(i);
			}
		}
#endif
		break;
	}
	default:
		break;
	}

	return button;
}

bool IsKeyHeldDown(Key key)
{
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		return IsKeyDown(ToInt(key));
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		return slGetKey(ToInt(key));
#endif
		break;
	}
	default:
		break;
	}

	return false;
}

bool IsKeyPressed(Key key)
{
	Key heldKey = GetKeyDown();

	if (heldKey == lastKeyPress) {
		return false;
	}
	else {
		if (key == heldKey && heldKey != Key::NULL_KEY) {
			lastKeyPress = heldKey;
			return true;
		}
		return false;
	}
}

Key GetKeyDown()
{
	Key key = Key::NULL_KEY;

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		for (int i = 0; i < ToInt(Key::SIZE); i++)
		{
			if (IsKeyDown(i)) {
				key = ToKey(i);
			}
		}
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		for (int i = 0; i < ToInt(Key::SIZE); i++)
		{
			if (slGetKey(i)) {
				key = ToKey(i);
			}
		}
#endif
		break;
	}
	default:
		break;
	}

	return key;
}

char LastKeyPressed()
{
	if (_kbhit()) {
		return static_cast<char>(_getch());
	}
	return false;
}

Key lastKeyPress = Key::NULL_KEY;
ButtonMouse lastMouseButton = ButtonMouse::NULL_BUTTON;
ButtonMouse menuSelectionMouseButton = ButtonMouse::LMB;

}