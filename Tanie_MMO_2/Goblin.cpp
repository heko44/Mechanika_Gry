#include "Goblin.hpp"
#include "ItemList.hpp"
#include <random>
#include <iostream>

Goblin::Goblin(int xpos, int ypos)
	:Entity(default_name, deafault_max_health_points, default_damage, 1, xpos, ypos, inv_size){
}

Goblin::Goblin(const Goblin& source)
	:Entity(default_name, source.get_max_health_points(), source.get_damage(), source.get_level(), source.get_x(), source.get_y(), inv_size) {
}

void Goblin::spawn() {

	//randomize level from 1 to 5
	std::random_device rand;
	std::uniform_int_distribution<> distr(1, 5);

	set_level(distr(rand));
	set_max_health_points(int(get_level() * deafault_max_health_points * 0.7));
	set_damage(int(get_level() * default_damage * 0.7));
	set_experience(get_level() * 50);

	std::cout << '\n' << "You've encountered " << *this << std::endl;
}


//==============Drops==================
void Goblin::drops() {

	std::random_device rand;
	std::uniform_int_distribution<> item(1, tier1.size() - 1);
	std::uniform_int_distribution<> amount(1, 50);
	int num = amount(rand);
	std::shared_ptr<Item> usable;

	if (num%5 == 0)
		usable = tier1_item(1);

	else {
		usable = tier1_item(0);
		usable->set_curr_num_of_blocks_in_stack(amount(rand));
	}
	std::shared_ptr<Item> item_tmp = tier1_item(item(rand));

	this->add_to_inventory(usable);				//money or potion
	this->add_to_inventory(item_tmp);
}

//==============Death==================
void Goblin::death() {
	std::cout << default_name << " is dead\n";
	this->drops();
}