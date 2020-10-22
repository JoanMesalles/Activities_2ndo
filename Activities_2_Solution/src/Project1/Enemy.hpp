#include <vector>
#include "Weapon.hpp"

class Enemy
{
public:
	std::string name;
	int live;
	int damage;
	int shield;
	float hitSpeed;
	int experience;
	std::vector<Weapon> weapons;

	Enemy() {};
	Enemy(std::string _name, int _live, int _damage, int _shield, float _hitSpeed, int _experience) :
		name(_name), live(_live), damage(_damage), shield(_shield), hitSpeed(_hitSpeed), experience(_experience) {};

};