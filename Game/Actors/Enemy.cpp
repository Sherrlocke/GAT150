#include "Enemy.h"
#include "Math/MathUtils.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	if (scene->GetActor<Player>()) {

		nc::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation);

		float turnAngle = nc::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * ( 3 * dt );

		//transform.rotation = nc::Lerp(transform.rotation, transform.rotation() + turnAngle, dt * 2);

		float angle = nc::Vector2::Angle(forward, direction.Normalized());

		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= nc::DegToRad(10)) {

			fireTimer = fireRate;

			nc::Transform t = transform;
			t.scale = 1.0f;
			scene->AddActor(std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("enemy_laser.png"), 200.0f));
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("enemy_fire");

		}
	}

	transform.position += (nc::Vector2::Rotate(nc::Vector2::right, transform.rotation)) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		actor->destroy = true;


		destroy = true;
		std::vector<nc::Color> colors = { nc::Color::purple, nc::Color::blue, nc::Color::white };
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 2, 0.5f, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("explosion.png"), 150);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("enemy_explosion");

		int dropChance = nc::RandomRangeInt(0, 10);
		if (dropChance == 5 || dropChance == 7) {
			nc::Event event;
			event.name = "SentrySpawn";
			event.data = "Sentry Turret Spawned";
			scene->engine->Get<nc::EventSystem>()->Notify(event);
		}

		nc::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<nc::EventSystem>()->Notify(event);
	}
}

