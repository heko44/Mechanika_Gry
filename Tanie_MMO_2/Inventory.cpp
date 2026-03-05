#include "Inventory.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Consumable.hpp"
#include <iostream>
#include <memory>
#include <sstream>

Inventory::Inventory(size_t invetorySize)
:MAX_INV_SIZE(invetorySize){
}

size_t Inventory::find_index_of(const Item& item) const {

	for (size_t i = 0; i < items.size(); i++) {
		if (items.at(i)->get_id() == item.get_id())
			return i;
	}	
	return MAX_INV_SIZE;
}

size_t Inventory::find_empty_slot() const {
	for (size_t i = 0; i < items.size(); i++) {
		if (items.at(i) == nullptr)
			return i;
	}
	return items.size();
}

//==========================================Add Item================================================

bool Inventory::add_item_to_existing_stack_if_possible(const Item& item) {
	size_t idx = find_index_of(item);

	if (!item.stackable() || idx == MAX_INV_SIZE) {
		return false;
	}

	if (item.get_id() == items[idx]->get_id()) {
		if (items[idx]->get_curr_num_of_blocks_in_stack() + item.get_curr_num_of_blocks_in_stack() <= items[idx]->get_max_num_blocks())
		{
			items[idx]->set_curr_num_of_blocks_in_stack(items[idx]->get_curr_num_of_blocks_in_stack() + item.get_curr_num_of_blocks_in_stack());
			return true;
		}
	}	
	return false;
}


void Inventory::add_item_to_new_stack_if_possible(std::shared_ptr<Item>& item) {
	size_t idx = find_empty_slot();

	if (idx != items.size())
		items.at(idx) = std::move(item);
	else 
		items.push_back(std::move(item));
}

bool Inventory::add_item(std::shared_ptr<Item>& item) {
	bool was_possible_to_add_to_existing_stack = add_item_to_existing_stack_if_possible(*item);

	if (!was_possible_to_add_to_existing_stack) {
		add_item_to_new_stack_if_possible(item);
		return true;
	}

	return false;
}

//==========================================Remove Item================================================

bool Inventory::remove_item_if_stackable(int slot_num) {
	int amount{-1};
	size_t idx = find_index_of(*items.at(slot_num));

	if (items.at(idx)->get_type() == 3)	//if Consumable
		amount = 1;

	else {
		while (amount < 0 || items.at(slot_num)->get_curr_num_of_blocks_in_stack() < amount){

			std::cout << "Enter amount: ";
			std::cin >> amount;
			if (amount < 0)
				std::cout << "Wrong amount\n\n";

		}
	}

	if (idx != MAX_INV_SIZE && amount <= items[idx]->get_curr_num_of_blocks_in_stack()) {


		if (items[idx]->get_curr_num_of_blocks_in_stack() - amount == 0) {
			items.erase(items.begin() + idx);

			return true;
		}

		else {
			items[idx]->set_curr_num_of_blocks_in_stack(items[idx]->get_curr_num_of_blocks_in_stack() - amount);
			return true;
		}
	}


	return false;
}

bool Inventory::remove_item_if_unstackable(int slot_num) {

	size_t idx = find_index_of(*items.at(slot_num));

	if (idx != MAX_INV_SIZE) {
		items.erase(items.begin() + slot_num);
		return true;
	}

	return false;
}


void Inventory::remove_stack(int slot_num) {

	if (items.begin()+slot_num != items.end())
		items.erase(items.begin() + slot_num);
}

bool Inventory::remove_item(int slot_num) {
	if (items.at(slot_num)->stackable()) {
		return remove_item_if_stackable(slot_num);
	}

	else
		return remove_item_if_unstackable(slot_num);

	return false;
}

//==========================================Getters================================================

std::shared_ptr<Item>& Inventory::get_item(int slotNumber) {
	return items[slotNumber];
}

const int Inventory::get_inventory_size() {
	return items.size(); 
}

std::stringstream Inventory::get_inventory_stream() const {
	std::stringstream ss;
	ss << "Inventory IDs: {";

	for (auto& item : items) {
		ss << item->get_id();
		if (item->stackable())
			ss << '(' << item->get_curr_num_of_blocks_in_stack() << ')';
		ss << ',';
	}

	ss << "}\n";

	return ss;
}
//==========================================Other================================================

void Inventory::print() const {
	int i = 1;
	for (auto& item : items) {
		std::cout <<"\t[" << i << "]";
		item->print();
		std::cout << std::endl;
		i++;
	}
}