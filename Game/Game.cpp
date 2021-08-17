#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

void Game::Initialize()
{
	// Create engine
	engine = std::make_unique<nc::Engine>(); //New Engine
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("GAT150", 800, 600);

	// create scene
	scene = std::make_unique<nc::Scene>(); //New Scene
	scene->engine = engine.get();

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::setFilePath("../Resources");

	// font
	int size = 14;
	std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/LHANDW.ttf", &size);

	// textures
	std::shared_ptr<nc::Texture> titleTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	titleTexture->Create(font->CreateSurface("Super Awesome Space Mission 5", nc::Color{ 1, 1, 1 }));
	engine->Get<nc::ResourceSystem>()->Add("titleTexture", titleTexture);

	std::shared_ptr<nc::Texture> enterTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	enterTexture->Create(font->CreateSurface("Press ENTER to play!", nc::Color{ 1, 1, 1 }));
	engine->Get<nc::ResourceSystem>()->Add("enterTexture", enterTexture);

	std::shared_ptr<nc::Texture> gameoverTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	gameoverTexture->Create(font->CreateSurface("Game Over", nc::Color{ 1, 1, 1 }));
	engine->Get<nc::ResourceSystem>()->Add("gameoverTexture", gameoverTexture);

	std::shared_ptr<nc::Texture> survivedTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	survivedTexture->Create(font->CreateSurface("You survived until round: ", nc::Color{ 0, 1, 0 }));
	engine->Get<nc::ResourceSystem>()->Add("survivedTexture", survivedTexture);

	std::shared_ptr<nc::Texture> HTP1Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	HTP1Texture->Create(font->CreateSurface("How to play: ", nc::Color{ 0, 1, 0 }));
	engine->Get<nc::ResourceSystem>()->Add("HTP1Texture", HTP1Texture);

	std::shared_ptr<nc::Texture> HTP2Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	HTP2Texture->Create(font->CreateSurface("Press W to use thrusters", nc::Color{ 0, 1, 0 }));
	engine->Get<nc::ResourceSystem>()->Add("HTP2Texture", HTP2Texture);

	std::shared_ptr<nc::Texture> HTP3Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	HTP3Texture->Create(font->CreateSurface("Press A and D to turn your ship", nc::Color{ 0, 1, 0 }));
	engine->Get<nc::ResourceSystem>()->Add("HTP3Texture", HTP3Texture);

	std::shared_ptr<nc::Texture> HTP4Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	HTP4Texture->Create(font->CreateSurface("Press SPACE to fire your missiles", nc::Color{ 0, 1, 0 }));
	engine->Get<nc::ResourceSystem>()->Add("HTP4Texture", HTP4Texture);

	std::shared_ptr<nc::Texture> HTP5Texture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	HTP5Texture->Create(font->CreateSurface("Press SPACE to start!", nc::Color{ 0, 1, 0 }));
	engine->Get<nc::ResourceSystem>()->Add("HTP5Texture", HTP5Texture);

	std::shared_ptr<nc::Texture> roundTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	roundTexture->Create(font->CreateSurface(std::to_string(round), nc::Color{ 0, 1, 0 }));
	engine->Get<nc::ResourceSystem>()->Add("roundTexture", roundTexture);

	std::shared_ptr<nc::Texture> scoreTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	scoreTexture->Create(font->CreateSurface(std::to_string(score), nc::Color{ 1, 1, 1 }));
	engine->Get<nc::ResourceSystem>()->Add("scoreTexture", scoreTexture);

	std::shared_ptr<nc::Texture> lifeTexture = std::make_shared<nc::Texture>(engine->Get<nc::Renderer>());
	lifeTexture->Create(font->CreateSurface(std::to_string(lives), nc::Color{ 1, 1, 1 }));
	engine->Get<nc::ResourceSystem>()->Add("lifeTexture", lifeTexture);

	std::shared_ptr<nc::Texture> playerTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("spaceShips_006.png", engine->Get<nc::Renderer>());
	std::shared_ptr<nc::Texture> enemyTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Galactica_Ranger_10.png", engine->Get<nc::Renderer>());
	std::shared_ptr<nc::Texture> sentryTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("sentry_ship.png", engine->Get<nc::Renderer>());
	std::shared_ptr<nc::Texture> playerLaserTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("player_laser.png", engine->Get<nc::Renderer>());
	std::shared_ptr<nc::Texture> enemyLaserTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("enemy_laser.png", engine->Get<nc::Renderer>());
	std::shared_ptr<nc::Texture> mineTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("mine.png", engine->Get<nc::Renderer>());
	std::shared_ptr<nc::Texture> explosionTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("explosion.png", engine->Get<nc::Renderer>());

	//game
	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("enemy_explosion", "audio/enemy_explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("enemy_fire", "audio/enemy_fire.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("player_fire", "audio/player_fire.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("music", "audio/dub_hub.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerHit", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("SentrySpawn", std::bind(&Game::OnSentrySpawn, this, std::placeholders::_1));

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

	float dt = engine->time.deltaTime;
	stateTimer += dt;

	switch (state)
	{

	case Game::eState::Title:
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_RETURN) == nc::InputSystem::eKeyState::PRESSED) {
		state = eState::Instructions;
		}
		break;

	case Game::eState::Instructions:
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::PRESSED) {
		state = eState::StartSound;
		}
		break;

	case Game::eState::StartGame:
		round = 1;
		score = 0;
		lives = 5;
		state = eState::StartLevel;
		break;

	case Game::eState::StartSound:
		musicChannel = engine->Get<nc::AudioSystem>()->PlayAudio("music", 1, 1, true);
		state = eState::StartGame;
		break;

	case Game::eState::StartLevel:
	{
		UpdateStartLevel(dt);
		state = eState::Game;
	}
		break;

	case Game::eState::NextLevel:
		NextLevel(dt);
		state = eState::Game;
		break;

	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() == 0) {
			state = eState::NextLevel;
		}
		if (lives < 1) {
			state = eState::GameOver;
			scene->RemoveAllActors();
		}

		break;

	case Game::eState::GameOver:
		if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_RETURN) == nc::InputSystem::eKeyState::PRESSED) {
			state = eState::StartGame;
		}
		break;

	default:
		break;
	}


	if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::PRESSED) {
		quit = true;
	}

}

void Game::Draw()
{
	engine->Get<nc::Renderer>()->BeginFrame();

	switch (state)
	{
	case Game::eState::Title:
	{
		nc::Transform t;
		t.position = { 400, 300 };
		t.scale = 3;
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("titleTexture"), t);
		t.position = { 400, 350 };
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("enterTexture"), t);
	}
		break;
	case Game::eState::Instructions:
	{
		nc::Transform t;
		t.scale = 2;
		t.position = { 400, 200 };
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("HTP1Texture"), t);
		t.position = { 400, 250 };
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("HTP2Texture"), t);
		t.position = { 400, 300 };
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("HTP3Texture"), t);
		t.position = { 400, 350 };
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("HTP4Texture"), t);
		t.position = { 400, 400 };
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("HTP5Texture"), t);
	}
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
	{
		nc::Transform s;
		s.position = { 50, 20 };
		std::shared_ptr<nc::Texture> scoreTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("scoreTexture");
		std::shared_ptr<nc::Font> scoreFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/LHANDW.ttf");
		scoreTexture->Create(scoreFont->CreateSurface(std::to_string(score), nc::Color{ 1, 1, 1 }));
		engine->Get<nc::Renderer>()->Draw(scoreTexture, s);

		s.position = { 750, 20 };
		std::shared_ptr<nc::Texture> lifeTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("lifeTexture");
		std::shared_ptr<nc::Font> lifeFont = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/LHANDW.ttf");
		lifeTexture->Create(lifeFont->CreateSurface(std::to_string(lives), nc::Color{ 1, 1, 1 }));
		engine->Get<nc::Renderer>()->Draw(lifeTexture, s);
	}
		break;

	case Game::eState::GameOver:
		nc::Transform t;
		t.position = { 400, 300 };
		t.scale = 3;
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("gameoverTexture"), t);
		t.position = { 385, 350 };
		engine->Get<nc::Renderer>()->Draw(engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("survivedTexture"), t);
		t.position = { 710, 350 };
		std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("roundTexture");
		std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/LHANDW.ttf");
		texture->Create(font->CreateSurface(std::to_string(round), nc::Color{ 0, 1, 0 }));
		engine->Get<nc::Renderer>()->Draw(texture, t);
		break;
	
	}

	scene->Draw(engine->Get<nc::Renderer>());
	engine->Draw(engine->Get<nc::Renderer>());


	engine->Get<nc::Renderer>()->EndFrame();
}

void Game::UpdateTitle(float dt)
{
	//if (Core::Input::IsPressed(VK_SPACE)) {
	//	
	//	stateFunction = &Game::UpdateStartLevel;
	//	//state = eState::StartGame;
	//}
}

void Game::UpdateStartLevel(float dt)
{
	scene->RemoveAllActors();

	scene->AddActor(std::make_unique<Player>(nc::Transform(nc::Vector2(400.0f, 300.0f), 0.0f, 0.8f), engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("spaceShips_006.png", engine->Get<nc::Renderer>()), 300.0f));
	
	for (size_t i = 0; i < 2; i++) {
		scene->AddActor(std::make_unique<Enemy>(nc::Transform(nc::Vector2(nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)), 0.0f, 1.0f ), engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Galactica_Ranger_10.png", engine->Get<nc::Renderer>()), 150.0f));
	}
}

void Game::NextLevel(float dt) {
	
	round++;

	for (size_t i = 0; i < 2; i++) {
		scene->AddActor(std::make_unique<Enemy>(nc::Transform(nc::Vector2(nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)), 0.0f, 1.0f), engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Galactica_Ranger_10.png", engine->Get<nc::Renderer>()), 150.0f));
	}
}

void Game::OnAddPoints(const nc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerHit(const nc::Event& event) {

	lives--;
	std::cout << std::get<std::string>(event.data) << std::endl;
}

void Game::OnSentrySpawn(const nc::Event& event) {
	scene->AddActor(std::make_unique<Enemy>(nc::Transform(nc::Vector2(nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)), 0.0f, 0.4f), engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("sentry_ship.png", engine->Get<nc::Renderer>()), 0.0f));
}