#pragma once
#include "Item.hpp"

class Consumable : public virtual Item {

	static constexpr int type = 3;
	static constexpr bool is_stackable = true;
	int consumable_type; // 0 - healing
	int effect_points; // points of a change in some entity property 

public:
	Consumable(int id, std::string name, int price, int consumable_type, int effect_points);
	Consumable(const Consumable& source);
	virtual ~Consumable() = default;

	int get_type() const override;
	int get_consumable_type() const;
	int get_effect_points() const;

	virtual void print() const override;
};