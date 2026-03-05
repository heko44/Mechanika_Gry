

//Weapon(std::string name, int price, int damage_points, int required_level); 0 - helmet, 1- chest, 2- legs, 3 shoes 
//Armor(std::string name, int price, int protection_points, int required_level, armor type);
//Consumable(std::string name, int price, int consumable_type, int effect_points);
#include "ItemList.hpp"
int aviable_id = 1;

void tier1_init() {
	tier1.push_back(std::make_shared<Money>());
	tier1.push_back(std::make_shared<Consumable>(aviable_id++, "Small healing potion", 5, 0, 15));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Rusty sword", 10, 5, 1));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Blunt sword", 15, 10, 1));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Common sword", 20, 15, 1));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Withered axe", 19, 13, 7));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Short Sword", 19, 12, 6));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Old Sword", 12, 12, 10));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Nail Club", 13, 11, 5));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Rusty Sword", 10, 10, 5));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Smith's Hammer", 5, 10, 5));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Hand Axe", 6, 9, 5));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Club (Light Mace)", 5, 8, 5));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Sickle", 4, 7, 5));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Poker", 3, 6, 5));
	tier1.push_back(std::make_shared<Weapon>(aviable_id++, "Club", 2, 5, 5));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Loos shirt", 5, 5, 1, 1));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Light Diggers Trousers", 4, 10, 1, 2));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Shadow's Dress", 15, 30, 1, 1));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Light Novice's Armor", 15, 30, 1, 1));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Judge's Robe", 10, 20, 1, 1));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Rogue's Dress", 5, 10, 1, 1));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Light Templars Armor", 20, 35, 1, 2));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Mercenary's Trousers", 15, 30, 1, 2));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Old Mercenary's Trousers", 25, 40, 1, 2));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Pest's trousers", 10, 20, 1, 2));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Light Templars Armor", 30, 45, 1, 2));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Headkerchief", 1, 5, 1, 0));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "eye patch", 5, 10, 1, 0));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Boots", 5, 10, 1, 3));
	tier1.push_back(std::make_shared<Armor>(aviable_id++, "Sandals", 1, 5, 1, 3));
}

void items_init() {
	tier1_init();
}

std::shared_ptr<Item> tier1_item(size_t slotNum) {

	return tier1.at(slotNum);
}

std::shared_ptr<Item> tier1_item_by_id(int id) {
	for (auto& item : tier1) {
		if (item->get_id() == id)
			return item;
	}
}
