#pragma once

#include "Item.hpp"

class Money : public virtual Item {
	static constexpr int type = 0;
	static constexpr bool is_stackable = true;

public:
	Money();
	Money(const Money& source);
	virtual ~Money() = default;

	virtual void print() const override;
	int get_type() const override;

	void add(int amount_to_add);
	void remove(int amount_to_remove);
};