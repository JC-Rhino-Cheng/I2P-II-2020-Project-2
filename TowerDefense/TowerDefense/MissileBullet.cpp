#include <cmath>
#include <random>
#include <string>
#include <utility>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "MissileBullet.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

class Turret;

MissileBullet::MissileBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-3.png", 100, 4, position, forwardDirection, rotation + ALLEGRO_PI / 2, parent, MISSILE) {
}
void MissileBullet::Update(float deltaTime) {
	if (!Target) {
		float minDistance = INFINITY;
		Enemy* enemy = nullptr;
		for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
			Enemy* e = dynamic_cast<Enemy*>(it);
			float distance = (e->Position - Position).Magnitude();
			if (distance < minDistance) {
				minDistance = distance;
				enemy = e;
			}
		}
		if (!enemy) {
			Bullet::Update(deltaTime);
			return;
		}
		Target = enemy;//Target 是Enemy*。
		Target->lockedBullets.push_back(this);//被這個"missile"bullet新鎖定的enemy，也記錄一下自己被這顆bullet鎖定了
		lockedBulletIterator = std::prev(Target->lockedBullets.end());
		//因為Target->lockedBullets是std::list<Bullets*>所以Target->lockedBullets.end()是Bullets*，故lockedBulletIterator也是Bullets*
		//std::prev可參考https://blog.csdn.net/u013630349/article/details/47105319
		//std::prev(..., a)相當於std::advance(..., -a)。advance是往前走a個iterator(往前是指類似於往陣列idx大的方向)，那當然如果是負數的話，就類似於向量方向。
		//所以std::prev(Target->lockedBullets.end());相當於找出Tagrget->lockedBullets.end()!!!注意!!!end()是指整個有效範圍「後」一個iterator!!!
		//因此才需要std::prev，往前一格才能回到有效位置。
		//lockedBulletIterator是個在MissileBullet.hpp裡面的std::list<Bullet*>::iterator lockedBulletIterator，記錄著每個已經鎖定好enemy目標的bullet。
	}
	Engine::Point originVelocity = Velocity.Normalize();
	Engine::Point targetVelocity = (Target->Position - Position).Normalize();
	float maxRotateRadian = rotateRadian * deltaTime;
	float cosTheta = originVelocity.Dot(targetVelocity);
	// Might have floating-point precision error.
	if (cosTheta > 1) cosTheta = 1;
	else if (cosTheta < -1) cosTheta = -1;
	float radian = acos(cosTheta);
	if (abs(radian) <= maxRotateRadian)
		Velocity = targetVelocity;
	else
		Velocity = ((abs(radian) - maxRotateRadian) * originVelocity + maxRotateRadian * targetVelocity) / radian;
	Velocity = speed * Velocity.Normalize();
	Rotation = atan2(Velocity.y, Velocity.x) + ALLEGRO_PI / 2;
	Bullet::Update(deltaTime);
}
void MissileBullet::OnExplode(Enemy* enemy) {
	if (Target->CollisionRadius != 15)Target->lockedBullets.erase(lockedBulletIterator);
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(4, 10);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-3.png", dist(rng), enemy->Position.x, enemy->Position.y));
}
