#pragma once
#include "Framework/System.h"
#include "Texture.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <vector>

namespace MarkOne {

	class Texture;
	class ParticleSystem : public GraphicsSystem {

	private:
		struct Particle {
			Vector2 position;
			Vector2 velocity;
			Vector2 prevPosition;
			std::shared_ptr<Texture> texture;

			float lifetime;
			bool isActive{ false };

			static bool IsNotActive(Particle particle) { return particle.isActive == false; }
		};

	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(class Renderer* renderer) override;

		void Create(const Vector2& position, size_t count, float lifetime, std::shared_ptr<Texture> texture, float speed);
		void Create(const Vector2& position, size_t count, float lifetime, const std::vector<Color>& colors, float speed, float angle, float angleRange);

	private:
		std::vector<Particle> particles;

	};
}