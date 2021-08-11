#include "Engine.h"
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include <cassert>

int main(int, char**)
{
	int i = 6;
	assert(i == 6);

	MarkOne::Engine engine;
	engine.Startup();
	engine.Get<MarkOne::Renderer>()->Create("GAT150", 800, 600);

	MarkOne::Scene scene;
	scene.engine = &engine;

	MarkOne::setFilePath("../Resources");

	engine.Get<MarkOne::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine.Get<MarkOne::AudioSystem>()->AddAudio("music", "audio/dub_hub.wav");
	MarkOne::AudioChannel channel = engine.Get<MarkOne::AudioSystem>()->PlayAudio("music", 1, 1, true);


	std::shared_ptr<MarkOne::Texture> texture = engine.Get<MarkOne::ResourceSystem>()->Get<MarkOne::Texture>("sf2.png", engine.Get<MarkOne::Renderer>());

	for (size_t i = 0; i < 10; i++) {
		MarkOne::Transform transform{ MarkOne::Vector2{MarkOne::RandomRange(0, 800), MarkOne::RandomRange(0, 600)}, MarkOne::RandomRange(0, 360), 1.0f };
		std::unique_ptr<MarkOne::Actor> actor = std::make_unique<MarkOne::Actor>(transform, texture);
		scene.AddActor(std::move(actor));
	}

	// get font from resource system
	int size = 16;
	std::shared_ptr<MarkOne::Font> font = engine.Get<MarkOne::ResourceSystem>()->Get<MarkOne::Font>("fonts/28 Days Later.ttf", &size);

	// create font texture
	std::shared_ptr<MarkOne::Texture> textTexture = std::make_shared<MarkOne::Texture>(engine.Get<MarkOne::Renderer>());
	// set font texture with font surface
	textTexture->Create(font->CreateSurface("hello world", MarkOne::Color{ 1, 1, 1 }));
	// add font texture to resource system
	engine.Get<MarkOne::ResourceSystem>()->Add("textTexture", textTexture);


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


		if (engine.Get<MarkOne::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == MarkOne::InputSystem::eKeyState::PRESSED) {
			quit = true;
		}

		if (engine.Get<MarkOne::InputSystem>()->GetButtonState((int)MarkOne::InputSystem::eMouseButton::Left) == MarkOne::InputSystem::eKeyState::PRESSED) {
			MarkOne::Vector2 position = engine.Get<MarkOne::InputSystem>()->GetMousePosition();
			// Create Particles
			//std::cout << position.x << " " << position.y << std::endl;
			engine.Get<MarkOne::AudioSystem>()->PlayAudio("explosion", 1, MarkOne::RandomRange(0.2, 2));
			channel.SetPitch(MarkOne::RandomRange(0.2f, 2.0f));
		}
		

		//if (engine.time.time >= quitTime) quit = true;
		//engine.time.timeScale = 0.1f;
		//std::cout << engine.time.time << std::endl;

		engine.Get<MarkOne::Renderer>()->BeginFrame();


		scene.Draw(engine.Get<MarkOne::Renderer>());
		engine.Draw(engine.Get<MarkOne::Renderer>());

		MarkOne::Transform t;
		t.position = { 30, 30 };
		t.scale = 3;
		engine.Get<MarkOne::Renderer>()->Draw(textTexture, t);

		engine.Get<MarkOne::Renderer>()->EndFrame();

	}

	SDL_Quit();

	return 0;
}
