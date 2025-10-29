#include "BorjaLib.h"

namespace rend {

	bool ChangeRenderer()
	{
		switch (activeGraphics)
		{
		case GraphicsLib::NONE:
			nextGraphics = GraphicsLib::RAYLIB;
			break;
		case GraphicsLib::RAYLIB:
			nextGraphics = GraphicsLib::SIGIL;
			break;
		case GraphicsLib::SIGIL:
			nextGraphics = GraphicsLib::RAYLIB;
			break;
		default:
			return false;
			break;
		}

		utl::SaveToFile("Settings.txt", "graphics", (int)nextGraphics);

		return true;
	}

	void OpenWindow(vec::Vector2 size, const char* title, bool fullScreen)
	{
		std::string graphics = "NONE";
		switch ((GraphicsLib)activeGraphics)
		{
		case GraphicsLib::NONE: {

			std::cout << "NONE";
			break;
		}
		case GraphicsLib::RAYLIB: {

			std::cout << "RAYLIB";
#ifdef HAS_RAYLIB
			graphics = title;
			graphics.append(" - RAYLIB");
			SetWindowState(FLAG_WINDOW_RESIZABLE);
			InitWindow(static_cast<int>(size.x), static_cast<int>(size.y), graphics.c_str());
			int monitor = GetCurrentMonitor();
			SetWindowPosition((GetMonitorWidth(monitor) / 2) - static_cast<int>(windowSize.x) / 2, (GetMonitorHeight(monitor) / 2) - static_cast<int>(windowSize.y) / 2);
			if (fullScreen) {
				ToggleFullscreen();
			}
			SetExitKey(KEY_MENU);
#endif
			break;
		}
		case GraphicsLib::SIGIL: {

			std::cout << "SIGIL";
#ifdef HAS_SIGIL
			graphics = title;
			graphics.append(" - SIGIL");
			slWindow(static_cast<int>(size.x), static_cast<int>(size.y), graphics.c_str(), fullScreen);
#endif
			break;
		}
		default:
			break;
		}
	}

	bool ShouldExit()
	{
		switch ((GraphicsLib)activeGraphics)
		{
		case GraphicsLib::NONE: {
			return false;
			break;
		}
		case GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			return WindowShouldClose();
#endif
			break;
		}
		case GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			return slShouldClose();
#endif
			break;
		}
		default:
			break;
		}
		return true;
	}

	void Close()
	{
		switch ((GraphicsLib)activeGraphics)
		{
		case GraphicsLib::NONE: {

			break;
		}
		case GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			CloseWindow();
#endif
			break;
		}
		case GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			slClose();
#endif
			break;
		}
		default:
			break;
		}
	}

	vec::Vector2 GetWindowSize()
	{
		vec::Vector2 size = { 1,1 };
		switch (activeGraphics)
		{
		case GraphicsLib::NONE: {

			break;
		}
		case GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB

			size = { (float)GetScreenWidth(),(float)GetScreenHeight() };
			//utl::Clamp(size.x, 1, (16.0f / 9.0f) * size.y);
			//utl::Clamp(size.y, 1, (9.0f / 16.0f) * size.x);
#endif
			break;
		}
		case GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			size = windowSize;
#endif
			break;
		}
		default:
			break;
		}

		windowRatio = size.x / size.y;

		return size;
	}

	vec::Vector2 GetMousePos()
	{
		vec::Vector2 pos = { 0,0 };

		switch (activeGraphics)
		{
		case GraphicsLib::NONE: {

			break;
		}
		case GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			pos = { (float)GetMousePosition().x / windowSize.x,(windowSize.y - (float)GetMousePosition().y) / windowSize.y };
#endif
			break;
		}
		case GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			pos = { (float)slGetMouseX() / windowSize.x,(float)slGetMouseY() / windowSize.y };
			//return { (float)slGetMouseX() / windowSize.x,(float)slGetMouseY() / windowSize.y };
#endif
			break;
		}
		default:
			break;
		}
		return pos;
	}

	float GetDeltaTime()
	{
		switch (activeGraphics)
		{
		case GraphicsLib::NONE: {

			break;
		}
		case GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			return GetFrameTime();
#endif
			break;
		}
		case GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			return static_cast<float>(slGetDeltaTime());
#endif
			break;
		}
		default:
			break;
		}
		return 1.0f;
	}

	void UpdateDeltaTime()
	{
		deltaTime = GetDeltaTime();
		secondCounter += deltaTime;
		secondSmallCounter += deltaTime;
	}

	void UpdateFramerate()
	{
		frameCounter++;
		secondFrameCounter++;

		if (secondSmallCounter >= 1.0f) {
			framerate = secondFrameCounter;
			secondSmallCounter = 0;
			secondFrameCounter = 0;
		}
	}

	GraphicsLib activeGraphics = GraphicsLib::NONE;
	GraphicsLib nextGraphics = GraphicsLib::NONE;

	ctrl::Key frameInfoKey = ctrl::Key::F1;
	InfoMode frameInfo = InfoMode::NONE;
	ctrl::Key devInfoKey = ctrl::Key::F2;
	InfoMode devInfo = InfoMode::NONE;
	ctrl::Key devModeKey = ctrl::Key::F3;
	InfoMode devMode = InfoMode::NONE;

	int frameCounter = 0;
	int framerate = 0;
	float secondCounter = 0;
	float secondSmallCounter = 0;
	int secondFrameCounter = 0;
	float deltaTime = 0;

	float fullscreen = false;

	vec::Vector2 windowSize = { 1600,900 };
	float windowRatio = (16.0f / 9.0f);

	std::string mouseSprite = "";
	vec::Vector2 mousePos = { 0,0 };
	vec::Vector2 lastMousePos = { 0,0 };
	vec::Vector2 mouseDelta = { 0,0 };

	bool pixelMode = false;
}