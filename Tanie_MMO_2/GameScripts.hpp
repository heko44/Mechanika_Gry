#pragma once
#include "Entity.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include <fstream>

class GameScripts {
	static double constexpr protection_mupliplier = 0.005;
	std::vector<std::pair<std::string, std::unique_ptr<std::fstream>>> saves;

	std::unique_ptr<Player> player;
	std::unique_ptr<Map> map;

	int save_slot_index{};
	std::string save_name;
	bool isRunning_game{ false };
	bool isRunning_save{ false };

public:
	GameScripts();

	void create_player();
	void show_saved_games();
	void create_new_game();
	void load_game();
	std::fstream save_game();
	void run_save();

	void fight(Entity& entity);
	void pick_up_item(Entity &e);

	void run_game();
	int I_game_menu();
	void I_display();
	void I_move_character();
	void I_open_inventory();
};