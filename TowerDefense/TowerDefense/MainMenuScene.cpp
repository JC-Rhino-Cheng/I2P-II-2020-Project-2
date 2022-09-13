#include <functional>
#include <string>

#include "AudioHelper.hpp"
#include "GameEngine.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "MainMenuScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

void MainMenuScene::Initialize() {
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;

	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 400 / 2, halfH - 100 / 2, 400, 100);
	btn->SetOnClickCallback(std::bind(&MainMenuScene::PlayOnClick, this, 1));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Start Game", "pirulen.ttf", 44, halfW, halfH, 0, 0, 0, 255, 0.5, 0.5));
	ThemeSongInstance = AudioHelper::PlaySample("ThemeSong.ogg", true, AudioHelper::BGMVolume);
}

void MainMenuScene::Terminate() {
	AudioHelper::StopSample(ThemeSongInstance);
	ThemeSongInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}

void MainMenuScene::PlayOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
