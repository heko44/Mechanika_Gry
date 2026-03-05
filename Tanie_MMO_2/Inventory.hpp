#pragma once
#include <vector>
#include <memory>
#include "Item.hpp"

class Inventory {

	//Invetory variables
	size_t MAX_INV_SIZE;
	static constexpr int INVENTORY_EMPTY_SLOT_ID = -1;
	std::vector<std::shared_ptr<Item>> items;

	size_t find_index_of(const Item& item) const;
	size_t find_empty_slot() const;

	//Add item
	bool add_item_to_existing_stack_if_possible(const Item& item);
	void add_item_to_new_stack_if_possible(std::shared_ptr<Item>& item);

	//Remove item
	bool remove_item_if_stackable(int slot_num);
	bool remove_item_if_unstackable(int slot_num);

	

public:
	Inventory(size_t inventorySize);

	bool add_item(std::shared_ptr<Item>& item);
	void remove_stack(int slot_num);
	bool remove_item(int slot_num);

	void print() const;

	//Getters
	std::shared_ptr<Item>& get_item(int slotNumber);
	const int get_inventory_size();
	std::stringstream get_inventory_stream() const;
};