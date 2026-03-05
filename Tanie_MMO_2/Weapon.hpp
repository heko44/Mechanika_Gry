#pragma once
#include "Item.hpp"

class Weapon : public virtual Item {
	int damage_points{};

	static constexpr bool is_stackable = false;
	static constexpr int type = 1;

public:
	Weapon(int id, std::string name, int price, int damage_points, int required_level);
	Weapon(const Weapon& source);
	virtual ~Weapon() = default;

	//print
	virtual void print() const override;

	//getters
	int get_damage_points() const;
	int get_required_lvl() const;
	virtual int get_type() const override;

	//setters
	void set_damage_points(int value);
	void set_required_lvl(int value);

	//modifires
	void add_damage_points(int value);
};