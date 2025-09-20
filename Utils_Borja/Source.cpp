#include "Utils_Borja.h"
//
//using namespace con;
//using namespace utl;
//using namespace rng;
//using namespace vec;
//using namespace std;
//
//const vec::Vector2 c1 = { 30,18 };
//const vec::Vector2 c2 = { 80,18 };
//const int radius = 20;
//const int maxMagnitude = 20;
//const int magnitudeChangeSpeed = 1;
//const int angleChangeSpeed = 5;
//
////void DrawVector(Vector2 v, Vector2 pos);
////void ClearVector(Vector2 v, Vector2 pos);
////void DrawBorder(Vector2 pos);
//
//void main() {
//	vec::Vector2 v1 = vec::Vector2();
//	vec::Vector2 v2 = vec::Vector2();
//
//	bool isRunning = true;
//
//	activeGraphics = (rend::GraphicsLib)stoi(SearchInFile("Settings.txt", "graphics"));
//
//	nextGraphics = activeGraphics;
//
//	windowSize.x = (float)stoi(SearchInFile("Settings.txt", "resolution_width"));
//	windowSize.y = (float)stoi(SearchInFile("Settings.txt", "resolution_height"));
//
//	drw::OpenWindow(windowSize, "Main");
//	snd::StartAudioDevice();
//	btn::InitButtonSound();
//
//	Clear();
//	DrawBorder(c1, maxMagnitude);
//	DrawBorder(c2, maxMagnitude);
//	con::DrawVector(v1, c1, maxMagnitude);
//	con::DrawVector(v2, c2, maxMagnitude);
//
//	btn::ButtonClick b1;
//	b1.pos = { 1.0f,0.5f };
//	b1.size = { 0.1f,0.05f };
//	b1.mainColor = RED;
//	b1.text = "Hola";
//
//	btn::ButtonClick b2;
//	b2.pos = { 0.0f,0.0f };
//	b2.size = { 0.1f,0.05f };
//	b2.mainColor = BLUE;
//	b2.activeColor = YELLOW;
//	b2.text = "ADIOS";
//
//	btn::ButtonClick b3;
//	b3.pos = { 0.2f,0.2f };
//	b3.size = { 0.08f,0.08f };
//	b3.type = btn::Type::Checkbox;
//	b3.mainColor = GREEN;
//	b3.activeColor = YELLOW;
//	b3.text = "AA";
//
//	btn::Container container;
//	container.pos = {0.5,0.6};
//	container.size = { 0.2,0.6 };
//
//	btn::InitContainer(container);
//	btn::InitButton(b1, container);
//	btn::InitButton(b2, container);
//	btn::InitButton(b3, container);
//
//	btn::ButtonClick buttons[] = {b1,b2,b3};
//
//	rend::SpriteData spriteData;
//	spriteData.file = "stickman.png";
//
//	drw::InitSpriteData(spriteData);
//
//	while (isRunning) {
//
//		if (activeGraphics != nextGraphics) {
//			drw::DeInitSpriteData(spriteData);
//			for (int i = 0; i < 3; i++)
//			{
//				btn::DeInitButtonSprite(buttons[i]);
//			}
//			btn::DeInitButtonSound();
//			drw::Close();
//			snd::EndAudioDevice();
//			activeGraphics = nextGraphics;
//			std::cout  << "\n\n"  << "GRAPHICS CHANGE -> " << (int)activeGraphics << "\n\n";
//			drw::OpenWindow(windowSize, "Main");
//			snd::StartAudioDevice();
//			btn::InitButtonSound();
//			for (int i = 0; i < 3; i++)
//			{
//				btn::InitButtonSprite(buttons[i]);
//				//btn::UpdateButtonSound(buttons[i]);
//			}
//			drw::InitSpriteData(spriteData);
//
//		}
//
//		isRunning = !drw::ShouldExit();
//
//		char key = LastKeyPressed();
//
//		if (key != false) {
//			ClearVector(v1, c1, maxMagnitude);
//			ClearVector(v2, c2, maxMagnitude);
//			switch (tolower(key))
//			{
//			case 'z': {
//				v1 = vec::Vector2();
//				break;
//			}
//			case 'e': {
//				v1.randomize(1, maxMagnitude);
//				break;
//			}
//					// flecha de arriba
//			case 'w': {
//				v1.magnitude(v1.magnitude() + magnitudeChangeSpeed);
//				break;
//			}
//					// flecha de izquierda
//			case 'a': {
//				v1.rotateDegree(angleChangeSpeed);
//				break;
//			}
//					// flecha de abajo
//			case 's': {
//				if (v1.magnitude() > magnitudeChangeSpeed) {
//					v1.magnitude(v1.magnitude() - magnitudeChangeSpeed);
//				}
//				break;
//			}
//					// flecha de derecha
//			case 'd': {
//				v1.rotateDegree(-angleChangeSpeed);
//				break;
//			}
//			case 'n': {
//				v1 = { 1,0 };
//				break;
//			}
//
//
//
//
//			case 'x': {
//				v2 = vec::Vector2();
//				break;
//			}
//			case 'o': {
//				v2.randomize(1, maxMagnitude);
//				break;
//			}
//					// flecha de arriba
//			case 'i': {
//				v2.magnitude(v2.magnitude() + magnitudeChangeSpeed);
//				break;
//			}
//					// flecha de izquierda
//			case 'j': {
//				v2.rotateDegree(angleChangeSpeed);
//				break;
//			}
//					// flecha de abajo
//			case 'k': {
//				if (v2.magnitude() > magnitudeChangeSpeed) {
//					v2.magnitude(v2.magnitude() - magnitudeChangeSpeed);
//				}
//				break;
//			}
//					// flecha de derecha
//			case 'l': {
//				v2.rotateDegree(-angleChangeSpeed);
//				break;
//			}
//			case 'm': {
//				v2 = { 1,0 };
//				break;
//			}
//
//			case 't': {
//				v1 += v2;
//				break;
//			}
//			case 'y': {
//				v1 -= v2;
//				break;
//			}
//
//
//			case 'v': {
//				v1.toCircular();
//				v2.toCircular();
//				break;
//			}
//			case 'b': {
//				v1.toCartesian();
//				v2.toCartesian();
//				break;
//			}
//
//			default:
//				break;
//			}
//
//			//v1.clamp(1, maxMagnitude);
//			//v2.clamp(1, maxMagnitude);
//			con::DrawVector(v1, c1, maxMagnitude);
//			con::DrawVector(v2, c2, maxMagnitude);
//			con::GoToxy(50, c1.y - maxMagnitude / 2);
//			std::cout << "Angle: " << (int)RadianToDegree(v1.angle(v2)) << "  \n";
//			con::GoToxy(50, 1 + c1.y - maxMagnitude / 2);
//			std::cout << "Last key: " << key;
//
//		}
//
//		for (int i = 0; i < 3; i++)
//		{
//			upd::Button(buttons[i]);
//		}
//
//		//update
//
//		windowSize = rend::GetWindowSize();
//		mousePos = rend::GetMousePos();
//
//		for (int i = 1; i < 3; i++)
//		{
//			upd::ButtonClick(buttons[i]);
//		}
//		
//		if (upd::ButtonClick(buttons[0]) && activeGraphics == nextGraphics) {
//			rend::ChangeRenderer();
//		}
//		
//
//		//draw
//		drw::Begin();
//
//		drw::Clear(BLACK);
//
//		drw::Rectangle(container.pos,container.size, WHITE);
//
//		for (int i = 0; i < 3; i++)
//		{
//			drw::ButtonClick(buttons[i]);
//		}
//
//		drw::Circle(mousePos,0.2,RED);
//		//cout << mousePos << '\n';
//
//		drw::Rectangle({ 0.5f,0.5f }, drw::PercentToScreen({0.05f,0.05f }),MAGENTA);
//
//		drw::Sprite(spriteData, { 0.8,0.5 }, {0.2,0.2});
//
//		drw::End();
//
//	}
//	drw::Close();
//}
