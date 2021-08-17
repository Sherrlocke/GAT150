#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor {
public:
	Player(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float mineTimer{ 0 };
	float mineRate{ 15.0f };
	float fireRate{ 1.0f };
	float speed{ 300 };
	nc::Vector2 velocity;
};