#pragma once
#include "Entity.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "Consumable.hpp"

class Player : public virtual Entity {
	
	int next_level_experience;
	static size_t constexpr inv_size = 40;
	static int constexpr default_next_level_experience = 1000;
	static const int default_level = 1;
	static const int default_damage = 10;
	static const int default_health = 100;
	static const int default_x = 1;
	static const int default_y = 1;

	//Equipment
	std::shared_ptr<Item> weapon;
	std::shared_ptr<Item> helmet;
	std::shared_ptr<Item> chest;
	std::shared_ptr<Item> legs;
	std::shared_ptr<Item> shoes;
	int weapon_damage{};
	int helmet_protection{};
	int chest_protection{};
	int legs_protection{};
	int shoes_protection{};

public:
	Player(std::string name);
	Player(std::string name, int health_points, int damage, int level, int xpos, int ypos);
	Player(const Player& source);

	//in game
	virtual void spawn() override;
	virtual void drops() override;
	virtual void death() override;
	void open_inventory();
	void display_equipment() const;
	void dispaly_stats() const;

	bool isLevelUp();
	void level_up();

	//Use
	void use_item(std::shared_ptr<Item>& item, int slotNum);

	//gettters
	int get_next_level_experience() const;
	std::stringstream get_player_stream() const;
	std::stringstream get_equipment_stream() const;

	//modifiers
	void add_experience_player(int value);
};