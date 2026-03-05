#include "Item.hpp"
#include <iostream>
#include <limits>


Item::Item(int id_tmp,std::string name_tmp, int type_tmp, int price_tmp, bool is_stackable_tmp, int required_level_tmp)
	:id(id_tmp),name(name_tmp),type(type_tmp), price(price_tmp), is_stackable(is_stackable_tmp), required_level(required_level_tmp) {
	
	if (type == 0)
	{
		std::uniform_int_distribution<> distr(5, 30);
		curr_num_of_blocks_in_stack = (distr(rand_device));

		max_num_blocks = std::numeric_limits<int>::max();	//MONEY
	}
	
	else if (is_stackable_tmp)
	{
		std::uniform_int_distribution<> distr(5, 30);
		curr_num_of_blocks_in_stack = (distr(rand_device));

		max_num_blocks = 100;
	}

	else
	{
		max_num_blocks = 1;
		curr_num_of_blocks_in_stack = 1;
	}
}

Item::Item(const Item& source)
	:Item(source.id, source.name, source.type, source.price, source.is_stackable, source.required_level) {

}

//getters

int Item::get_id() const {
	return id;
}

bool Item::stackable() const {
	return is_stackable;
}

int Item::get_max_num_blocks() const {
	return max_num_blocks;
}

int Item::get_curr_num_of_blocks_in_stack() const {
	return curr_num_of_blocks_in_stack;
}

std::string Item::get_name() const {
	return name;
}

int Item::get_price() const {
	return price;
}

int Item::get_required_level() const {
	return required_level;
}

std::random_device& Item::get_rand_device() {
	return rand_device;
}


//setters
void Item::set_max_num_blocks(int value) {
	max_num_blocks = value;
}

void Item::set_curr_num_of_blocks_in_stack(int value) {
	curr_num_of_blocks_in_stack = value;
}

void Item::set_id(int id_tmp) {
	id = id_tmp;
}

void Item::set_required_level(int value) {
	required_level = value;
}