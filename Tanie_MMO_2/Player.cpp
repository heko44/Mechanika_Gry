#include "Player.hpp"
#include <iostream>
#include <Windows.h>
#include <limits>
#include <sstream>

Player::Player(std::string name_tmp)
	:Entity(name_tmp, default_health, default_damage, default_level, default_x, default_y, inv_size),
	next_level_experience(default_next_level_experience), weapon_damage(0), helmet_protection(0), chest_protection(0), legs_protection(0),
	shoes_protection(0) {
	std::cout << "Player " << *this << " created.\n";
}

Player::Player(std::string name_tmp, int max_health_points_tmp, int damage_tmp, int level_tmp, int xpos_tmp, int ypos_tmp)
	:Entity(name_tmp, max_health_points_tmp, damage_tmp, level_tmp, xpos_tmp, ypos_tmp, inv_size),
	next_level_experience(default_next_level_experience * (level_tmp)), weapon_damage(0), helmet_protection(0), chest_protection(0), legs_protection(0),
	shoes_protection(0) {
	std::cout << "Player " << *this << " created.\n";
}

Player::Player(const Player& source)
	:Entity(source.get_name(), source.get_health_points(), source.get_damage(), source.get_level(), source.get_x(), source.get_y(), inv_size) {
	next_level_experience = source.next_level_experience;
	weapon_damage = source.weapon_damage;
	helmet_protection = source.helmet_protection;
	chest_protection = source.chest_protection;
	legs_protection = source.legs_protection;
	shoes_protection = source.shoes_protection;
}

//in game 
void Player::spawn() {
	std::cout << *this;
}

void Player::drops() {

}

void Player::death() {
	this->set_x(1);
	this->set_y(1);

	std::cout << "---------------You died------------.\n\nGame is going to restart in: \n5\n";
	for (int i = 4; i >= 1; i--) {
		Sleep(1000);
		std::cout << i << '\n';
	}
	Sleep(1000);
}

bool Player::isLevelUp() {
	if (get_experience() >= next_level_experience)
		return true;
	return false;
}

void Player::level_up() {
	while (isLevelUp()) {
		add_level(1);	//icrement level
		set_experience(get_experience() - next_level_experience);
		next_level_experience += get_level()*100;

		add_max_health_points(get_level() * 10);
		set_health_points(get_max_health_points());
		add_damage(get_level());

		std::cout << "You leveled up!\t" << *this << std::endl;
	}
}

void Player::dispaly_stats() const{

	std::cout << "===================" << get_name() << "==================== \n";
	std::cout << "Level: " << get_level() << '\n';
	std::cout << "Experience: " << get_experience() << "/" << next_level_experience << '\n';
	std::cout << "Health: " << get_health_points() << "/" << get_max_health_points() << "HP\n";
	std::cout << "Damage: " << get_absolute_damage() << '\n';
	std::cout << "Protection : " << get_protection() << '\n';
	std::cout << "===========================================================\n" << std::endl;
}

//Display equipment
void Player::display_equipment() const{

	std::cout << "==================== Equipment =================\n";
	
	std::cout << "Weapon: ";
	if (weapon != nullptr)
		weapon->print(); std::cout << '\n';

	std::cout << "Helmet: ";
	if (helmet != nullptr)
		helmet->print(); std::cout << '\n';

	std::cout << "Chest: ";
	if (chest != nullptr)
		chest->print(); std::cout << '\n';

	std::cout << "legs: ";
	if (legs != nullptr)
		legs->print(); std::cout << '\n';

	std::cout << "Shoes: ";
	if (shoes != nullptr)
		shoes->print(); std::cout << '\n';

	std::cout << "============================================\n" << std::endl;

}

//Open Inventory
void Player::open_inventory() {
	std::string choice;

	do
	{
		display_equipment();
		dispaly_stats();
		this->display_inventory();
		std::cout << "\nChoose slot of the item to interact (1-" << get_inventory_size() << ")\n";
		std::cout << "'Q' to quit inventory\n";
		std::cout << "Action: ";
		std::cin >> choice;
		int num{-1};

		if (!isalpha(choice[0]) && !isalpha(choice[1])) {
			num = std::stoi(choice) - 1;
		}

		if (num >= 0 && num < get_inventory_size()) {
			Item& item = *get_item(num);

			int act_choice{};

			std::cout << '\n' << item.get_name() << std::endl;
			std::cout << "1. Use\n";
			std::cout << "2. Drop\n";
			while (act_choice < 1 || act_choice > 2 || !std::cin.good()) {

				std::cout << "Action: ";
				std::cin >> act_choice;
				if (act_choice < 1 || act_choice > 2 || !std::cin.good()){
					std::cout << "Wrong action\n\n"; std::cin.clear(); std::cin.ignore();
				}
			}

			switch (act_choice) {
			case 1:
				use_item(get_item(num), num); break;
			case 2:
				remove_item_inventory(num); break;
			default:
				break;
			}

			Sleep(3000);

		}
		else if (choice[0] != 'Q' && choice[0] != 'q') {
			std::cout << "Wrong action" << std::endl;
			Sleep(1000);
		}
		system("cls");

	} while (choice[0] != 'Q' && choice[0] != 'q');

}


//Use
void Player::use_item(std::shared_ptr<Item>& item, int slotNum) {

	if (item->get_required_level() > this->get_level())
	{
		std::cout << "You don't have required level\n";
		return;
	}

	std::shared_ptr<Item> temp;

	switch (item->get_type()) { //1- weapon, 2 - armor

	case 1: {
		Weapon* weapon_tmp = dynamic_cast<Weapon*>(item.get());

		if (weapon != nullptr) {
			remove_damage(weapon_damage);
			temp = std::move(weapon);

			add_damage(weapon_tmp->get_damage_points());
			weapon_damage = weapon_tmp->get_damage_points();
			weapon = std::move(item);
			remove_stack_from_inventory(slotNum);
			add_to_inventory(temp);
		}

		else {
			add_damage(weapon_tmp->get_damage_points());
			weapon_damage = weapon_tmp->get_damage_points();
			weapon = std::move(item);
			remove_stack_from_inventory(slotNum);
		}
		break;
	}

	case 2: {
		Armor* armor_tmp = dynamic_cast<Armor*>(item.get());

		switch (armor_tmp->get_armor_type()) { //0 - helmet, 1- chest, 2- legs, 3 - shoes
		case 0: {
			if (helmet != nullptr) {
				remove_protection(helmet_protection);
				temp = std::move(helmet);

				add_protection(armor_tmp->get_protection_points());
				helmet_protection = armor_tmp->get_protection_points();
				helmet = std::move(item);
				remove_stack_from_inventory(slotNum);
				add_to_inventory(temp);
			}

			else {
				add_protection(armor_tmp->get_protection_points());
				helmet_protection = armor_tmp->get_protection_points();
				helmet = std::move(item);
				remove_stack_from_inventory(slotNum);
			}
		}break;

		case 1: {
			if (chest != nullptr) {
				remove_protection(chest_protection);
				temp = std::move(chest);

				add_protection(armor_tmp->get_protection_points());
				chest_protection = armor_tmp->get_protection_points();
				chest = std::move(item);
				remove_stack_from_inventory(slotNum);
				add_to_inventory(temp);
			}

			else {
				add_protection(armor_tmp->get_protection_points());
				chest_protection = armor_tmp->get_protection_points();
				chest = std::move(item);
				remove_stack_from_inventory(slotNum);
			}
		}break;

		case 2: {
			if (legs != nullptr) {
				remove_protection(legs_protection);
				temp = std::move(legs);

				add_protection(armor_tmp->get_protection_points());
				legs_protection = armor_tmp->get_protection_points();
				legs = std::move(item);
				remove_stack_from_inventory(slotNum);
				add_to_inventory(temp);
			}

			else {
				add_protection(armor_tmp->get_protection_points());
				legs_protection = armor_tmp->get_protection_points();
				legs = std::move(item);
				remove_stack_from_inventory(slotNum);
			}
		}break;

		case 3: {
			if (shoes != nullptr) {
				remove_protection(shoes_protection);
				temp = std::move(shoes);

				add_protection(armor_tmp->get_protection_points());
				shoes_protection = armor_tmp->get_protection_points();
				shoes = std::move(item);
				remove_stack_from_inventory(slotNum);
				add_to_inventory(temp);
			}

			else {
				add_protection(armor_tmp->get_protection_points());
				shoes_protection = armor_tmp->get_protection_points();
				shoes = std::move(item);
				remove_stack_from_inventory(slotNum);
			}
		}break;
		}
	}break;

	case 3: {
		Consumable* consumable_tmp = dynamic_cast<Consumable*>(item.get());
		// 0- healing
		switch (consumable_tmp->get_consumable_type()){
		case 0: {
			add_health_points(consumable_tmp->get_effect_points());
			remove_item_inventory(slotNum);
		}break;
		}
	}break;
	}

}

//getters

int Player::get_next_level_experience() const {
	return next_level_experience;
}

std::stringstream Player::get_player_stream() const {
	std::stringstream ss;

	ss << "Player: {\n";
	ss << get_name() << ", name\n";
	ss << get_max_health_points() << ", max health points\n";
	ss << get_absolute_damage() - weapon_damage<< ", absolute damage of player\n";
	ss << get_level() << ", level\n";
	ss << get_x() << ", x-cord\n";
	ss << get_y() << ", y-cord\n";
	ss << get_experience() << ", experience\n";
	ss << next_level_experience << ", next level experience\n}\n";

	return ss;
}

//std::unique_ptr<Item> weapon;
//std::unique_ptr<Item> helmet;
//std::unique_ptr<Item> chest;
//std::unique_ptr<Item> legs;
//std::unique_ptr<Item> shoes;
//int weapon_damage;
//int helmet_protection;
//int chest_protection;
//int legs_protection;
//int shoes_protection;

std::stringstream Player::get_equipment_stream() const {
	std::stringstream ss;
	ss << "Player equipment IDs: {\n";
	if (weapon != nullptr)
		ss  << weapon->get_id() << ", weapon" << '\n';
	
	if (helmet != nullptr)
		ss << helmet->get_id() << ", helmet" << '\n';
	
	if (chest != nullptr)
		ss << chest->get_id() << ", chest" << '\n';
	
	if (legs != nullptr)
		ss << legs->get_id() << ", legs" << '\n';
	
	if (shoes != nullptr)
	ss << shoes->get_id() << ", shoes" << '\n';

	ss << "}\n";
	/*ss << "}\nPlayers equimpnet stats: {";
	ss << weapon_damage << ',' << helmet_protection << ',' << chest_protection << ',' << legs_protection << ',' << shoes_protection << "}\n";*/

	return ss;
}

//modifiers 
void Player::add_experience_player(int value) {

	add_experience(value);
	std::cout << "You gained experienc: " << value << '\n' << *this << std::endl;

	level_up();
}
