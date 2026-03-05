#include "GameScripts.hpp"
#include "ItemList.hpp"
#include <random>
#include <iostream>
#include <string>
#include <windows.h>
#include <filesystem>
#include <ctime>
#include <chrono>
#include <limits>
#include <cwchar>
#undef max

namespace fs = std::filesystem;

GameScripts::GameScripts() {
	isRunning_game = true;
	tier1_init();

	std::unique_ptr<std::fstream> save;
	map = std::make_unique<Map>();

	if (!fs::exists("saves") && !fs::is_directory("saves"))
		fs::create_directory("saves");

	for (auto& path : fs::directory_iterator("saves")) {

		std::string filePath = path.path().string();
		save = std::make_unique<std::fstream>();
		save->open(filePath, std::ios::in);
		std::getline(*save, save_name);
		save->close();

		saves.push_back(std::make_pair(save_name, std::move(save)));
	}
}

void GameScripts::create_player() {

	std::cin.ignore();
	std::string name;
	std::cout << "Enter your character name: ";
	std::getline(std::cin, name);

	player = std::make_unique<Player>(name);
}

void GameScripts::run_game() {
	int choice;

	do {
		system("cls");

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,10);
		std::cout << "======================MAIN MENU=====================\n";
		SetConsoleTextAttribute(hConsole, 2);
		std::cout << "\t\t1. Continue\n";
		std::cout << "\t\t2. Exit\n\t\t";
		std::cout << "Action: ";
		std::cin >> choice;

		SetConsoleTextAttribute(hConsole, 1);


		switch (choice) {
		case 1: 
			show_saved_games();
			SetConsoleTextAttribute(hConsole, 7);
			run_save();
			  break;

		case 2: isRunning_game = false; break;
		default:
			std::cin.clear(); std::cin.ignore(); system("cls");
			break;
		}

	} while (isRunning_game || !std::cin.good());

}

void GameScripts::show_saved_games() {

	do{
		system("cls");
		std::cout << "Saves: \n";
		int i = 1;
		for (auto& save : saves) {
			std::cout << i << ". " << save.first << '\n';
			i++;
		}
		std::cout << i << ". New Game\n";

		

		std::cout << "Select save: ";
		std::cin >> save_slot_index;
		save_slot_index--;

	} while (save_slot_index < 0 || save_slot_index > saves.size() || !std::cin.good());

	if (saves.begin() + save_slot_index == saves.end()) {
		system("cls");
		std::cin.clear(); std::cin.ignore();
		std::cout << "Enter save name: ";
		std::getline(std::cin, save_name);

		create_new_game();
		saves.push_back(std::make_pair(save_name, std::make_unique<std::fstream>(save_game())));
	}

	else {
		load_game();
	}
}

void GameScripts::create_new_game() {

	create_player();
	map = std::make_unique<Map>();

	Sleep(2000);

	map->create_map();
	map->transform();
	map->spawn_mobs();
	system("cls");
}

std::fstream GameScripts::save_game() {

	std::string fileName = "saves\\save_" + std::to_string(save_slot_index + 1) + ".dat";
	std::fstream file;

	file.open(fileName, std::ios::out | std::ios::trunc);

	if (!file.good()) {
		fs::create_directories("saves");
		std::cout << "Directorie created\n\n";
		file.open(fileName, std::ios::out, std::ios::app);
	}

	file << save_name << '\n';
	file << player->get_player_stream().str();
	file << player->get_equipment_stream().str();
	file << player->get_inventory_stringstream().str();
	file << map->get_mob_stringstream().str();
	file << map->get_map_stringstream().str();

	file.close();

	return file;
}

void GameScripts::load_game() {
	/*player = std::make_unique<Player>(name, 100, 10, 1, 1, 1);*/

	std::string fileName = "saves\\save_" + std::to_string(save_slot_index + 1) + ".dat";
	std::fstream file;

	file.open(fileName, std::ios::in);

	if (!file.good()) {
		std::cout << "File doesnt exist\n\n";
	}

	std::string line;
	std::getline(file, save_name);
	

	//PLAYER
	std::getline(file, line);	//Player: {
	std::getline(file, line);
	auto pos = line.find(',');
	std::string name = line.substr(0, pos);

	std::getline(file, line);
	pos = line.find(',');
	int max_health = std::stoi(line.substr(0, pos));

	std::getline(file, line);
	pos = line.find(',');
	int absolute_damage = std::stoi(line.substr(0, pos));

	std::getline(file, line);
	pos = line.find(',');
	int level = std::stoi(line.substr(0, pos));

	std::getline(file, line);
	pos = line.find(',');
	int x_cord = std::stoi(line.substr(0, pos));

	std::getline(file, line);
	pos = line.find(',');
	int y_cord = std::stoi(line.substr(0, pos));

	std::getline(file, line);
	pos = line.find(',');
	int experience = std::stoi(line.substr(0, pos));

	std::getline(file, line);
	pos = line.find(',');
	int next_level_exp = std::stoi(line.substr(0, pos));

	player = std::make_unique<Player>(name, max_health, absolute_damage, level, x_cord, y_cord);

	//equipment 
	std::getline(file, line); std::getline(file, line); std::getline(file, line);
			
	while (line.find('}') == std::string::npos) {

		if (line.find("weapon") != std::string::npos) {
			pos = line.find(',');
			int id_tmp = std::stoi(line.substr(0, pos));

			std::shared_ptr<Item> temp = tier1_item_by_id(id_tmp);
			player->use_item(temp, 0);
			std::getline(file, line);
		}

		if (line.find("helmet") != std::string::npos) {
			pos = line.find(',');
			int id_tmp = std::stoi(line.substr(0, pos));

			std::shared_ptr<Item> temp = tier1_item_by_id(id_tmp);
			player->use_item(temp, 0);
			std::getline(file, line);
		}

		if (line.find("chest") != std::string::npos) {
			pos = line.find(',');
			int id_tmp = std::stoi(line.substr(0, pos));

			std::shared_ptr<Item> temp = tier1_item_by_id(id_tmp);
			player->use_item(temp, 0);
			std::getline(file, line);
		}

		if (line.find("legs") != std::string::npos) {
			pos = line.find(',');
			int id_tmp = std::stoi(line.substr(0, pos));

			std::shared_ptr<Item> temp = tier1_item_by_id(id_tmp);
			player->use_item(temp, 0);
			std::getline(file, line);
		}

		if (line.find("shoes") != std::string::npos) {
			pos = line.find(',');
			int id_tmp = std::stoi(line.substr(0, pos));

			std::shared_ptr<Item> temp = tier1_item_by_id(id_tmp);
			player->use_item(temp, 0);
			std::getline(file, line);
		}
	}

	//INVENTORY
	std::getline(file, line); //Inventory IDs: {
	pos = line.find('{') + 1;

	while (line.at(pos) != '}'){
		int id_tmp{};
		int amount{1};

		size_t t = line.find(',', pos) - 1;
		if (line.at(line.find(',', pos) - 1) == ')') { //ifstackable

			id_tmp = std::stoi(line.substr(pos, line.find('(')));
			pos = line.find('(') + 1;

			amount = std::stoi(line.substr(pos, line.find(')') - pos));
		}

		else
			id_tmp = std::stoi(line.substr(pos, line.find(',')));

		std::shared_ptr<Item> tmp = tier1_item_by_id(id_tmp);
		tmp->set_curr_num_of_blocks_in_stack(amount);
		player->add_to_inventory(tmp);

		if (line.at(line.find(',', pos) + 1) != '}')
			pos = line.find(',') + 1;

		else
			pos = line.size() - 1;
	}


	//MOBS
	std::getline(file, line);	//Mobs: {
	
	while (std::getline(file, line) && line.find(';') == std::string::npos) {// {
		
		std::getline(file, line);
		pos = line.find(',');
		std::string mob_name = line.substr(0, pos);

		std::getline(file, line);
		pos = line.find(',');
		int mob_level = std::stoi(line.substr(0, pos));

		std::getline(file, line);
		pos = line.find(',');
		int x_mob = std::stoi(line.substr(0, pos));

		std::getline(file, line);
		pos = line.find(',');
		int y_mob = std::stoi(line.substr(0, pos));

		map->set_mob_at_cord(mob_name, mob_level, x_mob, y_mob);
		std::getline(file, line); // }
	}

	//MAP
	std::getline(file, line);	//Map: {

	for (int i = 0; i < map->get_map_Y_max(); i++) {

		getline(file, line);	// getting row
		for (int j = 0; j < map->get_map_X_max(); j++) {
			map->set_map_at_cord(i, j, line[j] - '0');
		}
	}

	file.close();
}

void GameScripts::run_save() {

	system("cls");
	isRunning_save = true;
	I_display();
}

int GameScripts::I_game_menu() {
	int choice{};

	std::cout << "\nChoose action:\n";
	std::cout << "1. Move your character\n";
	std::cout << "2. Open inventory\n";
	std::cout << "3. Save game\n";
	std::cout << "4. Main menu\n\n"
		<< "Action: ";
	std::cin >> choice;

	return choice;
}

void GameScripts::I_display() {

	int action{};

	while (isRunning_save) {

		//map->display_mobs();
		map->display(*player);

		action = I_game_menu();;

		switch (action) {
		case 1: I_move_character(); break;
		case 2: I_open_inventory(); break;
		case 3: save_game(); break;
		case 4: isRunning_save = false ;break;

		default: std::cout << "Wrong action" << std::endl;
			break;
		}

		if (player->get_health_points() <= 0)
			I_display();
	}


}

void GameScripts::I_move_character() {

	int x, y;

	do {
		std::cout << "\nEnter X cordinates: ";
		std::cin >> x;
		std::cout << "Enter Y cordinates: ";
		std::cin >> y;

		if (!std::cin.good()) {
			std::cin.clear(); std::cin.ignore();
		}


		if (x < 1 || y < 1 || x > map->get_map_X_max() || y > map->get_map_Y_max()) {
			std::cout << "\nEnter correct cordinates\n";
		}

	} while (x < 1 || y < 1 || x > map->get_map_X_max() || y > map->get_map_Y_max());

	int Xdistance = abs(player->get_x() - x);
	int Ydistance = abs(player->get_y() - y);

	while ((Xdistance != 0 || Ydistance != 0) && player->get_health_points() > 0) {
		if (Xdistance >= Ydistance) {
			if (x < player->get_x())
				player->set_x(player->get_x() - 1);
			else
				player->set_x(player->get_x() + 1);

			Xdistance--;
		}

		else {
			if (y < player->get_y())
				player->set_y(player->get_y() - 1);
			else
				player->set_y(player->get_y() + 1);

			Ydistance--;
		}

		system("cls");
		//map->display_mobs();
		map->display(*player);

		if (map->mobs_cord(player->get_x(), player->get_y()) != nullptr) {

			std::unique_ptr<Entity> mob = std::move(map->mobs_cord(player->get_x(), player->get_y()));
			mob->spawn();

			fight(*mob);
			Xdistance = 0;
			Ydistance = 0;
		}
		Sleep(1000);
	}
	system("cls");
}

void GameScripts::I_open_inventory() {
	system("cls");
	player->open_inventory();
	system("cls");
}

void GameScripts::pick_up_item(Entity &e) {

	char action{};

	do
	{
		e.display_inventory();

		std::cout << "\nEnter slot number to pick the item (1-" << e.get_inventory_size() << ")\n";
		std::cout << "Enter 'A' to take all items\n";
		std::cout << "Enter 'Q' to quit\n";

		std::cin >> action;
		action = std::toupper(action);

		if (action == 'A') {
			while (e.get_inventory_size() > 0) {

				player->add_to_inventory(e.get_item(0));
				e.remove_stack_from_inventory(0);
			}
		}

		if (isdigit(action))
		{
			int num = action - '0';
			int amount{};

			if (num < 1 || num > e.get_inventory_size())
				std::cout << "Wrong slot number" << std::endl;

			else {
				player->add_to_inventory(e.get_item(num-1));
				e.remove_stack_from_inventory(num-1);
			}

		}
	} while (action != 'A' && action != 'Q' && e.get_inventory_size() > 0);
}

void GameScripts::fight(Entity& e) {

	//randomize who start(1 - player, 2 - e)
	std::random_device rand;
	std::uniform_int_distribution<> distr(1,2);
	int priority = distr(rand);
	int damage;
	int beaten{};

	if (priority % 2 == 1)
		std::cout << player->get_name() << " begin the fight.\n\n";
	else
		std::cout << e.get_name() << " begin the fight.\n\n";

	Sleep(5000);

	for (int i = priority; player->get_health_points() > 0 && e.get_health_points() > 0; i++) {

		if (i % 2 == 1) {

			damage = player->get_damage();
			damage -= protection_mupliplier * damage * e.get_protection();
			if (damage < 0)	damage = 0;

			e.receive_damage(damage);

			std::cout << " [ " << e.get_health_points() << "/" << e.get_max_health_points() << " HP.]\n\n";
		}

		else {
			damage = e.get_damage();
			damage -= protection_mupliplier * damage * player->get_protection();
			if (damage < 0)	damage = 0;
			player->receive_damage(damage);

			std::cout << " [ " << player->get_health_points() << "/" << player->get_max_health_points() << " HP.]\n\n";
		}

		Sleep(1000);
	}

	if (e.get_health_points() <= 0){
		e.drops();
		player->add_experience_player(e.get_experience());
		pick_up_item(e);
		std::cout << std::endl;
		Sleep(1000);
	}

	if (player->get_health_points() <= 0) {
		player->death();
		player.reset();	// clear std::unique<Player> player
		create_player();
	}
}

