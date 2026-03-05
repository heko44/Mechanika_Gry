#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include "Goblin.hpp"
#include <array>
#undef near

class Map {

	static constexpr int HEIGHT = 40 + 1;
	static constexpr int WIDTH = 99 + 1;

	int map[HEIGHT][WIDTH] = { 0 };
	std::array<std::array<std::unique_ptr<Entity>, WIDTH>, HEIGHT> mobs;

	static constexpr int bush = 0;
	static constexpr int field = 1;
	static constexpr int tree = 2;
	//static const int cave = 3;

	static constexpr char c_field = '.';
	static constexpr char c_bush = '#';
	static constexpr char c_tree = '?';

public:
	void create_map();
	void display(const Player& player) const;
	void display2() const;
	void display_mobs() const;
	void transform();
	void spawn_mobs();
	int near(int x, int y);

	//getters
	std::unique_ptr<Entity>& mobs_cord(int xPos, int yPos);
	int get_map_X_max()const;
	int get_map_Y_max() const;
	int get_map_at_cord(int x, int y) const;
	std::unique_ptr<Entity>& get_mob_from_cord(int x, int y);
	std::stringstream get_mob_stringstream() const;
	std::stringstream get_map_stringstream() const;

	//setters
	void set_map_at_cord(int x, int y, int Tex);
	void set_mob_at_cord(std::string name, int level, int x, int y);

};