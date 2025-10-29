#include "BorjaLib.h"

namespace prtcl {

	void Init(ParticleActivator& activator, ParticleData particles[])
	{
		for (int i = 0; i < activator.amount; i++)
		{
			Init(activator, particles[i]);
		}
	}

	void Init(ParticleActivator& activator, ParticleData& particle)
	{
		if (!activator.active) {
			activator.active = true;
			activator.direction.normalize();
		}

		particle.active = true;
		if (particle.id == 0) {
			particle.id = activator.id;
		}
		if (activator.animated) {
			particle.animated = true;
			particle.animation = activator.animation;
		}
		particle.amount = activator.amount;
		particle.pos = activator.pos;
		particle.pos.x += mth::GetRandomf(0.0f, activator.startingOffset.x) - activator.startingOffset.x / 2.0f;
		particle.pos.y += mth::GetRandomf(0.0f, activator.startingOffset.y) - activator.startingOffset.y / 2.0f;
		particle.size.x = mth::GetRandomf(activator.minSize.x, activator.maxSize.x);
		particle.size.y = mth::GetRandomf(activator.minSize.y, activator.maxSize.y);
		particle.direction = activator.direction;
		particle.direction.randomizeAngle(0, activator.spread);
		particle.direction.rotateDegree(-activator.spread / 2);
		if (activator.startingPosInfluence != 0.0f) {
			mth::Clamp(activator.startingPosInfluence);
			particle.direction = particle.direction * (1.0f - activator.startingPosInfluence) + vec::Vector2{ particle.pos - activator.pos }.normalized() * activator.startingPosInfluence;
			particle.direction.normalize();
		}
		particle.lifetime = mth::GetRandomf(activator.lifetime.x, activator.lifetime.y);
		particle.delay = mth::GetRandomf(activator.delay.x, activator.delay.y);
		particle.rotationChange = mth::GetRandomf(activator.rotation.x, activator.rotation.y);
		particle.speed = mth::GetRandomf(activator.speed.x, activator.speed.y);

		particle.size.x /= rend::windowRatio;
		particle.direction.x /= rend::windowRatio;
	}

	bool Update(ParticleData& particle)
	{
		if (particle.active) {

			if (particle.alive) {
				particle.pos += particle.direction * particle.speed * rend::deltaTime;
				particle.lifetime -= rend::deltaTime;
			}
			if (particle.delay > 0.0f) {

				particle.delay -= rend::deltaTime;

				if (particle.delay <= 0.0f) {
					particle.alive = true;
					particle.delay = 0.0f;
				}

			}
			if (particle.lifetime < 0.0f) {
				particle.lifetime = 0.0f;
				particle.active = false;
			}
		}
		return particle.active;
	}

	void Update(ParticleActivator& activator, ParticleData particles[])
	{
		bool active = false;

		for (int i = 0; i < particles[0].amount; i++)
		{
			if (Update(particles[i])) {
				active = true;
			}
			if (activator.loop) {
				if (particles[i].lifetime <= 0.0f) {
					Init(activator, particles[i]);
				}
			}
		}
		if (!activator.loop) {
			activator.active = active;
		}
	}

	void Draw(ParticleData particles[])
	{
		for (int i = 0; i < particles[0].amount; i++)
		{
			if (particles[i].alive && particles[i].active) {

				if (particles[i].animated) {
					drw::Animation(particles[i].animation, particles[i].pos, particles[i].size);
				}
				else {
					drw::Sprite(drw::spriteDataList[particles[i].id], particles[i].pos, particles[i].size);
				}
				if (rend::devInfo == rend::InfoMode::ADVANCED) {
					drw::Line(particles[i].pos, particles[i].direction.asCircular(), 0.025f, MAGENTA_B);
				}
			}
		}
	}
}