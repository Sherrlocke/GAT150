#include "Engine.h"
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
int main(int, char**)
{

	MarkOne::Engine engine;
	engine.Startup();
	engine.Get<MarkOne::Renderer>()->Create("GAT150", 800, 600);

	MarkOne::Scene scene;
	scene.engine = &engine;

	MarkOne::setFilePath("../Resources");

	std::shared_ptr<MarkOne::Texture> texture = engine.Get<MarkOne::ResourceSystem>()->Get<MarkOne::Texture>("sf2.png", engine.Get<MarkOne::Renderer>());

	for (size_t i = 0; i < 10; i++) {
		MarkOne::Transform transform{ MarkOne::Vector2{MarkOne::RandomRange(0, 800), MarkOne::RandomRange(0, 600)}, MarkOne::RandomRange(0, 360), 1.0f };
		std::unique_ptr<MarkOne::Actor> actor = std::make_unique<MarkOne::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}

	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3.0f;

	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}


		engine.Update();
		scene.Update(engine.time.deltaTime);

		if (engine.time.time >= quitTime) quit = true;
		engine.time.timeScale = 0.1f;

		std::cout << engine.time.time << std::endl;

		engine.Get<MarkOne::Renderer>()->BeginFrame();

		scene.Draw(engine.Get<MarkOne::Renderer>());

		engine.Get<MarkOne::Renderer>()->EndFrame();

	}

	SDL_Quit();

	return 0;
}
