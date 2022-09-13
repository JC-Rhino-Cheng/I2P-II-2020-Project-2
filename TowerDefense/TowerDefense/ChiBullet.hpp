#ifndef CHIBULLET_HPP
#define CHIBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class ChiBullet : public Bullet {
public:
	explicit ChiBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // CHIBULLET_HPP
