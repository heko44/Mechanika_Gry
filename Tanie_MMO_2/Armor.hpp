#pragma once
#include "Item.hpp"

class Armor : public virtual Item {
	int protection_points{};

	static constexpr int type = 2;
	static constexpr bool is_stackable = false;
	int armor_type;	//0 - helmet, 1- chest, 2- legs, 3 - shoes

public:
	Armor(int id, std::string name, int price, int protection_points, int required_level, int armor_type);
	Armor(const Armor& source);
	virtual ~Armor() = default;

	//print
	virtual void print() const override;

	//getters
	int get_protection_points() const;
	int get_required_lvl() const;
	int get_armor_type() const;
	virtual int get_type() const override;

	//setters
	void set_protection_points(int value);
	void set_required_lvl(int value);

	//modifires
	void add_protection_points(int value);
};