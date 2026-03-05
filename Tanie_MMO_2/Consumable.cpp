#include "Consumable.hpp"
#include <iostream>

Consumable::Consumable(int id_tmp, std::string name_tmp , int price_tmp, int consumable_type_tmp, int effect_points_tmp)
	:Item(id_tmp, name_tmp, type ,price_tmp, is_stackable, 1), consumable_type(consumable_type_tmp), effect_points(effect_points_tmp) {

	std::uniform_int_distribution<int> dist(1,3);
	this->set_curr_num_of_blocks_in_stack(dist(get_rand_device()));
}

Consumable::Consumable(const Consumable& source)
	:Item(source.get_id(), source.get_name(),type ,source.get_price(), is_stackable, source.get_required_level()), consumable_type(source.consumable_type),
	effect_points(source.effect_points) {

	this->set_curr_num_of_blocks_in_stack(source.get_curr_num_of_blocks_in_stack());
}

//====================Getters=====================

int Consumable::get_type() const {
	return type;
}

int Consumable::get_consumable_type() const {
	return consumable_type;
}

int Consumable::get_effect_points() const {
	return effect_points;
}

void Consumable::print() const {
	switch (consumable_type){
	case 0:
		std::cout << get_name() << " | Healing: " << effect_points << " | " << get_price() << " $"; break;
	}
}