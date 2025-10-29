#include "BorjaLib.h"

int main() {

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
	particleActivator.lifetime = {0.25f,1.0f};
	particleActivator.direction = {0.0f,1.0f};
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
	fireParticleActivator.minSize = {0.005f,0.005f};
	fireParticleActivator.maxSize = {0.01f,0.01f};
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

		prtcl::Update(particleActivator,particles);
		prtcl::Update(fireParticleActivator,fireParticles);

		vec::Vector2 point;
		vec::Vector2 object = {0.5f,0.5f};

		coll::CircleOnCircle(rend::mousePos, object, 0.075f,0.05f, point);

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

		drw::Circle(rend::mousePos, { 0.075f,0.075f },RED_B);

		drw::Circle(object, {0.05f,0.05f },DARKGREEN_B);
		drw::Circle(point, {0.01f,0.01f },BLUE_B);

		drw::End();

		//sounds
		btn::Sound(renderer);
		btn::Sound(button);
	}
	rend::Close();
	return 0;
}
