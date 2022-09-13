#ifndef MAINMENUSCENE_HPP
#define MAINMENUSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class MainMenuScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> ThemeSongInstance;
public:
	explicit MainMenuScene() = default;
	void Initialize() override;
	void Terminate() override;
	void PlayOnClick(int stage);
};

#endif // MAINMENUSCENE_HPP
