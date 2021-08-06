#pragma once
#include "Framework/System.h"

namespace MarkOne {
	class InputSystem : public System {

		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;
	};
}