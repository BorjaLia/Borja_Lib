#include "BorjaLib.h"

int Test01() {

	bool isRunning = true;

	bLib::Init("Main");

	drw::AnimationData anim;
	anim.duration = 3.0f;

	drw::SpriteData frame1;
	frame1.file = "res/sprites/one.png";
	frame1.size = { 0.2f,0.2f };

	drw::SpriteData frame2;
	frame2.file = "res/sprites/two.png";
	frame2.size = { 0.2f,0.2f };

	drw::SpriteData frame3;
	frame3.file = "res/sprites/three.png";
	frame3.size = { 0.2f,0.2f };

	drw::SpriteData frames[] = { frame1,frame2,frame3 };

	drw::InitAnimData(anim, frames, 3);

	prtcl::ParticleActivator particleActivator;
	particleActivator.id = 0;
	particleActivator.loop = true;
	particleActivator.animated = true;
	particleActivator.animation = anim;
	particleActivator.amount = 15;
	particleActivator.lifetime = { 0.25f,1.0f };
	particleActivator.direction = { 0.0f,1.0f };
	particleActivator.spread = 45.0f;
	particleActivator.pos = { 0.5f,0.65f };
	particleActivator.delay = { 0.5f,1.0f };
	particleActivator.speed = { 0.02f,0.4f };

	prtcl::ParticleData particle;

	prtcl::ParticleData particles[] = { particle ,particle ,particle ,particle ,particle,particle,particle,particle,particle,particle,particle,particle,particle,particle,particle };

	prtcl::Init(particleActivator, particles);

	drw::AnimationData fireAnim;
	fireAnim.duration = 0.125f;

	drw::SpriteData fireFrame1;
	fireFrame1.file = "res/sprites/fire1.png";
	fireFrame1.size = { 0.2f,0.2f };

	drw::SpriteData fireFrame2;
	fireFrame2.file = "res/sprites/fire2.png";
	fireFrame2.size = { 0.175f,0.175f };

	drw::SpriteData fireFrame3;
	fireFrame3.file = "res/sprites/fire3.png";
	fireFrame3.size = { 0.15f,0.15f };

	drw::SpriteData fireFrame4;
	fireFrame4.file = "res/sprites/fire4.png";
	fireFrame4.size = { 0.1f,0.1f };

	drw::SpriteData fireFrames[] = { fireFrame1,fireFrame2,fireFrame3, fireFrame4 };

	drw::InitAnimData(fireAnim, fireFrames, 4);

	prtcl::ParticleActivator fireParticleActivator;
	fireParticleActivator.loop = true;
	fireParticleActivator.startingOffset = { 0.2f,0.1f };
	fireParticleActivator.startingPosInfluence = 0.5f;
	fireParticleActivator.id = 0;
	fireParticleActivator.animated = true;
	fireParticleActivator.loop = true;
	fireParticleActivator.animation = fireAnim;
	fireParticleActivator.amount = 15;
	fireParticleActivator.lifetime = { 0.05f,0.25f };
	fireParticleActivator.direction = { 0.0f,1.0f };
	fireParticleActivator.spread = 0;
	fireParticleActivator.minSize = { 0.005f,0.005f };
	fireParticleActivator.maxSize = { 0.01f,0.01f };
	fireParticleActivator.pos = { 0.5f,0.65f };
	fireParticleActivator.delay = { 0.0f,0.25f };
	fireParticleActivator.speed = { 0.06f,0.7f };

	prtcl::ParticleData fireParticle;

	prtcl::ParticleData fireParticles[] = { fireParticle ,fireParticle ,fireParticle ,fireParticle ,fireParticle,fireParticle,fireParticle,fireParticle,fireParticle,fireParticle,fireParticle,fireParticle,fireParticle,fireParticle,fireParticle };

	prtcl::Init(fireParticleActivator, fireParticles);

	btn::Button renderer;
	renderer.useSprite = true;
	renderer.pos = { 0.2f,0.8f };
	renderer.size = { 0.1f,0.1f };
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::RAYLIB:
		renderer.textData.text = "Raylib";
		break;
	case rend::GraphicsLib::SIGIL:
		renderer.textData.text = "Sigil";
		break;
	default:
		break;
	}
	btn::Init(renderer);

	btn::Button button;
	button.useSprite = true;
	button.pos = { 0.5f,0.5f };
	button.size = { 0.2f,0.1f };
	btn::Init(button);

	while (isRunning) {

		isRunning = !rend::ShouldExit();

		//update
		bLib::UpdateStart();

		btn::UpdateInput(renderer);
		btn::UpdateInput(button);

		if (renderer.signal) {
			int graphics = 1;
			if (stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "graphics")) == 1) {
				graphics = 2;
			}
			utl::SaveToFile(utl::settingsFilePath.c_str(), "graphics", graphics);
			switch ((rend::GraphicsLib)graphics)
			{
			case rend::GraphicsLib::RAYLIB:
				renderer.textData.text = "Raylib";
				break;
			case rend::GraphicsLib::SIGIL:
				renderer.textData.text = "Sigil";
				break;
			default:
				break;
			}
		}

		if (ctrl::IsKeyPressed(ctrl::Key::R)) {
			prtcl::Init(particleActivator, particles);
			std::cout << (char)ctrl::lastKeyPress << "\n";
		}

		fireParticleActivator.pos = rend::mousePos;
		fireParticleActivator.direction = rend::mouseDelta.normalized();

		prtcl::Update(particleActivator, particles);
		prtcl::Update(fireParticleActivator, fireParticles);

		vec::Vector2 point;
		vec::Vector2 object = { 0.5f,0.5f };

		coll::CircleOnCircle(rend::mousePos, object, 0.075f, 0.05f, point);

		std::cout << "mouse = " << rend::mousePos << " point = " << point << "                                 " << '\r';

		bLib::UpdateEnd();

		//Outputs

		//draw
		drw::Begin();
		drw::Clear(DARKGREY_B);

		btn::Draw(renderer);
		btn::Draw(button);

		drw::Animation(anim, { 0.5f,0.15f }, { 0.2f,0.2f });

		prtcl::Draw(particles);
		prtcl::Draw(fireParticles);

		drw::Circle(rend::mousePos, { 0.075f,0.075f }, RED_B);

		drw::Circle(object, { 0.05f,0.05f }, DARKGREEN_B);
		drw::Circle(point, { 0.01f,0.01f }, BLUE_B);

		drw::End();

		//sounds
		btn::Sound(renderer);
		btn::Sound(button);
	}
	rend::Close();
	return 0;
}

int Test02() {

	// --- Definición de Estados del Juego ---
	enum class GameState {
		MAIN_MENU,
		GAMEPLAY,
		CREDITS,
		PAUSED
	};



	// --- Inicialización de la Librería ---
	bool isRunning = true;
	bLib::Init("Testeo v2");
	GameState currentState = GameState::MAIN_MENU;

	// --- Variables Globales del Juego ---
	float gameTimer = 0.0f;
	const int MOUSE_PARTICLE_COUNT = 5;

	// --- Declaración de todos los objetos ---
	// Menú Principal
	btn::Button btnPlay;
	btn::Button btnCredits;
	btn::Button btnExit;

	// Créditos
	btn::Button btnBack;
	drw::TextData creditsTextData;

	// Gameplay
	btn::Button btnPause;
	drw::TextData timerTextData;
	drw::AnimationData mouseAnim;
	prtcl::ParticleActivator mouseParticleActivator;
	prtcl::ParticleData mouseParticles[MOUSE_PARTICLE_COUNT]; // Array estático

	vec::Vector2 testRec;
	vec::Vector2 testRecSize;
	vec::Vector2 mouseCircle;
	vec::Vector2 mouseCircleSize;
	vec::Vector2 testCrash;

	// Pausa
	btn::Button btnReturn;
	btn::Button btnExitPause;

	// 2. Cargar Animación para Partículas del Mouse (usando "fire")
	drw::SpriteData fireFrame1;
	fireFrame1.file = "res/sprites/fire1.png";
	fireFrame1.size = { 0.1f, 0.1f }; // Tamaño normalizado

	drw::SpriteData fireFrame2;
	fireFrame2.file = "res/sprites/fire2.png";
	fireFrame2.size = { 0.1f, 0.1f };

	drw::SpriteData fireFrame3;
	fireFrame3.file = "res/sprites/fire3.png";
	fireFrame3.size = { 0.1f, 0.1f };

	drw::SpriteData fireFrame4;
	fireFrame4.file = "res/sprites/fire4.png";
	fireFrame4.size = { 0.1f, 0.1f };

	// Array de frames para la animación
	drw::SpriteData fireFrames[] = { fireFrame1, fireFrame2, fireFrame3, fireFrame4 };

	// Asumo que 'InitAnimData' itera 'fireFrames', llama a 'InitSpriteData'
	// por cada uno, y guarda el ID del primer frame en 'mouseAnim.id'.
	mouseAnim.duration = 0.25f; // Duración de la animación
	drw::InitAnimData(mouseAnim, fireFrames, 4); // 4 frames

	// --- Inicialización de Objetos del Juego ---

	vec::Vector2 buttonSize = { 0.3f, 0.1f };

	// 1. Menú Principal
	btnPlay.pos = { 0.5f, 0.6f };
	btnPlay.size = buttonSize;
	btnPlay.useSprite = true; // Usará el sprite default (ID 0)
	btnPlay.textData.text = "Play";
	btn::Init(btnPlay);

	btnCredits.pos = { 0.5f, 0.5f };
	btnCredits.size = buttonSize;
	btnCredits.useSprite = true;
	btnCredits.textData.text = "Credits";
	btn::Init(btnCredits);

	btnExit.pos = { 0.5f, 0.4f };
	btnExit.size = buttonSize;
	btnExit.useSprite = true;
	btnExit.textData.text = "Exit";
	btn::Init(btnExit);

	// 2. Créditos
	btnBack.pos = { 0.5f, 0.3f };
	btnBack.size = buttonSize;
	btnBack.useSprite = true;
	btnBack.textData.text = "Volver";
	btn::Init(btnBack);

	creditsTextData.fontSize = 0.05f;
	creditsTextData.text = "Hecho con BorjaLib";

	// 3. Gameplay
	btnPause.pos = { 0.5f, 0.9f };
	btnPause.size = buttonSize;
	btnPause.useSprite = true;
	btnPause.textData.text = "Pausa";
	btn::Init(btnPause);

	timerTextData.fontSize = 0.1f;
	
	testRec = {0.5f,0.5f};
	testRecSize = {0.125f,0.125f};
	mouseCircle = { 0.5f, 0.5f };
	mouseCircleSize = 0.05f;

	// Partículas del mouse
	mouseParticleActivator.loop = true;
	mouseParticleActivator.animated = true;
	mouseParticleActivator.animation = mouseAnim; // Asignamos la anim cargada
	mouseParticleActivator.amount = MOUSE_PARTICLE_COUNT;
	mouseParticleActivator.lifetime = { 0.2f, 0.5f };
	mouseParticleActivator.direction = { 0.0f, -1.0f }; // Hacia abajo
	mouseParticleActivator.spread = 180.0f;
	mouseParticleActivator.minSize = { 0.005f, 0.005f };
	mouseParticleActivator.maxSize = { 0.02f, 0.02f };
	mouseParticleActivator.speed = { 0.1f, 0.3f };
	prtcl::Init(mouseParticleActivator, mouseParticles);

	// 4. Pausa
	btnReturn.pos = { 0.5f, 0.6f };
	btnReturn.size = buttonSize;
	btnReturn.useSprite = true;
	btnReturn.textData.text = "Return";
	btn::Init(btnReturn);

	btnExitPause.pos = { 0.5f, 0.5f };
	btnExitPause.size = buttonSize;
	btnExitPause.useSprite = true;
	btnExitPause.textData.text = "Exit to Menu";
	btn::Init(btnExitPause);


	// --- Bucle Principal del Juego ---
	while (isRunning) {

		isRunning = !rend::ShouldExit();

		// --- Update ---
		bLib::UpdateStart();

		switch (currentState)
		{
		case GameState::MAIN_MENU:
			// Lógica de Update del Menú
			btn::UpdateInput(btnPlay);
			btn::UpdateInput(btnCredits);
			btn::UpdateInput(btnExit);

			if (btnPlay.signal) {
				currentState = GameState::GAMEPLAY;
				gameTimer = 0.0f; // Reiniciar timer
			}
			if (btnCredits.signal) {
				currentState = GameState::CREDITS;
			}
			if (btnExit.signal) {
				isRunning = false;
			}
			break;

		case GameState::GAMEPLAY:
			// Lógica de Update del Juego
			gameTimer += rend::deltaTime; // Avanzar el timer

			btn::UpdateInput(btnPause);
			if (btnPause.signal) {
				currentState = GameState::PAUSED;
			}

			// Actualizar partículas
			mouseParticleActivator.pos = rend::mousePos;
			prtcl::Update(mouseParticleActivator, mouseParticles);

			mouseCircle = rend::mousePos;

			if (coll::RecOnCircle(testRec, testRecSize, mouseCircle, mouseCircleSize, testCrash)) {
				std::cout << "collided" << rend::frameCounter << "\n";
			}

			break;

		case GameState::CREDITS:
			// Lógica de Update de Créditos
			btn::UpdateInput(btnBack);
			if (btnBack.signal) {
				currentState = GameState::MAIN_MENU;
			}
			break;

		case GameState::PAUSED:
			// Lógica de Update de Pausa (el timer no avanza)
			btn::UpdateInput(btnReturn);
			btn::UpdateInput(btnExitPause);

			if (btnReturn.signal) {
				currentState = GameState::GAMEPLAY;
			}
			if (btnExitPause.signal) {
				currentState = GameState::MAIN_MENU;
			}
			break;
		}

		drw::Rectangle(vec::Vector4(0.0f,0.0f,0.95f,1.0f),BLUE_B);

		bLib::UpdateEnd();

		// --- Draw ---
		drw::Begin();
		drw::Clear(DARKGREY_B);

		switch (currentState)
		{
		case GameState::MAIN_MENU:
			// Dibujar Menú
			btn::Draw(btnPlay);
			btn::Draw(btnCredits);
			btn::Draw(btnExit);
			break;

		case GameState::GAMEPLAY:
			// Dibujar Juego
			prtcl::Draw(mouseParticles);
			btn::Draw(btnPause);

			// Dibujar el timer
			timerTextData.text = std::to_string(gameTimer);
			drw::Text(timerTextData.text.c_str(), timerTextData, { 0.5f, 0.5f }, timerTextData.fontSize, { 0,0 }, WHITE_B);
			
			drw::Rectangle(testRec, testRecSize,RED_B);
			drw::Circle(mouseCircle, mouseCircleSize,BLUE_B);
			drw::Circle(testCrash, {0.025f,0.025f},MAGENTA_B);
			
			break;

		case GameState::CREDITS:
			// Dibujar Créditos
			btn::Draw(btnBack);
			drw::Text(creditsTextData.text.c_str(), creditsTextData, { 0.5f, 0.6f }, creditsTextData.fontSize, { 0,0 }, WHITE_B);
			break;

		case GameState::PAUSED:
			// Dibujar Pausa
			btn::Draw(btnReturn);
			btn::Draw(btnExitPause);

			// Dibujar el timer (pausado)
			timerTextData.text = std::to_string(gameTimer);
			drw::Text(timerTextData.text.c_str(), timerTextData, { 0.5f, 0.3f }, timerTextData.fontSize, { 0,0 }, WHITE_B);
			break;
		}

		drw::End();

		// --- Sounds ---
		// (Actualmente los botones no tienen sonidos asignados, pero la lógica estaría aquí)
		// ...
	}

	// --- Cierre ---
	rend::Close();
	return 0;

}

int main() {
	Test02();
	return 0;
}