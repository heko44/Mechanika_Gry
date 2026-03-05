#include "Money.hpp"
#include <iostream>

Money::Money()
	:Item(0,"Money", type, 1, is_stackable, 0){
	this->set_curr_num_of_blocks_in_stack(1);
}

Money::Money(const Money& source)
	:Item(0, source.get_name(), type, 1, is_stackable, 0) {
	this->set_curr_num_of_blocks_in_stack(source.get_curr_num_of_blocks_in_stack());
}

void Money::print() const {
	std::cout << "Money | " << get_curr_num_of_blocks_in_stack() << "$";
}

int Money::get_type() const {
	return 0;
}

void Money::add(int amount_to_add) {
	set_curr_num_of_blocks_in_stack(amount_to_add);
}

void Money::remove(int amount_to_remove) {
	set_curr_num_of_blocks_in_stack(get_curr_num_of_blocks_in_stack() - amount_to_remove);
}