#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"



void Game::Initialize()
{
	// Create engine
	engine = std::make_unique<nc::Engine>(); //New Engine
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	REGISTER_CLASS(PlayerComponent);
	REGISTER_CLASS(EnemyComponent);
	REGISTER_CLASS(PickupComponent);

	// create scene
	scene = std::make_unique<nc::Scene>(); //New Scene
	scene->engine = engine.get();

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::setFilePath("../Resources");

	rapidjson::Document document;
	bool success = nc::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);

	for (int i = 0; i < 10; i++) {
		auto actor = nc::ObjectFactory::Instance().Create<nc::Actor>("Coin");
		actor->transform.position = nc::Vector2{ nc::RandomRange(0, 800), nc::RandomRange(300, 500) };
		scene->AddActor(std::move(actor));
	}
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update()
{
	engine->Update();
	scene->Update(engine->time.deltaTime);
	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::PRESSED) {
		quit = true;
	}

}

void Game::Draw()
{
	engine->Get<nc::Renderer>()->BeginFrame();

	scene->Draw(engine->Get<nc::Renderer>());
	engine->Draw(engine->Get<nc::Renderer>());

	engine->Get<nc::Renderer>()->EndFrame();
}

