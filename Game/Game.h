#pragma once
#include "Engine.h"

class Game {
public:
	enum class eState {
		Title,
		Instructions,
		StartGame,
		StartSound,
		StartLevel,
		NextLevel,
		Game,
		GameOver,

	};

public:
	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool isQuit() { return quit; }

private:
	void UpdateTitle(float dt);
	void UpdateStartLevel(float dt);
	void NextLevel(float dt);

	void OnAddPoints(const nc::Event& event);
	void OnPlayerHit(const nc::Event& event);
	void OnSentrySpawn(const nc::Event& event);

public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;

private:
	bool quit = false;

	eState state = eState::Title;
	float stateTimer = 0.0f;

public:
	int round{ 0 };
	int lives{ 0 };
	int score{ 0 };

	nc::AudioChannel musicChannel;
	std::shared_ptr<nc::Texture> particleTexture;
	//std::shared_ptr<nc::Texture> textTexture;
};