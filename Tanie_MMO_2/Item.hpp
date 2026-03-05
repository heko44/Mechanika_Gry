#pragma once
#include <string>
#include <random>

class Item {

	//Item variables
	int type;	//0 - money, 1- weapon, 2 - armor, 3- consumable
	int id;
	bool is_stackable;
	int max_num_blocks;
	int curr_num_of_blocks_in_stack;
	int price;
	std::string name;
	int required_level{};

	std::random_device rand_device;

	//static int AVAILABLE_ID ;

public:

	//Constructor, Deep copy, virtual desstructor
	Item(int id, std::string name, int type, int price, bool is_stackable, int required_level);
	Item(const Item& source);
	virtual ~Item() = default;

	virtual void print() const = 0;

	//getters
	virtual int get_type() const = 0;
	int get_id() const;
	bool stackable() const;
	int get_max_num_blocks() const;
	int get_curr_num_of_blocks_in_stack() const;
	std::string get_name() const;
	int get_price() const;
	int get_required_level() const;
	std::random_device& get_rand_device();


	//setters
	void set_max_num_blocks(int value);
	void set_curr_num_of_blocks_in_stack(int value);
	void set_id(int id);
	void set_required_level(int value);
};