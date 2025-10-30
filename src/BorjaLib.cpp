#include "BorjaLib.h"

namespace bLib {

	void Init(std::string windowName)
	{
		rend::activeGraphics = rend::ToGraphicsLib(stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "graphics")));
		//rend::activeGraphics = (rend::GraphicsLib)1;

		rend::windowSize.x = static_cast<float>(stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "resolution_width")));
		rend::windowSize.y = static_cast<float>(stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "resolution_height")));

		rend::fullscreen = static_cast<bool>(stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "fullscreen")));

		rend::OpenWindow(rend::windowSize, windowName.c_str(), rend::fullscreen);
		snd::StartAudioDevice();

		// 1. Limpiamos el vector de sprites por si acaso
		drw::spriteDataList.clear();

		// 2. Creamos y cargamos el sprite por defecto
		drw::SpriteData defaultSprite = {};
		defaultSprite.file = "res/sprites/NoTexture.png"; // Ruta a tu sprite por defecto
		defaultSprite.size = { 0.1f, 0.1f };

		// IMPORTANTE: Si usas Sigil, setea la resolución manualmente
		if (rend::activeGraphics == rend::GraphicsLib::SIGIL) {
			// ¡Debes poner la resolución real de "NoTexture.png" aquí!
			// defaultSprite.resolution = { 64.0f, 64.0f }; 
		}

		// 3. Llamamos a InitSpriteData.
		//    Esto pondrá el defaultSprite en 'spriteDataList[0]'
		// <--- FIN CORRECCIÓN ---

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