#pragma once

#include "Entity.hpp"
#include "Inventory.hpp"
#include <string>

class Goblin : public virtual Entity {

	//Goblins Variables
	inline static std::string  default_name = "Goblin";
	static const int deafault_max_health_points = 10;
	static const int default_damage = 5;
	static const int default_inventory_size = 2;
	static constexpr size_t inv_size = 2;

public:
	Goblin(int x, int y);
	Goblin(const Goblin& source);

	virtual void spawn() override;

	//drop system
	virtual void death() override;
	virtual void drops() override;
};