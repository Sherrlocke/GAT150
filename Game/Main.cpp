#include "Engine.h"
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>

int main(int, char**)
{
	MarkOne::Engine engine;
	engine.Startup();

	engine.Get<MarkOne::Renderer>()->Create("GAT150", 800, 600);

	std::cout << MarkOne::getFilePath() << std::endl;
	MarkOne::setFilePath("../Resources");
	std::cout << MarkOne::getFilePath() << std::endl;

	std::shared_ptr<MarkOne::Texture> texture = engine.Get<MarkOne::ResourceSystem>()->Get<MarkOne::Texture>("sf2.png", engine.Get<MarkOne::Renderer>());

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Get<MarkOne::Renderer>()->BeginFrame();

		MarkOne::Vector2 position(300, 400);
		engine.Get<MarkOne::Renderer>()->Draw(texture, position);

		engine.Get<MarkOne::Renderer>()->EndFrame();

		//for (size_t i = 0; i < 1000; i++) {

		//SDL_Rect src{ 32, 64, 32, 64 };
		//SDL_Rect dest{ MarkOne::RandomRangeInt(0, screen.x), MarkOne::RandomRangeInt(0, screen.y), 32, 48 };
		//SDL_RenderCopy(renderer, texture, &src, &dest);
	}

		
	


	SDL_Quit();

	return 0;
}
