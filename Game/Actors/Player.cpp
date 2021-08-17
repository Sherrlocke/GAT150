#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "../Game.h"
#include <memory>

Player::Player(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform, texture }, speed{ speed } {

}

	void Player::Initialize() {

		std::unique_ptr locator = std::make_unique<Actor>();
		locator->transform.localposition = nc::Vector2{ 8, 0 };
		AddChild(std::move(locator));

		locator = std::make_unique<Actor>();
		locator->transform.localposition = nc::Vector2{ 0, 5 };
		AddChild(std::move(locator));

		locator = std::make_unique<Actor>();
		locator->transform.localposition = nc::Vector2{ 0, -5 };
		AddChild(std::move(locator));

		locator = std::make_unique<Actor>();
		locator->transform.localposition = nc::Vector2{ 0, 0 };
		AddChild(std::move(locator));
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		//movement
		float thrust = 0;
		if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == nc::InputSystem::eKeyState::HELD) transform.rotation -= 5 * dt;
		if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == nc::InputSystem::eKeyState::HELD) transform.rotation += 5 * dt;
		if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == nc::InputSystem::eKeyState::HELD) thrust = speed;

		nc::Vector2 acceleration;
		acceleration += (nc::Vector2::Rotate(nc::Vector2::right, transform.rotation)) * thrust;

		velocity += acceleration * dt;
		transform.position += velocity * dt;

		velocity *= 0.987f;

		transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
		transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

		//NEED A PLAYER TRAIL
		//scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 1, 0.3f, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("", scene->engine->Get<nc::Renderer>()), 50, transform.rotation, nc::DegToRad(30));

		//fire
		fireTimer -= dt;
		if (fireTimer <= 0 && scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::PRESSED) {

			fireTimer = fireRate;

			{
				nc::Transform t = children[1]->transform;
				t.scale = 1.3f;

				std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("player_laser.png"), 600.0f);
				projectile->tag = "Player";
				scene->AddActor(std::move(projectile));
				scene->engine->Get<nc::AudioSystem>()->PlayAudio("player_fire");

			}

		}

		mineTimer -= dt;
		if (mineTimer <= 0 && scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_E) == nc::InputSystem::eKeyState::PRESSED) {

			mineTimer = mineRate;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform.position, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("mine.png"), 0.0f);
			projectile->tag = "Player";
			scene->AddActor(std::move(projectile));
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("player_fire");

		}

		
	}



	void Player::OnCollision(Actor* actor)
	{
		if (dynamic_cast<Enemy*>(actor)) {

			actor->destroy = true;
			scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("explosion.png"), 50);
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

			nc::Event event;
			event.name = "PlayerHit";
			event.data = std::string("I'm Hit");
			scene->engine->Get<nc::EventSystem>()->Notify(event);

		}

		if (dynamic_cast<Projectile*>(actor) && actor->tag != "Player") {

			actor->destroy = true;
			scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("explosion.png"), 50);
			scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

			nc::Event event;
			event.name = "PlayerHit";
			event.data = std::string("I'm Hit");
			scene->engine->Get<nc::EventSystem>()->Notify(event);
		}
	}