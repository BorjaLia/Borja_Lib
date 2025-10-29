#include "BorjaLib.h"

namespace bLib {

	void Init(std::string windowName)
	{
		rend::activeGraphics = (rend::GraphicsLib)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "graphics"));
		//rend::activeGraphics = (rend::GraphicsLib)1;

		rend::windowSize.x = (float)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "resolution_width"));
		rend::windowSize.y = (float)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "resolution_height"));

		rend::fullscreen = (bool)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "fullscreen"));

		rend::OpenWindow(rend::windowSize, windowName.c_str(), rend::fullscreen);
		snd::StartAudioDevice();

		drw::InitSpriteData(drw::defaultSprite);
		drw::InitFontData(drw::defaultFont);
		snd::InitAudioData(snd::defaultAudio);
	}

	void UpdateStart()
	{
		rend::windowSize = rend::GetWindowSize();
		rend::mousePos = rend::GetMousePos();
		rend::UpdateDeltaTime();
		rend::UpdateFramerate();
	}

	void UpdateEnd()
	{

		if (rend::lastMousePos != rend::mousePos) {
			rend::mouseDelta = rend::lastMousePos - rend::mousePos;
		}
		rend::lastMousePos = rend::GetMousePos();

		if (IsKeyPressed(rend::frameInfoKey)) {

			switch (rend::frameInfo)
			{
			case rend::InfoMode::NONE: {
				rend::frameInfo = rend::InfoMode::BASIC;
				break;
			}
			case rend::InfoMode::BASIC: {
				rend::frameInfo = rend::InfoMode::ADVANCED;
				break;
			}
			case rend::InfoMode::ADVANCED: {
				rend::frameInfo = rend::InfoMode::NONE;
				break;
			}
			default:
				break;
			}
		}

		if (IsKeyPressed(rend::devInfoKey)) {

			switch (rend::devInfo)
			{
			case rend::InfoMode::NONE: {
				rend::devInfo = rend::InfoMode::BASIC;
				break;
			}
			case rend::InfoMode::BASIC: {
				rend::devInfo = rend::InfoMode::ADVANCED;
				break;
			}
			case rend::InfoMode::ADVANCED: {
				rend::devInfo = rend::InfoMode::NONE;
				break;
			}
			default:
				break;
			}
		}
		if (IsKeyPressed(rend::devModeKey)) {

			switch (rend::devMode)
			{
			case rend::InfoMode::NONE: {
				rend::devMode = rend::InfoMode::BASIC;
				break;
			}
			case rend::InfoMode::BASIC: {
				rend::devMode = rend::InfoMode::ADVANCED;
				break;
			}
			case rend::InfoMode::ADVANCED: {
				rend::devMode = rend::InfoMode::NONE;
				break;
			}
			default:
				break;
			}
		}

		ctrl::lastKeyPress = ctrl::GetKeyDown();
		ctrl::lastMouseButton = ctrl::GetMouseButtonDown();
	}
}