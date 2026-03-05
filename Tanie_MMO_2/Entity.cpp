#include "Entity.hpp"
#include <random>
#include <iostream>
#include <sstream>

//========================================Constructor,Deepcopy=========================================================

Entity::Entity(std::string name_tmp, int max_health_points_tmp, int damage_tmp, int level_tmp, int xpos_tmp, int ypos_tmp, size_t inventorySize)
	:name(name_tmp), max_health_points(max_health_points_tmp), health_points(max_health_points_tmp), damage(damage_tmp), level(level_tmp),
	xpos(xpos_tmp), ypos(ypos_tmp), inventory_max_size(inventorySize),
	protection(0), experience(0) {
	inventory = std::make_unique<Inventory>(inventorySize);
}

Entity::Entity(const Entity& source)
	:Entity(source.name, source.max_health_points, source.damage, source.level, source.xpos, source.ypos, source.inventory_max_size) {
	
	health_points = source.get_health_points();
	protection = source.get_protection();
	experience = source.get_experience();
	inventory = std::make_unique<Inventory>(source.inventory_max_size);
}

//=========================== operatro<< overloaded===========================
std::ostream& operator<<(std::ostream& os, const Entity& ent) {
	
	os << ent.name << " (" << ent.level << " lv. | " << ent.health_points << "/" << ent.max_health_points << "HP | " << ent.experience << " exp)";
	return os;
}

//===============Inventory=============

void Entity::add_to_inventory(std::shared_ptr<Item>& item) {
	inventory->add_item(item);
}

void Entity::remove_item_inventory(int slotNumber) {
	inventory->remove_item(slotNumber);
}

void Entity::remove_stack_from_inventory(int slotNumber) {
	inventory->remove_stack(slotNumber);
}

void Entity::display_inventory() const {
	std::cout << name << "'s inventory:\n";
	inventory->print();
}

std::shared_ptr<Item>& Entity::get_item(int slotNumber) const {
	return inventory->get_item(slotNumber);
}

size_t Entity::get_inventory_size() const {
	return inventory->get_inventory_size();
}

//===============Getters====================
int Entity::get_health_points()const {
	return health_points;
}

int Entity::get_damage() const {

	//randomize a damage in range from 80% to 120% of damage
	std::random_device rand;
	std::uniform_int_distribution<int> dist(int(damage * 0.8), int(damage * 1.2));

	return dist(rand);
}

int Entity::get_absolute_damage() const {
	return damage;
}

int Entity::get_level() const {
	return level;
}

std::string Entity::get_name() const {
	return name;
}

int Entity::get_x() const {
	return xpos;
}

int Entity::get_y() const {
	return ypos;
}

int Entity::get_protection() const {
	return protection;
}

int Entity::get_experience() const {
	return experience;
}

int Entity::get_max_health_points() const {
	return max_health_points;
}

std::stringstream Entity::get_inventory_stringstream() const {
	return inventory->get_inventory_stream();
}

std::stringstream Entity::get_entity_stream() const {
	std::stringstream ss;

	ss << "{\n";
	ss << name << ", name\n";
	ss << level << ", level\n";
	ss << xpos << ", x-cord\n";
	ss << ypos << ", y-cord\n}\n";

	return ss;
}

//================Setters======================
void Entity::set_health_points(int value) {
	health_points = value;
}

void Entity::set_max_health_points(int value) {
	max_health_points = value;
	health_points = value;
}

void Entity::set_damage(int value) {
	damage = value;
}

void Entity::set_level(int value) {
	level = value;
}

void Entity::set_name(std::string n) {
	name = n;
}

void Entity::set_x(int value) {
	xpos = value;
}

void Entity::set_y(int value) {
	ypos = value;
}

void Entity::set_protection(int value) {
	protection = value;
}

void Entity::set_experience(int value) {
	experience = value;
}

//===================Modifiers================

//add
void Entity::take_damage(int value) {
	health_points -= value;
}

void Entity::add_health_points(int value) {
	health_points += value;
}

void Entity::add_damage(int value) {
	damage += value;
}

void Entity::add_level(int value) {
	level += value;
}

void Entity::add_protection(int value) {
	protection += value;
}

void Entity::add_experience(int value) {
	experience += value;
}

void Entity::add_max_health_points(int value) {
	max_health_points += value;
}


//remove
void Entity::remove_health_points(int value) {
	health_points -= value;
}

void Entity::remove_damage(int value) {
	damage -= value;
}

void Entity::remove_level(int value) {
	level -= value;
}

void Entity::remove_protection(int value) {
	protection -= value;
}

//==================In game events====================================
void Entity::receive_damage(int damage_value) {
	std::cout << "\n" << name << "'s Health: " << health_points << " - " << damage_value;

	this->health_points -= damage_value;
}