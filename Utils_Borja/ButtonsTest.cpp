#include "Utils_Borja.h"

void main() {

	bool isRunning = true;

	rend::activeGraphics = (rend::GraphicsLib)stoi(utl::SearchInFile("Settings.txt", "graphics"));
	rend::activeGraphics = (rend::GraphicsLib)2;

	rend::nextGraphics = rend::activeGraphics;

	rend::windowSize.x = (float)stoi(utl::SearchInFile("Settings.txt", "resolution_width"));
	rend::windowSize.y = (float)stoi(utl::SearchInFile("Settings.txt", "resolution_height"));

	rend::OpenWindow(rend::windowSize, "Main",false);
	snd::StartAudioDevice();

	rend::defaultButtonHoveredTexture.file = "NoTextureHovered.png";

	btn::InitButtonDefaults();

	btn::Container container;
	container.pos = {0.3,0.5};
	container.size = {0.5,0.3};
	container.isRendered = true;
	container.useTexture = false;

	btn::Button button;
	button.useSprite = true;
	button.pos = {0.5,0.5};
	button.size = {0.2,0.2};

	btn::Init(container);
	btn::Init(button,container,true);

	btn::Button buttons[] = {button};

	//btn::Init(container,buttons,1);

	while (isRunning) {

		isRunning = !rend::ShouldExit();

		if (rend::activeGraphics != rend::nextGraphics) {
			rend::Close();
			snd::EndAudioDevice();
			rend::activeGraphics = rend::nextGraphics;
			std::cout << "\n\n" << "GRAPHICS CHANGE -> " << (int)rend::activeGraphics << "\n\n";
			rend::OpenWindow(rend::windowSize, "Main");
			snd::StartAudioDevice();
			btn::InitButtonDefaults();
			btn::Init(buttons,1);
		}

		//update

		rend::windowSize = rend::GetWindowSize();
		rend::mousePos = rend::GetMousePos();

		btn::UpdateInput(buttons,1);

		if (buttons[0].isClickedUpChange && buttons[0].isHovered) {
			//rend::ChangeRenderer();
		}

		//Outputs

		//draw
		drw::Begin();

		drw::Clear(BLACK);

		drw::Rectangle(container.pos,container.size,RED);
		//btn::Draw(button);
		btn::Draw(container,buttons,1);

		drw::End();

		//sounds

		btn::Sound(buttons,1);

	}
	rend::Close();
}
