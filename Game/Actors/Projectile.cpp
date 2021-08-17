#include "Projectile.h"
#include "Engine.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) destroy = true;

	transform.position += (nc::Vector2::Rotate(nc::Vector2::right, transform.rotation)) * speed * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);
}
