#include "Armor.hpp"
#include <iostream>

Armor::Armor(int id_tmp, std::string name_tmp, int price_tmp, int protection_points_tmp, int required_level_tmp, int armor_type_tmp)
	:Item(id_tmp, name_tmp, type ,price_tmp, is_stackable, required_level_tmp), protection_points(protection_points_tmp),armor_type(armor_type_tmp) {

}

Armor::Armor(const Armor& source)
	:Item(source.get_id(), source.get_name(), type ,source.get_price(), is_stackable, source.get_required_level()), protection_points(source.protection_points), 
	armor_type(source.get_armor_type()) {

}

//print
void Armor::print() const {
	std::cout << get_name() << " | " << get_protection_points() << " protection | " << get_required_level() << " level required | " << get_price() << " $";
}

//getters
int Armor::get_protection_points() const {
	return protection_points;
}

int Armor::get_required_lvl() const {
	return get_required_level();
}

int Armor::get_type() const {
	return type;
}

int Armor::get_armor_type() const {
	return armor_type;
}

//setters
void Armor::set_protection_points(int value) {
	protection_points = value;
}

void Armor::set_required_lvl(int value) {
	set_required_level(value);
}

//modifires
void Armor::add_protection_points(int value) {
	protection_points += value;
}