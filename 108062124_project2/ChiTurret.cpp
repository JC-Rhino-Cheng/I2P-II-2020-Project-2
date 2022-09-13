#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "ChiBullet.hpp"
#include "ChiTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int ChiTurret::Price = 500;
ChiTurret::ChiTurret(float x, float y) :
	Turret("play/tower-base.png", "play/turret-4.png", x, y, 600, Price, 0.5) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void ChiTurret::CreateBullet() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
	float rotation = atan2(diff.y, diff.x);
	Engine::Point normalized = diff.Normalize();
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new ChiBullet(Position + normalized * 36, diff, rotation, this));
	AudioHelper::PlayAudio("Fart.wav");
}
