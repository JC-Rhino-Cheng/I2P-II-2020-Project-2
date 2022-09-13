#ifndef CHITURRET_HPP
#define CHITURRET_HPP
#include "Turret.hpp"

class ChiTurret: public Turret {
public:
	static const int Price;
    ChiTurret(float x, float y);
	void CreateBullet() override;
};
#endif // CHITURRET_HPP
