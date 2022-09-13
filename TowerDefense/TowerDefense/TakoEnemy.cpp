#include <string>
#include "AudioHelper.hpp"
#include "TakoEnemy.hpp"
#include "PlayScene.hpp"

TakoEnemy::TakoEnemy(int x, int y) : Enemy("play/enemy-Tako.png", x, y, 15, 25, 600, 5000) {
}
