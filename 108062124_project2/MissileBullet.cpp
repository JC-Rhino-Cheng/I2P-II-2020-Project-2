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
		Target = enemy;//Target �OEnemy*�C
		Target->lockedBullets.push_back(this);//�Q�o��"missile"bullet�s��w��enemy�A�]�O���@�U�ۤv�Q�o��bullet��w�F
		lockedBulletIterator = std::prev(Target->lockedBullets.end());
		//�]��Target->lockedBullets�Ostd::list<Bullets*>�ҥHTarget->lockedBullets.end()�OBullets*�A�GlockedBulletIterator�]�OBullets*
		//std::prev�i�Ѧ�https://blog.csdn.net/u013630349/article/details/47105319
		//std::prev(..., a)�۷��std::advance(..., -a)�Cadvance�O���e��a��iterator(���e�O�������󩹰}�Cidx�j����V)�A����M�p�G�O�t�ƪ��ܡA�N������V�q��V�C
		//�ҥHstd::prev(Target->lockedBullets.end());�۷���XTagrget->lockedBullets.end()!!!�`�N!!!end()�O����Ӧ��Ľd��u��v�@��iterator!!!
		//�]���~�ݭnstd::prev�A���e�@��~��^�즳�Ħ�m�C
		//lockedBulletIterator�O�ӦbMissileBullet.hpp�̭���std::list<Bullet*>::iterator lockedBulletIterator�A�O���ۨC�Ӥw�g��w�nenemy�ؼЪ�bullet�C
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
