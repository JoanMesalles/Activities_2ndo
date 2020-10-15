
#include <string>
class Enemie {
public:
	int live;
	int attack;
	int def;
	int xp;
	int frq;
	struct weapon
	{
		std::string id;
		std::string type;
		int reach;
	};

};