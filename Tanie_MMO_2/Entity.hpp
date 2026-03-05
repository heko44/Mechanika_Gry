#pragma once
#include "Inventory.hpp"

class Entity {

	//=====Variables=====
	std::string name;
	int health_points;
	int max_health_points;
	int damage;
	int protection;
	int level;
	int xpos, ypos;
	size_t inventory_max_size;
	int experience;

	std::random_device rand;

	//=======Inventory=================
	std::unique_ptr<Inventory> inventory;

	//==========Friends===============================================
	friend std::ostream& operator<<(std::ostream& os, const Entity& entity);


public:

	//Constructor, Deep copy, virtual destructor
	Entity(std::string name, int max_health_points, int damage, int level, int xpos, int ypos, size_t inventorySize);
	Entity(const Entity& source);
	virtual ~Entity() = default;

	//Invetory operations
	void add_to_inventory(std::shared_ptr<Item>& item);
	void add_to_inventory_at_index(std::shared_ptr<Item> &item, int slotNum);
	void remove_item_inventory(int slotNumber);
	void remove_stack_from_inventory(int slotNumber);
	void display_inventory() const;
	std::shared_ptr<Item>& get_item(int slotNumber) const;

	//in game events
	void receive_damage(int value);
	virtual void spawn() = 0;
	virtual void drops() = 0;
	virtual void death() = 0;

	//getters
	int get_health_points() const;
	int get_absolute_damage() const;
	int get_damage() const;
	int get_protection() const;
	int get_level() const;
	std::string get_name() const;
	int get_x() const;
	int get_y() const;
	size_t get_inventory_size() const;
	int get_experience() const;
	int get_max_health_points() const;
	std::stringstream get_inventory_stringstream() const;
	std::stringstream get_entity_stream() const;

	//setters
	void set_health_points(int value);
	void set_max_health_points(int value);
	void set_damage(int value);
	void set_protection(int value);
	void set_level(int value);
	void set_name(std::string name);
	void set_x(int xPos);
	void set_y(int yPos);
	void set_experience(int value);


	//modifiers
	void take_damage(int value);
	void add_health_points(int value);
	void add_damage(int value);
	void add_level(int value);
	void add_protection(int value);
	void add_experience(int value);
	void add_max_health_points(int value);

	void remove_health_points(int value);
	void remove_damage(int value);
	void remove_level(int value);
	void remove_protection(int value);

};