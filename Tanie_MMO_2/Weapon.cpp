#pragma once
#include "Weapon.hpp"
#include <string>
#include <iostream>

Weapon::Weapon(int id_tmp, std::string name_tmp, int price_tmp, int damage_points_tmp, int required_level_tmp)
	:Item(id_tmp, name_tmp, type, price_tmp, is_stackable, required_level_tmp), damage_points(damage_points_tmp) {

}

Weapon::Weapon(const Weapon& source)
	:Item(source.get_id(), source.get_name(),type ,source.get_price(), is_stackable, source.get_required_level()), damage_points(source.damage_points){

}

//print
void Weapon::print() const {
	std::cout << get_name() << " | " << get_damage_points() << " damage | " << get_required_level() << " level required | " << get_price() << " $";
}

//getters
int Weapon::get_damage_points() const {
	return damage_points;
}

int Weapon::get_required_lvl() const {
	return get_required_level();
}

int Weapon::get_type() const {
	return type;
}

//setters
void Weapon::set_damage_points(int value) {
	damage_points = value;
}

void Weapon::set_required_lvl(int value) {
	set_required_level(value);
}

//modifires
void Weapon::add_damage_points(int value) {
	damage_points += value;
}